#include "Arduino.h"
#include "BMX-055.h"

/* BMX055 object, input the I2C bus and address */
BMX055::BMX055(
  TwoWire &bus, 
  uint8_t addressAccel, 
  uint8_t addressGyro, 
  uint8_t addressMag){
  _i2c = &bus; // I2C bus
  _accelAddress = addressAccel; // I2C Accel Address
  _gyroAddress = addressGyro;   // I2C Gyro Address
  _magAddress = addressMag;     // I2C Mag Address
}

/* starts communication with the BMX055 */
int BMX055::begin(){
    // starting the I2C bus
    _i2c->begin();
    // setting the I2C clock
    _i2c->setClock(_i2cRate);

    if(!(readAccelRegisters(BGW_CHIPID) == BMX055_ACCEL_ID)){
      return -1;
    }

    if(!setAccelRange(ACCEL_RANGE_8G)){
      return -2;
    }

    if(!setAccelBandwidth(HZ_7_81)){
      return -3;
    }

    if(!setAccelSleepPeriod(MS_1)){
      return -4;
    }

    delay(100);

    if(!(readGyroRegisters(GYR_CHIP_ID) == BMX055_GYRO_ID)){
      return -5;
    }

    if(!setGyroRange(GYRO_RANGE_1000)){
      return -6;
    }

    if(!setGyroBandwidth(ODR_100_BDW_12)){
      return -7;
    }

    if(!setGyroPowerMode(GYRO_NORMAL_MODE, GYRO_2_MS)){
      return -8;
    }

    if(!setMagOn()){
      return -9;
    }

    if(!setMagODR()){
      return -10;
    }

    if(!enableMagAxis()){
      return -11;
    }
    
    if(!setMagRepetition()){
      return -12;
    }

  // successful init, return 1
  return 1;
}

// Sets the range for accelerometer measurements
bool BMX055::setAccelRange(BMX055_ACCEL_RANGE_t range){
  accelRangeBuffer = range;
  if(!writeAccelRegister(PMU_RANGE, range)){
    return false;
  }
  return true;
}

// Sets the Bandwidth for the Low Pass Filter
bool BMX055::setAccelBandwidth(BMX_ACCEL_DATA_BANDWIDTH_t bandwidth){
  if(!writeAccelRegister(PMU_BW, bandwidth)){
    return false;
  }
  return true;
}

// Sets the duration of the sleep period during 
bool BMX055::setAccelSleepPeriod(BMX_ACCEL_SLEEP_DUR_t duration){
  if(!writeAccelRegister(PMU_LPW, duration)){
    return false;
  }
  return true;
}

// Performs accelerometer read and conversion
void BMX055::readAccel(void){
  // Buffers for raw 8-bit data
  uint8_t xRawData[2];
  uint8_t yRawData[2];
  uint8_t zRawData[2];
  
  // Reading registers
  xRawData[0] = readAccelRegisters(ACCD_X_LSB);
  xRawData[1] = readAccelRegisters(ACCD_X_MSB);
  
   // Reading registers
  yRawData[0] = readAccelRegisters(ACCD_Y_LSB);
  yRawData[1] = readAccelRegisters(ACCD_Y_MSB);

   // Reading registers
  zRawData[0] = readAccelRegisters(ACCD_Z_LSB);
  zRawData[1] = readAccelRegisters(ACCD_Z_MSB);

  // Converting registers to 12 bit variables
  int16_t accelX12Bit = (( (xRawData[1] << 8) | (xRawData[0] & 0xF0) ) >> 4);
  int16_t accelY12Bit = (( (yRawData[1] << 8) | (yRawData[0] & 0xF0) ) >> 4);
  int16_t accelZ12Bit = (( (zRawData[1] << 8) | (zRawData[0] & 0xF0) ) >> 4);

  // Convert data into a + and - range
  if (accelX12Bit > 2047)
  {
    accelX12Bit -= 4096;
  }
   // Convert data into a + and - range
  if (accelY12Bit > 2047)
  {
    accelY12Bit -= 4096;
  }
   // Convert data into a + and - range
  if (accelZ12Bit > 2047)
  {
    accelZ12Bit -= 4096;
  }

  uint16_t divider = 1;

  // Sensitivity Scale from the datasheet
  if (accelRangeBuffer == ACCEL_RANGE_2G)
    divider = 1024;
  else if (accelRangeBuffer == ACCEL_RANGE_4G)
    divider = 512;
  else if (accelRangeBuffer == ACCEL_RANGE_8G)
    divider = 256;
  else if (accelRangeBuffer == ACCEL_RANGE_16G)
    divider = 128;

  // Save to local values
  _ax = (float)accelX12Bit/divider;
  _ay = (float)accelY12Bit/divider;
  _az = (float)accelZ12Bit/divider;

}

