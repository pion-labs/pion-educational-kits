#include "PION_System.h"

System canSat;

void setup(){
  // Inicializa seu CanSat    
  canSat.init();
}

void loop(){
  canSat.setLed(L1, HIGH);
  delay(1000);
  canSat.setLed(L1, LOW);
  delay(1000);
}