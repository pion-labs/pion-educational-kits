#include "PION_System.h"

/* 
  Esse código demonstra como o subsistema de armazenamento de dados
  pode ser utilizado para que de acordo com a chamada da função 
  logOnSDFile() sejam armazenados os dados coletados.
*/

System canSat;

void setup(){
  // Inicializa seu canSat, e seus periféricos  
  canSat.init();
  // Cria o arquivo para armazenamento no cartão SD
  canSat.createLogOnSD();
}

void loop(){
  // Salva uma nova linha com dados no seu arquivo a cada 1000 millisegundos ou 1 segundo
  canSat.logOnSDFile();
  delay(1000);
}
