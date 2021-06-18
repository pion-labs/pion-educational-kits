#include "BMX-055.h"

BMX055 bmx(Wire,BMX055_ACCEL_DEFAULT_ADDRESS,BMX055_GYRO_DEFAULT_ADDRESS,BMX055_MAG_DEFAULT_ADDRESS);

void setup() {
  
  Serial.begin(115200);

  Serial.println("BMX055 Initialization: ");
  
  int status = bmx.begin();
  if(status != 1){
    Serial.print("Error code: "); Serial.println(status);
  }

  Serial.println("BMP Init OK");
}

void loop() {
  // put your main code here, to run repeatedly:
  bmx.readAccel();

  Serial.print("Accel: ");
  Serial.print("X ");
  Serial.print(bmx.getAccelX_mss());
  Serial.print(" Y ");
  Serial.print(bmx.getAccelY_mss());
  Serial.print(" Z ");
  Serial.println(bmx.getAccelZ_mss());

  bmx.readGyro();

  Serial.print("Gyro: ");
  Serial.print("X ");
  Serial.print(bmx.getGyroX_degs());
  Serial.print(" Y ");
  Serial.print(bmx.getGyroY_degs());
  Serial.print(" Z ");
  Serial.println(bmx.getGyroZ_degs());
  
  bmx.readMag();

  Serial.print("Mag: ");
  Serial.print("X ");
  Serial.print(bmx.getMagX_uT());
  Serial.print(" Y ");
  Serial.print(bmx.getMagY_uT());
  Serial.print(" Z ");
  Serial.println(bmx.getMagZ_uT());

  delay(200);
}
