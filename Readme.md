# LIS3DE_SPI

SPI Arduino library for the ST LIS3DE.

Forked from [Sodaq_LIS3DE](https://github.com/SodaqMoja/Sodaq_LIS3DE) with improvements by [ctjet](https://github.com/ctjet/Sodaq_LIS3DE).

## Usage

Method|Description
------|------
**LIS3DE\_SPI( int CS_pin, uint32_t SPI_clock_Hz = 100000 )**|Constructor with requiring CS pin number and optional SPI clock frequency in Hz.
**getTemperatureDelta()**|Returns the temperature delta as read from the sensor (8-bit int).
**enable( bool isLowPowerEnabled = false, ODR odr = NormalLowPower25Hz, Axes axes = XYZ, Scale scale = Scale2g, bool isTemperatureOn = true )**|Enables the sensor with the default values or the given data rate, axes and scale.
**disable()**|Disables the sensor and puts it in the lowest power consumption state possible.
**reboot()**|Resets all the registers of the sensor.
**enableInterrupt1( uint8_t axesEvents, float threshold, uint8_t duration, InterruptMode interruptMode = MovementRecognition )**|Enables the interrupt on INT1 pin using the given triggger criteria. The axesEvents can be multiple ORed AxesEvents.
**enableInterrupt2( uint8_t axesEvents, float threshold, uint8_t duration, InterruptMode interruptMode = MovementRecognition )**|Enables the interrupt on INT2 pin using the given triggger criteria. The axesEvents can be multiple ORed AxesEvents.
**getX()**|Returns a measurement of the X axis (float, in g).
**getY()**|Returns a measurement of the Y axis (float, in g).
**getZ()**|Returns a measurement of the Z axis (float, in g).

## Examples

See examples folder - currently just a demo that prints X, Y, Z values every 5 seconds, switching off the LIS3DE between readings.

## License

Copyright (c) 2017 SODAQ with additions from ctjet and stefandz. All rights reserved.

This file is part of LIS3DE_SPI.

LIS3DE_SPI is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation, either version 3 of
the License, or(at your option) any later version.

LIS3DE_SPI is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with LIS3DE_SPI.  If not, see
<http://www.gnu.org/licenses/>.
