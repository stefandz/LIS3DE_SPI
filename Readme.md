# Sodaq_LIS3DE

Arduino library for the ST LIS3DE.

## Usage

Method|Description
------|------
**LIS3DE(TwoWire& wire = Wire, uint8_t address = LIS3DE_ADDRESS)**|Constructor with optional Wire instance and address parameters.
**getTemperatureDelta()**|Returns the temperature delta as read from the sensor (8-bit int).
**enable(bool isLowPowerEnabled = false, ODR odr = NormalLowPower25Hz, Axes axes = XYZ, Scale scale = Scale2g, bool isTemperatureOn = true)**|Enables the sensor with the default values or the given data rate, axes and scale.
**disable()**|Disables the sensor and puts it in the lowest power consumption state possible.
**reboot()**|Resets all the registers of the sensor.
**enableInterrupt1(uint8_t axesEvents, float threshold, uint8_t duration, InterruptMode interruptMode = MovementRecognition)**|Enables the interrupt on INT1 pin using the given triggger criteria. The axesEvents can be multiple ORed AxesEvents.
**enableInterrupt2(uint8_t axesEvents, float threshold, uint8_t duration, InterruptMode interruptMode = MovementRecognition)**|Enables the interrupt on INT2 pin using the given triggger criteria. The axesEvents can be multiple ORed AxesEvents.
**getX()**|Returns a measurement of the X axis.
**getY()**|Returns a measurement of the Y axis.
**getZ()**|Returns a measurement of the Z axis.

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request


## License

Copyright (c) 2017 SODAQ. All rights reserved.

This file is part of Sodaq_LIS3DE.

Sodaq_LIS3DEis free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation, either version 3 of
the License, or(at your option) any later version.

Sodaq_LIS3DEis distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with Sodaq_LIS3DE.  If not, see
<http://www.gnu.org/licenses/>.
