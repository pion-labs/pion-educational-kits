#ifndef TYPES_H
#define TYPES_H

  typedef enum{
    ALARM_OFF,
    ALARM_SIREN,
    ALARM_ERROR,
    ALARM_LOW_BATTERY,
  } SirenState_t;

  typedef enum{
    INIT_OK = 0,
    ERROR_BMP280,
    ERROR_SHT20,
    ERROR_MPU9250,
    ERROR_CCS811,
  } InitStatus_t;

  typedef enum{
    NO_SD = 0,
    SD_CONNECTED,
    SD_RECORDING,
    SD_ERROR,
  } SDStatus_t;


  enum Colors{
    OFF = 0,
    RED,
    GREEN,
    BLUE,
    WHITE,
    PURPLE
  };

  enum LED{
    ALL_OFF = 0,
    L1,
    L2,
    L3,
    L4,
    ALL
  };

#endif