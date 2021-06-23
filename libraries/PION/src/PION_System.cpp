#include <Arduino.h>
#include <WiFi.h>

#include "_config.h"
#include "_types.h"

#include "PION_System.h"
#include "PION_Storage.h"
#include "PION_Sensors.h"
#include "PION_Network.h"
#include "PION_Interface.h"

// Instantiate an I2C Handling Semaphore
SemaphoreHandle_t System::xI2C_semaphore;

// Sensors Debugging Task that is default turned off
#ifdef DEBUG
  // Task for serial Inputs
  void SerialInTask(void *pvParameters);
  void DebugSensorTask(void *pvParameters); 
#endif

uint8_t initSuccess = 0;

// System battery so everyone access
uint8_t System::battery = 0;

float battery = 0;
void BatteryTask(void *pvParameters);

uint32_t getSerialNumber();

InitStatus_t status = INIT_OK;

float batteryCache[50]={0};
float calculateMovingAvg(float * ,uint8_t ,float);

Sensors sensors;
Storage storage;
Network network;
Interface interface;

// System Initialization 
void System::init(){

  // initialize serial communication at speed set in config file
  Serial.begin(SERIAL_SPEED);

  // Creation of the system mutex for I2C comms
  System::xI2C_semaphore = xSemaphoreCreateMutex();

  // Act if semaphore creation not possible
  if (System::xI2C_semaphore == NULL){
    LOG("Falha ao criar Semaphore");ENDL;
    vTaskDelay(1000);
    ESP.restart(); 
  }
  
  interface.init();
  
  network.init();

  status = Sensors::init();

  storage.init();
  /* Check sensors initialization status and if it's OK, Beep and log initialization
    if it's false present the user through the LEDs which sensor is faulty */
  if(status == INIT_OK){
    interface.doBeeps(2,50,100);
    LOG("System::init");ENDL;
  }else{
    interface.setLed((((1 << ((uint8_t)(ERROR_BMP280-1))) & status)>>(ERROR_BMP280-1)) >= 1 ? ERROR_BMP280 : -1);
    interface.setLed((((1 << ((uint8_t)(ERROR_SHT20-1))) & status)>>(ERROR_SHT20-1)) >= 1 ? ERROR_SHT20 : -1);
    interface.setLed((((1 << ((uint8_t)(ERROR_MPU9250-1))) & status)>>(ERROR_MPU9250-1)) >= 1 ? ERROR_MPU9250 : -1);
    interface.setLed((((1 << ((uint8_t)(ERROR_CCS811-1))) & status)>>(ERROR_CCS811-1)) >= 1 ? ERROR_CCS811 : -1);
    interface.sirenAction = ALARM_ERROR;
    vTaskResume(interface.sirenTask);
    LOG("System::failed");ENDL;
  }

  // FreeRTOS Tasks Creation
  xTaskCreatePinnedToCore(BatteryTask, "BatTask", 1024  , NULL, 1, NULL, ARDUINO_RUNNING_CORE);

  #ifdef SENSORS_DEBUG
    xTaskCreatePinnedToCore(SerialInTask, "SerialTask", 4096  , NULL, 1, NULL, ARDUINO_RUNNING_CORE);
    xTaskCreatePinnedToCore(DebugSensorTask, "DebugTask", 1024  , NULL, 1, NULL, ARDUINO_RUNNING_CORE);
  #endif
}

