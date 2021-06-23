#include "PION_System.h"
#include "FS.h"

/* 
  Esse código demonstra como o subsistema de armazenamento de dados
  pode ser modificado para que de acordo com a chamada da função 
  logOnSDFile() sejam armazenados os dados desejados.
*/


System cubeSat;

void setup(){
  // Inicializa seu cubeSat, e seus periféricos  
  cubeSat.init();
  // Cria o arquivo para armazenamento no cartão SD
  cubeSat.createLogOnSD();
}

void loop(){
  // Salva uma nova linha com dados no seu arquivo a cada 1000 millisegundos ou 1 segundo
  cubeSat.logOnSDFile();
  delay(1000);
}

// Declaração de funções que sobrescrevem as funcionalidades padrão

// Função Modificada
void createFileFirstLine(fs::FS &fs, const char * path){
  // Mostra o nome do arquivo
  Serial.printf("Escrevendo em: %s\n", path);
  
  //Abre o arquivo do SD para a memória RAM
  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Falha ao abrir para escrita");
    return;
  }
  // Cria a primeira linha modificada e separada por vírgulas do CSV. 
  const char * message = "tempo(ms),temperatura(C),umidade(%),co2(ppm),bateria(%)";
  
  // Escreve a mensagem criada anteriormente
  if(file.println(message)){
    Serial.println("Escrita Começou");
  } else {
    Serial.println("Falha na escrita");
  }
  // Fecha o arquivo
  file.close();
}

// Função Modicada para armazenamento
void appendFile(fs::FS &fs, const char * path, TickType_t time){
  //Abre o arquivo do SD para a memória RAM
  File file = fs.open(path, FILE_APPEND);
  if(!file){
    Serial.println("Falha ao abrir para gravacao");
    return;
  }
  // Salva no CSV o dado, seguido de uma vírgula. 
  file.print(time);
  file.write(',');
  file.print(cubeSat.getTemperature());
  file.write(',');
  file.print(cubeSat.getHumidity());
  file.write(',');
  file.print(cubeSat.getCO2Level());
  file.write(',');
  file.println(cubeSat.getBattery());
  // Fecha o arquivo
  file.close();
}