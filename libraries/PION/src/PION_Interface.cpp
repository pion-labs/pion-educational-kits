#include <Arduino.h>

#include <Wire.h>
#include <MCP23017.h>

#include "_types.h"
#include "_config.h"

#include "PION_System.h"
#include "PION_Interface.h"

// IoExpander Helper Variables
uint16_t mcpState = 0;
MCP23017 mcp = MCP23017(MCP23017_ADDR);

// Actuator's functions
void setRGB(uint8_t);
void setLed(uint8_t);

// Storing and sharing Siren State
bool sirenState = false;

bool Interface::shouldChangeLed = false;
bool Interface::shouldChangeRGB = false;

// Task Handles for managing all actuators tasks
TaskHandle_t Interface::sirenTask;

SirenState_t Interface::sirenAction = ALARM_OFF;

// Tasks Forward Declaration
void SirenTask(void *pvParameters);
void LedTask(void *pvParameters);


// Interface Class
void Interface::init(){

  pinMode(BUZZER, OUTPUT);

  xTaskCreatePinnedToCore(SirenTask, "SirenTask", 1024, NULL, 1, &sirenTask, ARDUINO_RUNNING_CORE);
 
 // Aquire Semaphore for I2C port expander instantiation
  if ( xSemaphoreTake(System::xI2C_semaphore, TIME_TO_SEMAPHORE ) == pdTRUE ){
    
    Wire.begin();
    
    mcp.init();
    
    mcp.portMode(MCP23017Port::A, 0); //Port A as output
    mcp.portMode(MCP23017Port::B, 0); //Port B as output

    mcp.writeRegister(MCP23017Register::GPIO_A, 0x00);  //Reset port A 
    mcp.writeRegister(MCP23017Register::GPIO_B, 0x00);  //Reset port B

    mcp.write(0);

    xSemaphoreGive(System::xI2C_semaphore);
  }else{
    LOG("[D]Int init Semaphore");ENDL;
  }

  setRGB(RED);
  vTaskDelay(200);
  setRGB(GREEN);
  vTaskDelay(200);
  setRGB(BLUE);
  vTaskDelay(200);
  setRGB(WHITE);
  vTaskDelay(200);  
  setRGB(OFF);

  xTaskCreatePinnedToCore(LedTask, "LedTask", 1024, NULL, 1, NULL, ARDUINO_RUNNING_CORE);
}

// Interface Class
void Interface::init(bool original){

  pinMode(BUZZER, OUTPUT);

  xTaskCreatePinnedToCore(SirenTask, "SirenTask", 1024, NULL, 1, &sirenTask, ARDUINO_RUNNING_CORE);
 
 // Aquire Semaphore for I2C port expander instantiation
  if ( xSemaphoreTake(System::xI2C_semaphore, TIME_TO_SEMAPHORE ) == pdTRUE ){
    
    Wire.begin();
    
    mcp.init();
    
    mcp.portMode(MCP23017Port::A, 0); //Port A as output
    mcp.portMode(MCP23017Port::B, 0); //Port B as output

    mcp.writeRegister(MCP23017Register::GPIO_A, 0x00);  //Reset port A 
    mcp.writeRegister(MCP23017Register::GPIO_B, 0x00);  //Reset port B

    mcp.write(0);

    xSemaphoreGive(System::xI2C_semaphore);
  }else{
    LOG("[D]Int init Semaphore");ENDL;
  }

  setRGB(RED);
  vTaskDelay(200);
  setRGB(GREEN);
  vTaskDelay(200);
  setRGB(BLUE);
  vTaskDelay(200);
  setRGB(WHITE);
  vTaskDelay(200);  
  setRGB(OFF);

  xTaskCreatePinnedToCore(LedTask, "LedTask", 1024, NULL, 1, NULL, ARDUINO_RUNNING_CORE);

}


/////////////////////////////////////////////////////////////////////////////////
//                                Siren API                                    //
/////////////////////////////////////////////////////////////////////////////////

