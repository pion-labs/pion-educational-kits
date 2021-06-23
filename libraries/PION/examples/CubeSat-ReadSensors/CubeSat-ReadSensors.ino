#include "PION_System.h"

/* 
  Esse código demonstra como obter os dados dos sensores do seu kit
*/

System cubeSat;

void setup(){
  // Inicializa seu cubeSat, e seus periféricos 
  cubeSat.init();
}

void loop(){
  // Realizando a Leitura de temperatura
  Serial.print("Temperatura: ");
  Serial.print(cubeSat.getTemperature());
  Serial.println(" °C");

  // Realizando a Leitura de umidade
  Serial.print("Umidade: ");
  Serial.print(cubeSat.getHumidity());
  Serial.println(" %HR");
  
  // Realizando a Leitura de pressão
  Serial.print("Pressão: ");
  Serial.print(cubeSat.getPressure());
  Serial.println(" pa");
  
  // Realizando a Leitura do Nível de CO2 
  Serial.print("Nível de CO2: ");
  Serial.print(cubeSat.getCO2Level());
  Serial.println(" ppm");
  
  // Realizando a Leitura de luminosidade
  Serial.print("Luminosidade: ");
  Serial.print(cubeSat.getLuminosity());
  Serial.println(" %");
  
  // Realizando a Leitura do Acelerometro
  Serial.print("Acelerometro X | Y | Z : ");
  Serial.print(cubeSat.getAccelerometer(0));
  Serial.print(" m/s^2 | ");
  Serial.print(cubeSat.getAccelerometer(1));
  Serial.print(" m/s^2 | ");
  Serial.print(cubeSat.getAccelerometer(2));
  Serial.println(" m/s^2");
  
  // Realizando a Leitura do Giroscopio
  Serial.print("Giroscopio X | Y | Z : ");
  Serial.print(cubeSat.getGyroscope(0));
  Serial.print(" graus/s | ");
  Serial.print(cubeSat.getGyroscope(1));
  Serial.print(" graus/s | ");
  Serial.print(cubeSat.getGyroscope(2));
  Serial.println(" graus/s");
  
  // Realizando a Leitura do Magnetometro
  Serial.print("Magnetometro X | Y | Z : ");
  Serial.print(cubeSat.getMagnetometer(0));
  Serial.print(" uT | ");
  Serial.print(cubeSat.getMagnetometer(1));
  Serial.print(" uT | ");
  Serial.print(cubeSat.getMagnetometer(2));
  Serial.println(" uT");
  
  delay(1000);
}