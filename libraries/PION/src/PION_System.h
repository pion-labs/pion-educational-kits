#ifndef PION_SYSTEM_H
#define PION_SYSTEM_H 
  
#include "_types.h"

class System{
  public:
    static void init();
    static void init(bool);
    static void initNoNetwork();
    static uint8_t battery;
    static uint8_t getBattery();
    static SemaphoreHandle_t xI2C_semaphore;
    static float getTemperature();
    static float getHumidity();
    static float getPressure();
    static float getCO2Level();
    static float getLuminosity();
    static float getAccelerometer(uint8_t);
    static float getGyroscope(uint8_t);
    static float getMagnetometer(uint8_t);
    static void setRGB(uint8_t);
    static void setLed(uint8_t);
    static void setLed(uint8_t,uint8_t);
    static void buzzer(uint16_t);
    static void doBeeps(uint8_t, uint16_t, uint16_t);
    static void toggleSiren();
    static SirenState_t getSirenState();
    static uint32_t getSerialNumber();
    static SDStatus_t getSDStatus();
    static void createSDLogTask();
    static void toggleSD();
    static void deactivateSDLog();
    static void activateSDLog();
    static void createLogOnSD();
    static void logOnSDFile();
};

#endif