// Siren FreeRTOS task
void SirenTask( void *pvParameters ){
  (void) pvParameters;
  vTaskSuspend(NULL);
  for(;;){
    switch (Interface::sirenAction){
      case ALARM_OFF:
        break;
      case ALARM_SIREN:
        Interface::doBeeps(2,100,100);
        break;
      case ALARM_ERROR:
        Interface::doBeeps(5,20,50);
        break;  
      case ALARM_LOW_BATTERY:
        Interface::doBeeps(3,50,100);
      default:
        break;
    }
    vTaskDelay(1000);
  }
}

/* Actuate the buzzer with Delay */
void Interface::doBeeps(uint8_t times, uint16_t duration, uint16_t interval){
  uint8_t i = 0;
  for (i = 0; i < times; ++i) {
    digitalWrite(BUZZER, HIGH);
    vTaskDelay(duration);
    digitalWrite(BUZZER, LOW);
    vTaskDelay(interval);
  }
}

// Siren task control
void Interface::toggleSiren(){
  eTaskState state = eTaskGetState(sirenTask);
  if (state == 3){
    sirenState = true;
    Interface::sirenAction = ALARM_SIREN;
    vTaskResume(Interface::sirenTask);
  } else{
    Interface::sirenAction = ALARM_OFF;
    sirenState = false;
    digitalWrite(BUZZER, LOW);
    vTaskSuspend(Interface::sirenTask);
  }
}

// Check if should toggle LED flag is true and toggle it
void LedTask( void *pvParameters ){
  (void) pvParameters;
  for(;;){
    if(Interface::shouldChangeRGB){
      Interface::toggleRGB();
      Interface::shouldChangeRGB = false;
    }
    if(Interface::shouldChangeLed){
      Interface::toggleLed();
      Interface::shouldChangeLed = false;
    }
    vTaskDelay(100);
  }
}
// //--------------------------------------------------------------------------
// // RGB API
// //--------------------------------------------------------------------------

/* Actuate the RGB */
void Interface::setRGB(uint8_t color){
  if(xSemaphoreTake(System::xI2C_semaphore, TIME_TO_SEMAPHORE ) == pdTRUE){
    switch (color){
      case OFF: //All Off
        mcpState = mcp.read();
        mcpState &= ~(_BV(2) | _BV(3) | _BV(4) | _BV(5) | _BV(6) | _BV(7) | _BV(8) | _BV(9) | _BV(10) | _BV(11) | _BV(12) | _BV(13)); 
        mcp.write(mcpState);
        break;
      case RED: //All Red
        mcpState = mcp.read();
        mcpState &= ~(_BV(2) | _BV(3) | _BV(4) | _BV(5) | _BV(6) | _BV(7) | _BV(8) | _BV(9) | _BV(10) | _BV(11) | _BV(12) | _BV(13));
        mcpState |= (_BV(4) | _BV(7) | _BV(8) | _BV(11));
        mcp.write(mcpState);
        break;
      case GREEN: //All Green
        mcpState = mcp.read();
        mcpState &= ~(_BV(2) | _BV(3) | _BV(4) | _BV(5) | _BV(6) | _BV(7) | _BV(8) | _BV(9) | _BV(10) | _BV(11) | _BV(12) | _BV(13));
        mcpState |= (_BV(3) | _BV(6) | _BV(9) | _BV(12));
        mcp.write(mcpState);
        break;
      case BLUE: //All Blues
        mcpState = mcp.read();
        mcpState &= ~(_BV(2) | _BV(3) | _BV(4) | _BV(5) | _BV(6) | _BV(7) | _BV(8) | _BV(9) | _BV(10) | _BV(11) | _BV(12) | _BV(13));
        mcpState |= (_BV(2) | _BV(5) | _BV(10) | _BV(13));
        mcp.write(mcpState);
        break;
      case WHITE: //All White
        mcpState = mcp.read();
        mcpState &= ~(_BV(2) | _BV(3) | _BV(4) | _BV(5) | _BV(6) | _BV(7) | _BV(8) | _BV(9) | _BV(10) | _BV(11) | _BV(12) | _BV(13));
        mcpState |= (_BV(2) | _BV(3) | _BV(4) | _BV(5) | _BV(6) | _BV(7) | _BV(8) | _BV(9) | _BV(10) | _BV(11) | _BV(12) | _BV(13));
        mcp.write(mcpState);
        break;
      case PURPLE: //All Purple
        mcpState = mcp.read();
        mcpState &= ~(_BV(2) | _BV(3) | _BV(4) | _BV(5) | _BV(6) | _BV(7) | _BV(8) | _BV(9) | _BV(10) | _BV(11) | _BV(12) | _BV(13));
        mcpState |= (_BV(2) | _BV(4) | _BV(5) | _BV(7) | _BV(8) | _BV(10) | _BV(11) | _BV(13));
        mcp.write(mcpState);
        break;
      default:
        mcpState = mcp.read();
        mcp.write(mcpState);
        break;
    }
    xSemaphoreGive(System::xI2C_semaphore);
  }else{
    LOG("[D]RGB I2C Semaphore");ENDL;
  }
}

