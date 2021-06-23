#ifndef STORAGE_H
#define STORAGE_H 
  
#include "_types.h"

class Storage{
  public:
    static SDStatus_t sdStatus;
    static void init();
    static void init(bool);
    static void toggleSD(uint8_t);
    static void deactivateSDLog();
    static void activateSDLog();
    static void createSDLogTask();
    static void createLogOnSD();
    static void logOnSDFile();
};

#endif