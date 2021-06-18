#include "PION_System.h"

System canSat;

void setup(){
  // Inicializa seu CanSat    
  canSat.init();
}

void loop(){
  canSat.setRGB(BLUE);
  delay(1000);
  canSat.setLed(OFF);
  delay(1000);
}