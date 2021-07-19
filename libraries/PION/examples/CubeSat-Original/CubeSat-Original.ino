#include "PION_System.h"

/* 
  Esse código demonstra como interagir com os LEDs presentes na placa de interface do seu kit
*/

System cubeSat;

void setup(){
  // Inicializa seu CanSat, e seus periféricos 
  cubeSat.init(true);
}

void loop(){
  // Loop vazio pois as funções básicas rodam em um nucleo paralelo
}