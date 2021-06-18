#include "PION_System.h"

System canSat;

void setup(){
  // Inicializa seu CanSat, e a serial    
  canSat.init();
}

void loop(){
  // Realizando a Leitura de temperatura
  Serial.print("Temperatura: ");
  Serial.print(canSat.getTemperature());
  Serial.println(" °C");

  // Realizando a Leitura de umidade
  Serial.print("Umidade: ");
  Serial.print(canSat.getHumidity());
  Serial.println(" %HR");
  
  // Realizando a Leitura de pressão
  Serial.print("Pressão: ");
  Serial.print(canSat.getPressure());
  Serial.println(" pa");
  
  // Realizando a Leitura do Nível de CO2 
  Serial.print("Nível de CO2: ");
  Serial.print(canSat.getCO2Level());
  Serial.println(" ppm");
  
  // Realizando a Leitura de luminosidade
  Serial.print("Luminosidade: ");
  Serial.print(canSat.getLuminosity());
  Serial.println(" %");
  
  // Realizando a Leitura do Acelerometro
  Serial.print("Acelerometro X | Y | Z : ");
  Serial.print(canSat.getAccelerometer(0));
  Serial.print(" m/s^2 | ");
  Serial.print(canSat.getAccelerometer(1));
  Serial.print(" m/s^2 | ");
  Serial.print(canSat.getAccelerometer(2));
  Serial.println(" m/s^2");
  
  // Realizando a Leitura do Giroscopio
  Serial.print("Giroscopio X | Y | Z : ");
  Serial.print(canSat.getGyroscope(0));
  Serial.print(" graus/s | ");
  Serial.print(canSat.getGyroscope(1));
  Serial.print(" graus/s | ");
  Serial.print(canSat.getGyroscope(2));
  Serial.println(" graus/s");
  
  // Realizando a Leitura do Magnetometro
  Serial.print("Magnetometro X | Y | Z : ");
  Serial.print(canSat.getMagnetometer(0));
  Serial.print(" uT | ");
  Serial.print(canSat.getMagnetometer(1));
  Serial.print(" uT | ");
  Serial.print(canSat.getMagnetometer(2));
  Serial.println(" uT");
  
  delay(1000);
}