// returns the accelerometer measurement in the x direction, m/s^2 
float BMX055::getAccelX_mss(void){
  return _ax*G;
}
// returns the accelerometer measurement in the y direction, m/s^2 
float BMX055::getAccelY_mss(void){
  return _ay*G;
}
// returns the accelerometer measurement in the z direction, m/s^2 
float BMX055::getAccelZ_mss(void){
  return _az*G;
}

// Gyro

bool BMX055::setGyroRange(BMX055_GYRO_RANGE_t range){
  gyroRangeBuffer = range;
  if(!writeGyroRegister(GYR_RANGE, range)){
    return false;
  }
  return true;
}

bool BMX055::setGyroBandwidth(BMX_GYRO_DATA_BANDWIDTH_t bandwidth){
  if(!writeGyroRegister(GYR_BW, bandwidth)){
    return false;
  }
  return true;
}

bool BMX055::setGyroPowerMode(BMX055_GYRO_POWER_MODES_t powerMode, BMX_GYRO_SLEEP_DUR_t sleepDuration){
  if(!writeGyroRegister(GYR_LPM1, (powerMode | sleepDuration))){
    return false;
  }
    return true;
}

void BMX055::readGyro(void){
    // Buffers for raw 8-bit data
  uint8_t xRawData[2];
  uint8_t yRawData[2];
  uint8_t zRawData[2];
  
  // Reading registers
  xRawData[0] = readGyroRegisters(GYR_RATE_X_LSB);
  xRawData[1] = readGyroRegisters(GYR_RATE_X_MSB);
  
   // Reading registers
  yRawData[0] = readGyroRegisters(GYR_RATE_Y_LSB);
  yRawData[1] = readGyroRegisters(GYR_RATE_Y_MSB);

   // Reading registers
  zRawData[0] = readGyroRegisters(GYR_RATE_Z_LSB);
  zRawData[1] = readGyroRegisters(GYR_RATE_Z_MSB);

  // Converting registers to 12 bit variables
  int32_t gyroX = ((xRawData[1] << 8) | (xRawData[0]));
  int32_t gyroY = ((yRawData[1] << 8) | (yRawData[0]));
  int32_t gyroZ = ((zRawData[1] << 8) | (zRawData[0]));

  // Convert data into a + and - range
  if (gyroX > 32767)
  {
    gyroX -= 65536;
  }
   // Convert data into a + and - range
  if (gyroY > 32767)
  {
    gyroY -= 65536;
  }
   // Convert data into a + and - range
  if (gyroZ > 32767)
  {
    gyroZ -= 65536;
  }

  float divider = 1;

  // Sensitivity Scale from the datasheet
  if (gyroRangeBuffer == GYRO_RANGE_125)
    divider = 262.4;
  else if (gyroRangeBuffer == GYRO_RANGE_250)
    divider = 131.2;
  else if (gyroRangeBuffer == GYRO_RANGE_500)
    divider = 65.6;
  else if (gyroRangeBuffer == GYRO_RANGE_1000)
    divider = 32.8;
  else if (gyroRangeBuffer == GYRO_RANGE_2000)
    divider = 16.4;

  // Save to local values
  _gx = (float)gyroX/divider;
  _gy = (float)gyroY/divider;
  _gz = (float)gyroZ/divider;

}

float BMX055::getGyroX_degs(){
  return _gx;
}
float BMX055::getGyroY_degs(){
  return _gy;
}
float BMX055::getGyroZ_degs(){
  return _gz;
}

// Magnetometer

bool BMX055::setMagOn(void){
  if(!writeMagRegister(MAG_PWR_CTRL_SR, 0x83)){
    return false;
  }
  return true;
}

bool BMX055::setMagODR(void){
  if(!writeMagRegister(MAG_OM_ODR_SELF, 0x00)){
    return false;
  }
  return true;
}

bool BMX055::enableMagAxis(void){
  if(!writeMagRegister(MAG_INT_REG_1, 0x84)){
    return false;
  }
    return true;
}

bool BMX055::setMagRepetition(void){
  if(!writeMagRegister(MAG_REP_CTRL_XY, 0x0F)){
    return false;
  }
  if(!writeMagRegister(MAG_REP_CTRL_Z, 0x0F)){
    return false;
  }
    return true;
}

