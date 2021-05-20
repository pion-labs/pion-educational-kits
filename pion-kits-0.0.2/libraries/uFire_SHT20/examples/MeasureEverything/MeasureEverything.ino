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
  sht20.measure_all();
  Serial.println((String)sht20.tempC + "°C");
  Serial.println((String)sht20.tempF + "°F");
  Serial.println((String)sht20.dew_pointC + "°C dew point");
  Serial.println((String)sht20.dew_pointF + "°F dew point");
  Serial.println((String)sht20.RH + " %RH");
  Serial.println((String)sht20.vpd() + " kPa VPD");
  Serial.println();
  delay(5000);
}
