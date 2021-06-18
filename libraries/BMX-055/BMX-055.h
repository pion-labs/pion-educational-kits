/*!
 *  @file BMX-055.h
 *
 *  This is a library for the BMX055 Inertial Measurement Unit
 *
 *  These sensors use I2C to communicate, 2 pins are required to interface.
 *
 *  João Pedro Vilas (github.com/joaopedrovbs)
 *
 *  MIT license, all text above must be included in any redistribution
 */

#ifndef __ADAFRUIT_BMX055_H__
#define __ADAFRUIT_BMX055_H__

#include "Arduino.h"
#include <Wire.h>

// BMX055 default I2C addresses
#define BMX055_ACCEL_DEFAULT_ADDRESS  0x18
#define BMX055_GYRO_DEFAULT_ADDRESS   0x68
#define BMX055_MAG_DEFAULT_ADDRESS    0x10

/** BMX055 ID **/
#define BMX055_ACCEL_ID       0xFA
#define BMX055_GYRO_ID        0x0F
#define BMX055_MAG_ID         0x32

class BMX055 {
  public:

    /* BMX055 object, input the I2C bus and addresses */
    BMX055(TwoWire &bus, uint8_t, uint8_t, uint8_t);

    int begin(void);


    typedef enum {
      NORMAL_MODE,      //  All parts held powered-up and data acquisition is performed continuosly
      DEEP_SUSPEND,     //  Only interface Section is kept alive. No Data Acquisition is performed
      SUSPEND_MODE,     //  The whole analog part is powered down. No Data Acquisition is performed 
                        //  there are some restriction to writing and reading (wait for some time)
      STANDBY_MODE,     //  Same as suspend but without restrictions
      LOW_POWER_MODE_1, //  Device periodically switches between a sleep(suspend mode) and a wake-up phase(normal mode)
      LOW_POWER_MODE_2, //  Similar to mode 1 but register access can happen anytime without restrictions
    }BMX055_ACCEL_POWER_MODES_t;
    
    typedef enum{
      MS_0_5  =0x05,
      MS_1    =0x06,
      MS_2    =0x07,
      MS_4    =0x08,
      MS_6    =0x09,
      MS_10   =0x0A,
      MS_25   =0x0B,
      MS_50   =0x0C,
      MS_100  =0x0D,
      MS_500  =0x0E,
      MS_1000 =0x0F,
    }BMX_ACCEL_SLEEP_DUR_t;

    enum{
      FILTERED = 0,
      UNFILTERED,
    }BMX_ACCEL_DATA_STREAM_t;

    typedef enum{
      HZ_7_81   =0x08,
      HZ_15_63  =0x09,
      HZ_31_25  =0x0A,
      HZ_62_5   =0x0B,
      HZ_125    =0x0C,
      HZ_250    =0x0D,
      HZ_500    =0x0E,
      HZ_1000   =0x10,
    }BMX_ACCEL_DATA_BANDWIDTH_t;

    typedef enum{ 
      ACCEL_RANGE_2G    =0x03,
      ACCEL_RANGE_4G    =0x05,
      ACCEL_RANGE_8G    =0x08,
      ACCEL_RANGE_16G   =0x0C
    }BMX055_ACCEL_RANGE_t;

    typedef enum {
      GYRO_NORMAL_MODE       =0x00,      
      GYRO_DEEP_SUSPEND_MODE =0x20,
      GYRO_SUSPEND_MODE      =0x80,
    }BMX055_GYRO_POWER_MODES_t;

    typedef enum{
      GYRO_2_MS    =0x00,
      GYRO_4_MS    =0x01,
      GYRO_5_MS    =0x02,
      GYRO_8_MS    =0x03,
      GYRO_10_MS   =0x04,
      GYRO_15_MS   =0x05,
      GYRO_18_MS   =0x06,
      GYRO_20_MS   =0x07,
    }BMX_GYRO_SLEEP_DUR_t;

    typedef enum{ 
      GYRO_RANGE_2000   =0x00,
      GYRO_RANGE_1000   =0x01,
      GYRO_RANGE_500    =0x02,
      GYRO_RANGE_250    =0x03,
      GYRO_RANGE_125    =0x04
    }BMX055_GYRO_RANGE_t;

