#include <Arduino.h>

#include "_config.h"
#include "_types.h"

#include "PION_Storage.h"
#include "PION_System.h"
#include "PION_Sensors.h"
#include "PION_Network.h"

#include "FS.h"
#include "SD.h"
#include "SPI.h"

SDStatus_t Storage::sdStatus = NO_SD;

TaskHandle_t sdTask;
void SDTask(void *pvParameters);

void createFileFirstLine(fs::FS &fs, const char * path);
void appendFile(fs::FS &fs, const char * path, TickType_t time);

const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
char fileName[13] = FILE_BASE_NAME "00.csv";

void Storage::init(){
  LOG("Storage::init");ENDL;

  pinMode(PIN_SD_SS, OUTPUT);

  if(!SD.begin(PIN_SD_SS)){
    LOG("SD Card Mount Falhou");ENDL;
  }
  
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    Storage::sdStatus = NO_SD;
    LOG("Não ha cartão SD");ENDL;
  } else{
    Storage::sdStatus = SD_CONNECTED;
  }
}

void Storage::init(bool original){
  LOG("Storage::init");ENDL;

  pinMode(PIN_SD_SS, OUTPUT);

  if(!SD.begin(PIN_SD_SS)){
    LOG("SD Card Mount Falhou");ENDL;
  }
  
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    Storage::sdStatus = NO_SD;
    LOG("Não ha cartão SD");ENDL;
  } else{
    Storage::sdStatus = SD_CONNECTED;
  }
  
  createSDLogTask();
}

void Storage::createSDLogTask(){
  xTaskCreatePinnedToCore(SDTask, "SDTask", 4096, NULL, 1, &sdTask, ARDUINO_RUNNING_CORE);
}

bool haveStartTime = false;

void SDTask(void *pvParameters){

  (void)pvParameters;

  TickType_t startTick;
  TickType_t runTime;
  vTaskSuspend(sdTask);
  for(;;){
    if(!haveStartTime){
      startTick = xTaskGetTickCount();
      haveStartTime = true;
    }

    if(Storage::sdStatus == SD_RECORDING){
      appendFile(SD, fileName, xTaskGetTickCount()-startTick);
    }
    vTaskDelay(500);
  }
}

void Storage::toggleSD(uint8_t type){
  switch (Storage::sdStatus){
    case SD_CONNECTED:
      // Find an unused file name.
      if (BASE_NAME_SIZE > 6) {
        LOG("FILE_BASE_NAME too long");ENDL;
      }
      while (SD.exists(fileName)) {
        if (fileName[BASE_NAME_SIZE + 1] != '9') {
          fileName[BASE_NAME_SIZE + 1]++;
        } else if (fileName[BASE_NAME_SIZE] != '9') {
          fileName[BASE_NAME_SIZE + 1] = '0';
          fileName[BASE_NAME_SIZE]++;
        } else {
          LOG("Can't create file name");ENDL;
        }
      }
      createFileFirstLine(SD, fileName);
      Storage::sdStatus = SD_RECORDING;
      vTaskResume(sdTask);
      if(type == 1){
        Network::deInit();
      }
      break;
    case SD_RECORDING:
      LOG("Escrita finalizada!");ENDL;
      haveStartTime = false;
      Storage::sdStatus = SD_CONNECTED;
      vTaskSuspend(sdTask);
      break;
    case NO_SD:
      LOG("Nenhum SD Conectado!");ENDL;
      break;
    default:
      LOG("Erro de ativação de escrita!");ENDL;
      break;
  }
}

void Storage::deactivateSDLog(){
  if(Storage::sdStatus == SD_RECORDING){
    LOG("Escrita finalizada!");ENDL;
    haveStartTime = false;
    Storage::sdStatus = SD_CONNECTED;
    vTaskSuspend(sdTask);
  } else if(Storage::sdStatus == NO_SD){
    LOG("Nenhum SD Conectado!");ENDL;
  }
}

