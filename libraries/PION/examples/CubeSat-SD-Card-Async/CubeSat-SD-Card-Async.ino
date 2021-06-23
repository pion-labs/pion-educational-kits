#include "PION_System.h"

/* 
  Esse código demonstra como o subsistema de armazenamento de dados
  pode ser utilizado para que de maneira assíncrona (em paralelo a 
  seu código) seja feito armazenamento dos dados coletados.
*/

System cubeSat;

void setup(){
  // Inicializa seu cubeSat, e seus periféricos  
  cubeSat.init();
  // Cria a Task assíncrona de armazenamento
  cubeSat.createSDLogTask();
}
void loop(){
  // Liga a gravação a cada meio segundo por 30 segundos
  cubeSat.activateSDLog();
  // Libera o sistema para fazer outras ações por 30000 millisegundos
  delay(30000);
  // Desativa a gravação 
  cubeSat.deactivateSDLog();
}