// System Initialization 
void System::init(bool original){

  // initialize serial communication at speed set in config file
  Serial.begin(SERIAL_SPEED);

  // Creation of the system mutex for I2C comms
  System::xI2C_semaphore = xSemaphoreCreateMutex();

  // Act if semaphore creation not possible
  if (System::xI2C_semaphore == NULL){
    LOG("Falha ao criar Semaphore");ENDL;
    vTaskDelay(1000);
    ESP.restart(); 
  }
  
  interface.init(true);
  
  network.init();

  status = Sensors::init();

  storage.init(true);
  /* Check sensors initialization status and if it's OK, Beep and log initialization
    if it's false present the user through the LEDs which sensor is faulty */
  if(status == INIT_OK){
    interface.doBeeps(2,50,100);
    LOG("System::init");ENDL;
  }else{
    interface.setLed((((1 << ((uint8_t)(ERROR_BMP280-1))) & status)>>(ERROR_BMP280-1)) >= 1 ? ERROR_BMP280 : -1);
    interface.setLed((((1 << ((uint8_t)(ERROR_SHT20-1))) & status)>>(ERROR_SHT20-1)) >= 1 ? ERROR_SHT20 : -1);
    interface.setLed((((1 << ((uint8_t)(ERROR_MPU9250-1))) & status)>>(ERROR_MPU9250-1)) >= 1 ? ERROR_MPU9250 : -1);
    interface.setLed((((1 << ((uint8_t)(ERROR_CCS811-1))) & status)>>(ERROR_CCS811-1)) >= 1 ? ERROR_CCS811 : -1);
    interface.sirenAction = ALARM_ERROR;
    vTaskResume(interface.sirenTask);
    LOG("System::failed");ENDL;
  }

  // FreeRTOS Tasks Creation
  xTaskCreatePinnedToCore(BatteryTask, "BatTask", 1024  , NULL, 1, NULL, ARDUINO_RUNNING_CORE);

  #ifdef SENSORS_DEBUG
    xTaskCreatePinnedToCore(SerialInTask, "SerialTask", 4096  , NULL, 1, NULL, ARDUINO_RUNNING_CORE);
    xTaskCreatePinnedToCore(DebugSensorTask, "DebugTask", 1024  , NULL, 1, NULL, ARDUINO_RUNNING_CORE);
  #endif
}

// System without network Initialization 
void System::initNoNetwork(){

  // initialize serial communication at speed set in config file
  Serial.begin(SERIAL_SPEED);

  // Creation of the system mutex for I2C comms
  System::xI2C_semaphore = xSemaphoreCreateMutex();

  // Act if semaphore creation not possible
  if (System::xI2C_semaphore == NULL){
    LOG("Falha ao criar Semaphore");ENDL;
    vTaskDelay(1000);
    ESP.restart(); 
  }
  
  // Initialize interface options
  interface.init();

  // Initialize Sensors and get it's status
  status = sensors.init();

  // Initialize Storage
  storage.init();

  /* Check sensors initialization status and if it's OK, Beep and log initialization
  if it's false present the user through the LEDs which sensor is faulty */
  if(status == INIT_OK){
    interface.doBeeps(2,50,100);
    LOG("System::init");ENDL;
  }else{
    interface.setLed((((1 << ((uint8_t)(ERROR_BMP280-1))) & status)>>(ERROR_BMP280-1)) >= 1 ? ERROR_BMP280 : -1);
    interface.setLed((((1 << ((uint8_t)(ERROR_SHT20-1))) & status)>>(ERROR_SHT20-1)) >= 1 ? ERROR_SHT20 : -1);
    interface.setLed((((1 << ((uint8_t)(ERROR_MPU9250-1))) & status)>>(ERROR_MPU9250-1)) >= 1 ? ERROR_MPU9250 : -1);
    interface.setLed((((1 << ((uint8_t)(ERROR_CCS811-1))) & status)>>(ERROR_CCS811-1)) >= 1 ? ERROR_CCS811 : -1);
    interface.sirenAction = ALARM_ERROR;
    vTaskResume(interface.sirenTask);
    LOG("System::failed");ENDL;
  }

  /////////////////////////////////////////////////////////////////////////////////
  //                         FreeRTOS Tasks Creation                             //
  /////////////////////////////////////////////////////////////////////////////////
  xTaskCreatePinnedToCore(BatteryTask, "BatTask", 1024  , NULL, 1, NULL, ARDUINO_RUNNING_CORE);
  #ifdef DEBUG
    xTaskCreatePinnedToCore(SerialInTask, "SerialTask", 4096  , NULL, 1, NULL, ARDUINO_RUNNING_CORE);
    xTaskCreatePinnedToCore(DebugSensorTask, "DebugTask", 1024  , NULL, 1, NULL, ARDUINO_RUNNING_CORE);
  #endif
}