    typedef enum{
      ODR_100_BDW_32    =0x07,
      ODR_200_BDW_64    =0x06,
      ODR_100_BDW_12    =0x05,
      ODR_200_BDW_23    =0x04,
      ODR_400_BDW_47    =0x03,
      ODR_1000_BDW_116  =0x02,
      ODR_2000_BDW_230  =0x01,
      ODR_2000_BDW_523  =0x00,
    }BMX_GYRO_DATA_BANDWIDTH_t;

    bool setAccelRange(BMX055_ACCEL_RANGE_t);

    bool setAccelBandwidth(BMX_ACCEL_DATA_BANDWIDTH_t);

    bool setAccelSleepPeriod(BMX_ACCEL_SLEEP_DUR_t);

    void readAccel(void);

    float getAccelX_mss();
    float getAccelY_mss();
    float getAccelZ_mss();

    bool setGyroRange(BMX055_GYRO_RANGE_t);

    bool setGyroBandwidth(BMX_GYRO_DATA_BANDWIDTH_t);

    bool setGyroPowerMode(BMX055_GYRO_POWER_MODES_t,BMX_GYRO_SLEEP_DUR_t);

    void readGyro(void);

    float getGyroX_degs();
    float getGyroY_degs();
    float getGyroZ_degs();

    bool setMagOn(void);

    bool setMagODR(void);

    bool enableMagAxis(void);

    bool setMagRepetition(void);

    void readMag(void);

    float getMagX_uT();
    float getMagY_uT();
    float getMagZ_uT();

  private:
    /** BMX055 Registers **/
    typedef enum {
      BGW_CHIPID    =0x00,
      ACCD_X_LSB    =0x02,
      ACCD_X_MSB    =0x03,
      ACCD_Y_LSB    =0x04,
      ACCD_Y_MSB    =0x05,
      ACCD_Z_LSB    =0x06,
      ACCD_Z_MSB    =0x07,
      ACCD_TEMP     =0x08,
      INT_STATUS_0  =0x09,
      INT_STATUS_1  =0x0A,
      INT_STATUS_2  =0x0B,
      INT_STATUS_3  =0x0C,
      FIFO_STATUS   =0x0E,
      PMU_RANGE     =0x0F,
      PMU_BW        =0x10,
      PMU_LPW       =0x11,
      PMU_LOW_POWER =0x12,
      ACCD_HBW      =0x13,
      BGW_SOFTRESET =0x14,
      INT_EN_0      =0x16,
      INT_EN_1      =0x17,
      INT_EN_2      =0x18,
      INT_MAP_0     =0x19,
      INT_MAP_1     =0x1A,
      INT_MAP_2     =0x1B,
      INT_SRC       =0x1E,
      INT_OUT_CTRL  =0x20,
      INT_RST_LATCH =0x21,
      INT_0         =0x22,
      INT_1         =0x23,
      INT_2         =0x24,
      INT_3         =0x25,
      INT_4         =0x26,
      INT_5         =0x27,
      INT_6         =0x28,
      INT_7         =0x29,
      INT_8         =0x2A,
      INT_9         =0x2B,
      INT_A         =0x2C,
      INT_B         =0x2D,
      INT_C         =0x2E,
      INT_D         =0x2F,
      FIFO_CONFIG_0 =0x30,
      PMU_SELF_TEST =0x32,
      TRIM_NVM_CTRL =0x33,
      BGW_SPI3_WDT  =0x34,
      OFC_CTRL      =0x36,
      OFC_SETTING   =0x37,
      OFC_OFFSET_X  =0x38,
      OFC_OFFSET_Y  =0x39,
      OFC_OFFSET_Z  =0x3A,
      TRIM_GP0      =0x3B,
      TRIM_GP1      =0x3C,
      FIFO_CONFIG_1 =0x3E,
      FIFO_DATA     =0x3F,
    }BMX055_Accel_reg_t;

