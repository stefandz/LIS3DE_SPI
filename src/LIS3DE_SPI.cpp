#include "LIS3DE_SPI.h"
#include <math.h>

#define _BV(bit) (1 << (bit))

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

LIS3DE_SPI::LIS3DE_SPI( int CS_pin, uint32_t SPI_clock_Hz = 100000 )
{
	this->CS_pin = CS_pin;
	pinMode( this->CS_pin , OUTPUT );
	digitalWrite( this->CS_pin, HIGH ); // CS is active LOW

	this->SPI_clock_Hz = SPI_clock_Hz;
}

int8_t LIS3DE_SPI::getTemperatureDelta()
{
	setRegisterBits(CTRL_REG4, _BV(BDU));

	readRegister(OUT_ADC3_L); // low byte can be thrown away, but must be read!
	int8_t value = readRegister(OUT_ADC3_H);

	unsetRegisterBits(CTRL_REG4, _BV(BDU));

	return value;
}

bool LIS3DE_SPI::dataAvailable()
{
	bool dataAvailable = (0b00001000 & readRegister(LIS3DE_SPI::STATUS_REG2)) > 0;
	return dataAvailable;
}

void LIS3DE_SPI::setScale(Scale scale)
{
	writeRegister(CTRL_REG4, (scale << FS0));
	this->scale = scale;
}

float LIS3DE_SPI::getGsFromScaledValue(int8_t value)
{
	int8_t scaleMax = getScaleMax( scale );
	return mapFloat(value, INT8_MIN, INT8_MAX, -scaleMax, scaleMax);
}

int8_t LIS3DE_SPI::getScaledValueFromGs(float gValue)
{
	int8_t scaleMax = getScaleMax( scale );
	return trunc(mapFloat(gValue, -scaleMax, scaleMax, INT8_MIN, INT8_MAX));
}

int8_t LIS3DE_SPI::getScaleMax(Scale scale)
{
	return (1 << (scale + 1));
}

void LIS3DE_SPI::enable(bool isLowPowerEnabled, ODR odr, Axes axes, Scale scale, bool isTemperatureOn)
{
	// set odr, mode, enabled axes
	writeRegister(CTRL_REG1, (odr << ODR0) | (isLowPowerEnabled << LPen) | axes);

	setScale( scale );

	if (isTemperatureOn) {
		// enable aux ADC and temperature sensor
		writeRegister(TEMP_CFG_REG, _BV(ADC_PD) | _BV(TEMP_EN));
	}
	else {
		// disable aux ADC and temperature sensor
		writeRegister(TEMP_CFG_REG, 0);
	}
}

void LIS3DE_SPI::disable()
{
	enable(true, PowerDown, NoAxis, scale, false);
}

void LIS3DE_SPI::reboot()
{
	writeRegister(CTRL_REG5, _BV(BOOT));
}

void LIS3DE_SPI::setRegisterBits(Register reg, uint8_t byteValue)
{
	uint8_t value = readRegister(reg);
	value |= byteValue;
	writeRegister(reg, value);
}

void LIS3DE_SPI::unsetRegisterBits(Register reg, uint8_t byteValue)
{
	uint8_t value = readRegister(reg);
	value &= ~byteValue;
	writeRegister(reg, value);
}

void LIS3DE_SPI::enableInterrupt1(uint8_t axesEvents, float threshold, uint8_t duration, InterruptMode interruptMode)
{
	// setup the interrupt
	writeRegister(IG1_CFG, interruptMode | (axesEvents & 0b00111111));
	writeRegister(IG1_THS, getScaledValueFromGs(threshold));
	writeRegister(IG1_DURATION, duration);

	// disable latching
	unsetRegisterBits(CTRL_REG5, _BV(LIR_IG1));

	// enable interrupt generator 1 on INT1
	setRegisterBits(CTRL_REG3, _BV(INT1_IG1));
}

void LIS3DE_SPI::disableInterrupt1()
{
	// disable interrupt generator 1
	unsetRegisterBits(CTRL_REG3, _BV(INT1_IG1));
}

void LIS3DE_SPI::enableInterrupt2(uint8_t axesEvents, float threshold, uint8_t duration, InterruptMode interruptMode)
{
	// setup the interrupt
	writeRegister(IG2_CFG, interruptMode | (axesEvents & 0b00111111));
	writeRegister(IG2_THS, getScaledValueFromGs(threshold));
	writeRegister(IG2_DURATION, duration);

	// disable latching
	unsetRegisterBits(CTRL_REG5, _BV(LIR_IG2));

	// enable interrupt generator 2 on INT2
	setRegisterBits(CTRL_REG6, _BV(INT2_IG2));
}

void LIS3DE_SPI::disableInterrupt2()
{
	// enable interrupt generator 2 on INT2
	unsetRegisterBits(CTRL_REG6, _BV(INT2_IG2));
}

uint8_t LIS3DE_SPI::readRegister(Register reg)
{
	SPI.beginTransaction( SPISettings( SPI_clock_Hz, MSBFIRST, SPI_MODE0 ));
	digitalWrite( CS_pin, LOW );

  	SPI.transfer(( 0b10000000 | reg ) & 0b10111111 );

	scratch = SPI.transfer( 0x00 ); // send 8 dummy bits to clock out the register

	digitalWrite( CS_pin, HIGH );

	return( scratch );
}

void LIS3DE_SPI::writeRegister(Register reg, uint8_t value)
{
	SPI.beginTransaction( SPISettings( SPI_clock_Hz, MSBFIRST, SPI_MODE0 ));
	digitalWrite( CS_pin, LOW );

  	SPI.transfer( reg & 0b00111111 );
	SPI.transfer( value ); 

	digitalWrite( CS_pin, HIGH );
}
