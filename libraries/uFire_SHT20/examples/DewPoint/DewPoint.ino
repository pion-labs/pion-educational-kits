#include "uFire_SHT20.h"
uFire_SHT20 sht20;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  sht20.begin();
}

void loop()
{
  Serial.println((String)sht20.dew_point() + "°C dew point");
  Serial.println((String)sht20.dew_pointF + "°F dew point");
  Serial.println();
  delay(5000);
}