// TODO move this to utils
uint8_t mapfloat(float x, float in_min, float in_max, float out_min, float out_max){
  uint8_t result = (uint8_t)((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
  return  result > 100 ? 100 : result; 
}

void BatteryTask( void *pvParameters ){
  (void)pvParameters;
  
  pinMode(BAT_SENSOR, INPUT);
  
  uint8_t counter = 0;
  
  for(;;){
    vTaskDelay(200);
    
    if(counter >= 50){
      System::battery = mapfloat(calculateMovingAvg(batteryCache,50,VBAT_VOLTAGE(analogRead(BAT_SENSOR))), 3.5, 4.15, 0.0, 100.0);
      battery = VBAT_VOLTAGE(analogRead(BAT_SENSOR));
    } else{
      System::battery =  mapfloat(VBAT_VOLTAGE(analogRead(BAT_SENSOR)), 3.5, 4.15, 0.0, 100.0);
      battery = VBAT_VOLTAGE(analogRead(BAT_SENSOR));
      calculateMovingAvg(batteryCache,50,VBAT_VOLTAGE(analogRead(BAT_SENSOR)));
      counter++;
    }

    if (System::battery <= 15){
      vTaskResume(interface.sirenTask);
      interface.sirenAction = ALARM_LOW_BATTERY;
    } else if(interface.sirenAction != ALARM_SIREN){
      interface.sirenAction = ALARM_OFF;
    }
  }
}

#ifdef DEBUG
void DebugSensorTask(void *pvParameters){
  (void)pvParameters;
  
  for(;;){
    LOG("[SYSTEM] Siren Action: "); 
    LOG(interface.sirenAction);ENDL;
    LOG("[SYSTEM] Battery: ");
    LOG(System::battery);
    LOG("% ");
    LOG(battery);
    LOG("V");ENDL;
    LOG("[SENSORS] Pressure: ");
    LOG(Sensors::pressure);ENDL;
    LOG("[SENSORS] Temperature: ");
    LOG(Sensors::temperature);ENDL;
    LOG("[SENSORS] Humidity: ");
    LOG(Sensors::humidity);ENDL;
    LOG("[SENSORS] CO2: ");
    LOG(Sensors::CO2Level);ENDL;
    LOG("[SENSORS] Luminosity: ");
    LOG(Sensors::luminosity);ENDL;
    LOG("[SENSORS] Accel: ");
    LOG(Sensors::accel[0]);ENDL;
    LOG("[SENSORS] Gyro: ");
    LOG(Sensors::gyro[0]);ENDL;
    LOG("[SENSORS] Mag: ");
    LOG(Sensors::mag[0]);ENDL;
    vTaskDelay(1000);
  }
}

void SerialInTask(void *pvParameters){
  (void)pvParameters;
  
  char commandsBuffer[3] = {0};
  bool menu = false;
  const char* sensorStateMessage[] = {"OK","Error"};
  const char* sdStatusMessage[] = {"NO_SD","SD_CONNECTED","SD_RECORDING","SD_ERROR"};
  
  for(;;){
    if(!menu){
        ENDL;
        LOG(F("------ PION Satélites Educacionais ------"));ENDL;
        LOG(F("a ... para status de inicializacao"));ENDL;
        LOG(F("b ... para Nivel de Bateria"));ENDL;
        LOG(F("d ... para dados de todos os sensores"));ENDL;
        LOG(F("h ... para reimprimir ajuda"));ENDL;
        LOG(F("l ... para acionar os LEDs"));ENDL;
        LOG(F("r ... para reiniciar"));ENDL;
        LOG(F("s ... para Serial Number"));ENDL;
        LOG(F("u ... para Iniciar/Parar salvamento no cartão SD sem WiFi"));ENDL;
        LOG(F("x ... para Ligar a Sirene"));ENDL;
        LOG(F("z ... para Ligar o RGB"));ENDL;
        menu = true;
    }
    if(Serial.available()){
      commandsBuffer[0] = Serial.read();
      switch (toupper(commandsBuffer[0])){
      case 'A':
        LOG("SD:");
        LOG(sdStatusMessage[Storage::sdStatus]);ENDL;
        LOG("BMP280:");
        LOG(sensorStateMessage[(((1 << ((uint8_t)(ERROR_BMP280-1))) & status)>>(ERROR_BMP280-1))]);ENDL;
        LOG("SHT20:");
        LOG(sensorStateMessage[(((1 << ((uint8_t)(ERROR_SHT20-1))) & status)>>(ERROR_SHT20-1))]);ENDL;
        LOG("MPU9250:");
        LOG(sensorStateMessage[(((1 << ((uint8_t)(ERROR_MPU9250-1))) & status)>>(ERROR_MPU9250-1))]);ENDL;
        LOG("CCS811:");
        LOG(sensorStateMessage[(((1 << ((uint8_t)(ERROR_CCS811-1))) & status)>>(ERROR_CCS811-1))]);ENDL;
        break;
      case 'B':
        LOG("[SYSTEM] Battery: ");
        LOG(System::battery);
        LOG("% ");
        LOG(battery);
        LOG("V");ENDL;
        break;
      case 'D':
        LOG("[SENSORS] Pressure(Pa): ");
        LOG(Sensors::pressure);ENDL;
        LOG("[SENSORS] Temperature(C): ");
        LOG(Sensors::temperature);ENDL;
        LOG("[SENSORS] Humidity(%): ");
        LOG(Sensors::humidity);ENDL;
        LOG("[SENSORS] CO2(ppm): ");
        LOG(Sensors::CO2Level);ENDL;
        LOG("[SENSORS] Luminosity: ");
        LOG(Sensors::luminosity);ENDL;
        LOG("[SENSORS] Accel(m/s^2): ");
        LOG(Sensors::accel[0]);LOG(" | ");LOG(Sensors::accel[1]);LOG(" | ");LOG(Sensors::accel[2]);ENDL;
        LOG("[SENSORS] Gyro(deg/s): ");
        LOG(Sensors::gyro[0]);LOG(" | ");LOG(Sensors::gyro[1]);LOG(" | ");LOG(Sensors::gyro[2]);ENDL;
        LOG("[SENSORS] Mag(uT): ");
        LOG(Sensors::mag[0]);LOG(" | ");LOG(Sensors::mag[1]);LOG(" | ");LOG(Sensors::mag[2]);ENDL;
        break;
      case 'H':
        menu = false;
        break;
      case 'L':
        interface.toggleLed();
        break;
      case 'R':
        LOG(F("Reiniciando..."));ENDL;
        ESP.restart();
        break;
      case 'S':
        LOG(String(getSerialNumber()));
        break;
      case 'U':
        Storage::toggleSD(1);
        break;
      case 'X':
        interface.toggleSiren();
        break;
      case 'Z':
        interface.toggleRGB();
        break;
      default:
        LOG(F("Comando não encontrado"));ENDL;
        menu = false;
        break;
      }
    }
  }
}
#endif

// Get Battery Level
uint8_t System::getBattery(){
  return System::battery;
}

// Get Temperature from sensors
float System::getTemperature(){
  return sensors.temperature;
}

// Get Humidity from sensors
float System::getHumidity(){
  return sensors.humidity;
}

// Get Pressure from sensors
float System::getPressure(){
  return sensors.pressure;
}

// Get CO2Level from sensors
float System::getCO2Level(){
  return sensors.CO2Level;
}

// Get Luminosity Value from sensors
float System::getLuminosity(){
  return sensors.luminosity;
}

// Get Accelerometer Values from sensors
float System::getAccelerometer(uint8_t axis){
  if(axis < 3)
    return sensors.accel[axis];
  else 
    return 0;
}

// Get Gyroscope  from sensors
float System::getGyroscope(uint8_t axis){
  if(axis < 3)
    return sensors.gyro[axis];
  else 
    return 0;
}

// Get Magnetometer from sensors
float System::getMagnetometer(uint8_t axis){
  if(axis < 3)
    return sensors.gyro[axis];
  else 
    return 0;
}

void System::setRGB(uint8_t color){
  interface.setRGB(color);
}

void System::setLed(uint8_t number){
  interface.setLed(number);
}

void System::setLed(uint8_t number, uint8_t state){
  interface.setLed(number, state);
}

void System::buzzer(uint16_t duration){
  interface.doBeeps(1, duration, 0);
}

void System::doBeeps(uint8_t times, uint16_t duration, uint16_t interval){
  interface.doBeeps(times, duration, interval);
}

void System::toggleSiren(){
  interface.toggleSiren();
}

SDStatus_t System::getSDStatus(){
  return storage.sdStatus;
}

SirenState_t System::getSirenState(){
  return interface.sirenAction;
}

void System::createSDLogTask(){
  storage.createSDLogTask();
}

void System::toggleSD(){
  storage.toggleSD(0);
}

void System::activateSDLog(){
  storage.activateSDLog();
}

void System::deactivateSDLog(){
  storage.deactivateSDLog();
}


void System::createLogOnSD(){
  storage.createLogOnSD();
}

void System::logOnSDFile(){
  storage.logOnSDFile();
}

// Ease out the battery levels by applying a moving average filter
float calculateMovingAvg(float *avg , uint8_t numSamples, float sample) {
  float sum = 0;

  uint8_t i = 0;

  for(i = 0; i < numSamples - 1; i++){
    avg[i] = avg[i+1];
  }

  avg[(numSamples - 1)] = sample;

  for (i = 0; i < numSamples; i++) {
    sum += avg[i];
  }

  return (sum/(float)numSamples);
}

// Perform a read of the mac address connverting it from HEX to Decimal
uint32_t System::getSerialNumber(){
    uint32_t chipId = 0;
    for(int i=0; i<17; i=i+8) {
      chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
    }
    return (chipId);
}