    typedef enum{
      GYR_CHIP_ID       =0x00,
      GYR_RATE_X_LSB    =0x02,
      GYR_RATE_X_MSB    =0x03,
      GYR_RATE_Y_LSB    =0x04,
      GYR_RATE_Y_MSB    =0x05,
      GYR_RATE_Z_LSB    =0x06,
      GYR_RATE_Z_MSB    =0x07,
      GYR_INT_STATUS_0  =0x09,
      GYR_INT_STATUS_1  =0x0A,
      GYR_INT_STATUS_2  =0x0B,
      GYR_INT_STATUS_3  =0x0C,
      GYR_FIFO_STATUS   =0x0E,
      GYR_RANGE         =0x0F,
      GYR_BW            =0x10,
      GYR_LPM1          =0x11,
      GYR_LPM2          =0x12,
      GYR_RATE_HBW      =0x13,
      GYR_BGW_SOFTRESET =0x14,
      GYR_INT_EN_0      =0x15,
      GYR_INT_EN_1      =0x16,
      GYR_INT_MAP_0     =0x17,
      GYR_INT_MAP_1     =0x18,
      GYR_INT_MAP_2     =0x19,
      GYR_INT_DATA_SRC  =0x1A,
      GYR_FOC_DATA_SRC  =0x1B,
      GYR_ANY_MOTION    =0x1C,
      GYR_FIFO_WATER_MK =0x1E,
      GYR_INT_RST_LATCH =0x21,
      GYR_HIGH_TH_X     =0x22,
      GYR_HIGH_DUR_X    =0x23,
      GYR_HIGH_TH_Y     =0x24,
      GYR_HIGH_DUR_Y    =0x25,
      GYR_HIGH_TH_Z     =0x26,
      GYR_HIGH_DUR_Z    =0x27,
      GYR_SOC           =0x31,
      GYR_A_FOC         =0x32,
      GYR_TRIM_NVM_CTRL =0x33,
      GYR_BGW_SPI3_WDT  =0x34,
      GYR_OFC1          =0x36,
      GYR_OFC2          =0x37,
      GYR_OFC3          =0x38,
      GYR_OFC4          =0x39,
      GYR_TRIM_GP0      =0x3A,
      GYR_TRIM_GP1      =0x3B,
      GYR_BIST          =0x3C,
      GYR_FIFO_CONFIG_0 =0x3D,
      GYR_FIFO_CONFIG_1 =0x3E,
      GYR_FIFO_DATA     =0x3F,
    }BMX055_Gyro_reg_t;

    typedef enum{
      MAG_CHIP_ID       =0x40,
      MAG_X_LSB         =0x42,
      MAG_X_MSB         =0x43,
      MAG_Y_LSB         =0x44,
      MAG_Y_MSB         =0x45,
      MAG_Z_LSB         =0x46,
      MAG_Z_MSB         =0x47,
      MAG_RHALL_LSB_DRDY=0x48,
      MAG_RHALL_MSB_DRDY=0x49,
      MAG_INT_STATUS    =0x4A,
      MAG_PWR_CTRL_SR   =0x4B,
      MAG_OM_ODR_SELF   =0x4C,
      MAG_INT_REG_0     =0x4D,
      MAG_INT_REG_1     =0x4E,
      MAG_LOW_TH_INT    =0x4F,
      MAG_HIGH_TH_INT   =0x50,
      MAG_REP_CTRL_XY   =0x51,
      MAG_REP_CTRL_Z    =0x52,
    }BMX055_Mag_reg_t;
    
    // i2c
    TwoWire *_i2c;
    const uint32_t _i2cRate = 400000; // 400 kHz
    
    uint8_t _accelAddress;
    uint8_t _gyroAddress;
    uint8_t _magAddress;

    BMX055_ACCEL_RANGE_t accelRangeBuffer;
    BMX055_GYRO_RANGE_t gyroRangeBuffer;
    
    float _ax, _ay, _az;
    float _gx, _gy, _gz;
    float _mx, _my, _mz;

    const float G = 9.807f;

    bool writeAccelRegister(BMX055_Accel_reg_t , uint8_t);
    uint8_t readAccelRegisters(BMX055_Accel_reg_t);

    bool writeGyroRegister(BMX055_Gyro_reg_t, uint8_t data);
    uint8_t readGyroRegisters(BMX055_Gyro_reg_t);

    bool writeMagRegister(BMX055_Mag_reg_t, uint8_t data);
    uint8_t readMagRegisters(BMX055_Mag_reg_t);
};

#endif