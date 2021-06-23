#include "PION_System.h"

/* 
  Esse código demonstra como interagir com os LEDs presentes na placa de interface do seu kit
*/

System cubeSat;

void setup(){
  // Inicializa seu CubeSat, e seus periféricos 
  cubeSat.init();
}

void loop(){
  // Ativa o LED L1
  cubeSat.setLed(L1, HIGH);
  delay(1000);
  // Desativa o LED L1
  cubeSat.setLed(L1, LOW);
  delay(1000);
}