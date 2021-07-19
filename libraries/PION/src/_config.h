#ifndef CONFIG_H
#define CONFIG_H

#include "Arduino.h"

#define FILE_BASE_NAME                "/Dados"

///////////// Make logging Easier
#define LOG                           Serial.print
#define ENDL                          LOG("\n\r")
#define SERIAL_SPEED                  115200

///// Constants
#define TIME_TO_SEMAPHORE             500

#define BAT_R1                        100000
#define BAT_R2                        100000
#define BAT_DROP                      0.12
#define VBAT_VOLTAGE(adc)             (adc / (4096 / 3.3)) * (BAT_R1 + BAT_R2) * (1.0 / BAT_R2) + BAT_DROP

// Inputs
#define BAT_SENSOR                    35
#define LIGHT_SENSOR                  34

// Outputs
#define BUZZER                        25

// SD Hardware Pins
#define PIN_SD_SS                     15

// I2C Addresses
#define BMP280_ADDRESS                0x76
#define MPU9250_ADDRESS               0x68
#define MCP23017_ADDR                 0x20

// Corrections
#define TEMPERATURE_CORRECTION        13.0

// FreeRTOS Core Definition
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#endif