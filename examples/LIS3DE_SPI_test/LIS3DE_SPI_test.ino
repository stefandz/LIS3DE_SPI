#include <LIS3DE_SPI.h>

const int CS_pin = 2; // set this to the pin connected to CS on the LIS3DE
const uint32_t SPI_clock_Hz = 100000;

LIS3DE_SPI LIS3DE( CS_pin, SPI_clock_Hz );

void setup() {

  Serial.begin( 9600 );
  while( !Serial );  

  SPI.begin();
  
}

void loop() {

  // print X, Y, Z values every 5 seconds, switching off the LIS3DE between readings

  LIS3DE.enable( true, LIS3DE_SPI::NormalLowPower1Hz, LIS3DE_SPI::XYZ, LIS3DE_SPI::Scale2g, false );
  while( !LIS3DE.dataAvailable() );

  Serial.print  ( "X = " );
  Serial.print  ( LIS3DE.getX());
  Serial.println( "g" );

  Serial.print  ( "Y = " );
  Serial.print  ( LIS3DE.getY());
  Serial.println( "g" );

  Serial.print  ( "Z = " );
  Serial.print  ( LIS3DE.getZ());
  Serial.println( "g" );  

  Serial.println();
  
  LIS3DE.disable();

  delay( 5000 );
}


