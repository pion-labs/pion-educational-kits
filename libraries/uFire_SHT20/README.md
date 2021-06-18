### SHT20 Temperature and Humidity Sensor

Measure temperature and humidity with the Sensiron SHT20 sensor.    

- **Temperature range**: -40 to 125 C(-40 to 257 F)
- **Humidity range**: 0 to 100 % RH
- **Temperature accuracy**: ± 0.5% C
- **Humidity accuracy**: ± 5% RH
- **Interface**: I2C
- **Voltage range**: 2.1 - 3.6 V
 
#### What it is

An SHT20 sensor in a plastic enclosure with a 1m length of cable. 

The device uses the [Qwiic](https://www.sparkfun.com/qwiic) Connect System for wiring, it's an easy-to-use, polarized, push-to-fit connector. No more mistaken connections or soldering header pins. 

#### Using it

Read the [documentation](https://ufire.co/docs/uFire_SHT20/) on the [specifications] of the device.

The library to use it is in the Arduino and Particle.io IDE. A [python](https://github.com/u-fire/uFire_SHT20/tree/master/python/RaspberryPi) and [rust](https://crates.io/crates/ufire_sht20) implementation for Raspberry Pi is available. 

```
#include "uFire_SHT20.h"
uFire_SHT20 sht20;

Wire.begin();
sht20.begin();
float temp_c = sht20.temperature();
float rh = sht20.humidity();
```

#### Buy it

Visit [ufire.co](http://ufire.co) and buy a board and probe.