void BMX055::readMag(void){
    // Buffers for raw 8-bit data
  uint8_t xRawData[2];
  uint8_t yRawData[2];
  uint8_t zRawData[2];
  
  // Reading registers
  xRawData[0] = readMagRegisters(MAG_X_LSB);
  xRawData[1] = readMagRegisters(MAG_X_MSB);
  
   // Reading registers
  yRawData[0] = readMagRegisters(MAG_Y_LSB);
  yRawData[1] = readMagRegisters(MAG_Y_MSB);

   // Reading registers
  zRawData[0] = readMagRegisters(MAG_Z_LSB);
  zRawData[1] = readMagRegisters(MAG_Z_MSB);

  // Converting registers to 12 bit variables
  int16_t magX = (((xRawData[1] << 8) | (xRawData[0] & 0xF8) ) >> 3);
  int16_t magY = (((yRawData[1] << 8) | (xRawData[0] & 0xF8) ) >> 3);
  int16_t magZ = (((zRawData[1] << 8) | (xRawData[0] & 0xFE) ) >> 1);

  // Convert data into a + and - range
  if (magX > 4095)
  {
    magX -= 8192;
  }
   // Convert data into a + and - range
  if (magY > 4095)
  {
    magY -= 8192;
  }
   // Convert data into a + and - range
  if (magZ > 16383)
  {
    magZ -= 32768;
  }

  float divider = 16;

  // Save to local values
  _mx = (float)magX/divider;
  _my = (float)magY/divider;
  _mz = (float)magZ/divider;

}

float BMX055::getMagX_uT(){
  return _mx;
}
float BMX055::getMagY_uT(){
  return _my;
}
float BMX055::getMagZ_uT(){
  return _mz;
}

// Private Functions

/* writes a byte to BMX055 Accelerometer register given a register address and data */
bool BMX055::writeAccelRegister(BMX055_Accel_reg_t regAddress, uint8_t data){
  /* write data to device */
  _i2c->beginTransmission((uint8_t)_accelAddress); // open the device
  _i2c->write((uint8_t)regAddress); // write the register address
  _i2c->write((uint8_t)data); // write the data
  _i2c->endTransmission();

  /* check the read back register against the written register */
  if(readAccelRegisters(regAddress) == data) {
    return true;
  }
  return false;
}

/* reads registers from BMX055 Accelerometer given a starting register address, number of bytes, and a pointer to store data */
uint8_t BMX055::readAccelRegisters(BMX055_Accel_reg_t regAddress){
  _i2c->beginTransmission((uint8_t)_accelAddress); // open the device
  _i2c->write((uint8_t)regAddress); // specify the starting register address
  _i2c->endTransmission(false);
  _i2c->requestFrom((int)_accelAddress, (int)1); // specify the number of bytes to receive
  return _i2c->read();
}

//////////////////////////////////////
// Gyro 
//////////////////////////////////////

/* writes a byte to BMX055 register given a register address and data */
bool BMX055::writeGyroRegister(BMX055_Gyro_reg_t regAddress, uint8_t data){
  /* write data to device */
  _i2c->beginTransmission(_gyroAddress); // open the device
  _i2c->write((uint8_t)regAddress); // write the register address
  _i2c->write(data); // write the data
  _i2c->endTransmission();

  return true;
}

/* reads registers from BMX055 given a starting register address, number of bytes, and a pointer to store data */
uint8_t BMX055::readGyroRegisters(BMX055_Gyro_reg_t regAddress){
  _i2c->beginTransmission(_gyroAddress); // open the device
  _i2c->write((uint8_t)regAddress); // specify the starting register address
  _i2c->endTransmission(false);
  _i2c->requestFrom((int)_gyroAddress, (int)1); // specify the number of bytes to receive
  return (_i2c->read());
}

//////////////////////////////////////
// Mag
//////////////////////////////////////

/* writes a byte to BMX055 register given a register address and data */
bool BMX055::writeMagRegister(BMX055_Mag_reg_t regAddress, uint8_t data){
  /* write data to device */
  _i2c->beginTransmission((uint8_t)_magAddress); // open the device
  _i2c->write((uint8_t)regAddress); // write the register address
  _i2c->write(data); // write the data
  _i2c->endTransmission();

  return true;
}

/* reads registers from BMX055 given a starting register address, number of bytes, and a pointer to store data */
uint8_t BMX055::readMagRegisters(BMX055_Mag_reg_t regAddress){
  _i2c->beginTransmission((uint8_t)_magAddress); // open the device
  _i2c->write((uint8_t)regAddress); // specify the starting register address
  _i2c->endTransmission(false);
  _i2c->requestFrom((int)_magAddress, (int)1); // specify the number of bytes to receive
  return _i2c->read();
}
