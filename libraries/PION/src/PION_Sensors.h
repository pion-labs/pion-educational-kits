#ifndef PION_SENSORS_H
#define PION_SENSORS_H 

#include "_types.h"
  
class Sensors{
  public:
    static InitStatus_t init();
    static float temperature;
    static float humidity;
    static float pressure;
    static float BMPtemp;
    static float CO2Level;
    static float luminosity;
    static float accel[3];
    static float gyro[3];
    static float mag[3];

};

#endif