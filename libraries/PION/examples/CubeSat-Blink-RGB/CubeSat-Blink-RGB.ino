#include "PION_System.h"

/* 
  Esse código demonstra como interagir com os LEDs RGB presentes na placa de interface do seu kit
*/

System cubeSat;

void setup(){
  // Inicializa seu cubeSat, e seus periféricos  
  cubeSat.init();
}

void loop(){
  cubeSat.setRGB(BLUE);
  delay(1000);
  cubeSat.setRGB(OFF);
  delay(1000);
}