#ifndef PION_NETWORK_H
#define PION_NETWORK_H 
  
class Network{
  public:
    static void init();
    static void deInit();
    static TaskHandle_t netTask;
};

#endif