uint8_t rgbColor = RED;

void Interface::toggleRGB(){
  setRGB(rgbColor);
  rgbColor++;
  if (rgbColor > PURPLE){
    rgbColor = 0;
  }
}

uint8_t ledPosition = 1;

void Interface::toggleLed(){
  setLed(ledPosition);
  ledPosition++;
  if (ledPosition > L4){
    ledPosition = 0;
  }
}

void Interface::setLed(uint8_t number){
  if (xSemaphoreTake(System::xI2C_semaphore, TIME_TO_SEMAPHORE ) == pdTRUE){
    switch (number){
      case ALL_OFF: //All Off
        mcpState = mcp.read();
        mcpState &= ~(_BV(0) | _BV(1) | _BV(14) | _BV(15)); 
        mcp.write(mcpState);
        break;
      case L1: //White LED 1
        mcpState = mcp.read();
        mcpState |= (_BV(0));
        mcp.write(mcpState);
        break;
      case L2: //White LED 2
        mcpState = mcp.read();
        mcpState |= (_BV(1));
        mcp.write(mcpState);
        break;
      case L3: //White LED 3
        mcpState = mcp.read();
        mcpState |= (_BV(15));
        mcp.write(mcpState);
        break;
      case L4: //White LED 4
        mcpState = mcp.read();
        mcpState |= (_BV(14));
        mcp.write(mcpState);
        break;
      default: // Defaults to same as before
        mcpState = mcp.read();
        mcp.write(mcpState);
        break;
    }
    xSemaphoreGive(System::xI2C_semaphore);
  }else{
    LOG("[D]LED I2C Semaphore");ENDL;
  }
}

void Interface::setLed(uint8_t number, uint8_t state){
  if (xSemaphoreTake(System::xI2C_semaphore, TIME_TO_SEMAPHORE ) == pdTRUE){
    switch (number){
      case ALL_OFF: //All Off
        mcpState = mcp.read();
        mcpState &= ~(_BV(0) | _BV(1) | _BV(14) | _BV(15)); 
        mcp.write(mcpState);
        break;
      case L1: //White LED 1
        mcpState = mcp.read();
        if(state == HIGH)
          mcpState |= (_BV(0));
        else
          mcpState &= ~(_BV(0)); 
        mcp.write(mcpState);
        break;
      case L2: //White LED 2
        mcpState = mcp.read();
        if(state == HIGH)
          mcpState |= (_BV(1));
        else
          mcpState &= ~(_BV(1)); 
        mcp.write(mcpState);
        break;
      case L3: //White LED 3
        mcpState = mcp.read();
        if(state == HIGH)
          mcpState |= (_BV(15));
        else
          mcpState &= ~(_BV(15)); 
        mcp.write(mcpState);
        break;
      case L4: //White LED 4
        mcpState = mcp.read();
        if(state == HIGH)
          mcpState |= (_BV(14));
        else
          mcpState &= ~(_BV(14)); 
        mcp.write(mcpState);
        break;
      default: // Defaults to same as before
        mcpState = mcp.read();
        mcp.write(mcpState);
        break;
    }
    xSemaphoreGive(System::xI2C_semaphore);
  }else{
    LOG("[D]LED I2C Semaphore");ENDL;
  }
}