void Storage::activateSDLog(){
  if(Storage::sdStatus == SD_CONNECTED){
    // Find an unused file name.
    if (BASE_NAME_SIZE > 6) {
      LOG("FILE_BASE_NAME too long");ENDL;
    }
    while (SD.exists(fileName)) {
      if (fileName[BASE_NAME_SIZE + 1] != '9') {
        fileName[BASE_NAME_SIZE + 1]++;
      } else if (fileName[BASE_NAME_SIZE] != '9') {
        fileName[BASE_NAME_SIZE + 1] = '0';
        fileName[BASE_NAME_SIZE]++;
      } else {
        LOG("Can't create file name");ENDL;
      }
    }
    createFileFirstLine(SD, fileName);
    Storage::sdStatus = SD_RECORDING;
    vTaskResume(sdTask);
  } else if(Storage::sdStatus == NO_SD){
    LOG("Nenhum SD Conectado!");ENDL;
  }
}

void Storage::createLogOnSD(){
  switch (Storage::sdStatus){
    case SD_CONNECTED:
      // Find an unused file name.
      if (BASE_NAME_SIZE > 6) {
        LOG("FILE_BASE_NAME too long");ENDL;
      }
      while (SD.exists(fileName)) {
        if (fileName[BASE_NAME_SIZE + 1] != '9') {
          fileName[BASE_NAME_SIZE + 1]++;
        } else if (fileName[BASE_NAME_SIZE] != '9') {
          fileName[BASE_NAME_SIZE + 1] = '0';
          fileName[BASE_NAME_SIZE]++;
        } else {
          LOG("Can't create file name");ENDL;
        }
      }
      createFileFirstLine(SD, fileName);
      Storage::sdStatus = SD_RECORDING;
      break;
    case NO_SD:
      LOG("Nenhum SD Conectado!");ENDL;
      break;
    default:
      LOG("Erro de ativação de escrita!");ENDL;
      break;
  }
}

void Storage::logOnSDFile(){
  if(Storage::sdStatus == SD_RECORDING){
    appendFile(SD, fileName, xTaskGetTickCount());
  } else{
    LOG("Erro na criação do Arquivo!");ENDL;
  }
}

__attribute__((weak)) void createFileFirstLine(fs::FS &fs, const char * path){
    Serial.printf("Escrevendo em: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Falha ao abrir para escrita");
        return;
    }
    const char * message = "tempo(ms),temperatura(C),umidade(%),pressao(Pa),co2(ppm),luminosidade(%),acelX(m/s2),accelY,acelZ,giroX(graus/s),giroY,giroZ,magX(uT),magY,magZ,bateria(%)";
    if(file.println(message)){
        Serial.println("Escrita Começou");
    } else {
        Serial.println("Falha na escrita");
    }
    file.close();
}

__attribute__((weak)) void appendFile(fs::FS &fs, const char * path, TickType_t time){
    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Falha ao abrir para gravacao");
        return;
    }
    file.print(time);
    file.write(',');
    file.print(Sensors::temperature);
    file.write(',');
    file.print(Sensors::humidity);
    file.write(',');
    file.print(Sensors::pressure);
    file.write(',');
    file.print(Sensors::CO2Level);
    file.write(',');
    file.print(Sensors::luminosity);
    file.write(',');
    file.print(Sensors::accel[0]);
    file.write(',');
    file.print(Sensors::accel[1]);
    file.write(',');
    file.print(Sensors::accel[2]);
    file.write(',');
    file.print(Sensors::gyro[0]);
    file.write(',');
    file.print(Sensors::gyro[1]);
    file.write(',');
    file.print(Sensors::gyro[2]);
    file.write(',');
    file.print(Sensors::mag[0]);
    file.write(',');
    file.print(Sensors::mag[1]);
    file.write(',');
    file.print(Sensors::mag[2]);
    file.write(',');
    file.println(System::battery);
    file.close();
}