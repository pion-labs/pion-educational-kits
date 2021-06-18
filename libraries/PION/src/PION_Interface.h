#ifndef PION_INTERFACE_H
#define PION_INTERFACE_H 

#include "_types.h"

class Interface{
  public:
    static void init();
    static void init(bool);
    static void doBeeps(uint8_t, uint16_t, uint16_t);
    static SirenState_t sirenAction;
    static TaskHandle_t sirenTask;
    static void setLed(uint8_t);
    static void setLed(uint8_t,uint8_t);
    static void setRGB(uint8_t);
    static bool shouldChangeLed;
    static bool shouldChangeRGB;
    static void toggleRGB(void);
    static void toggleLed(void);
    static void toggleSiren(void);
};

#endif