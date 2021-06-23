#include "PION_System.h"
#include "WiFi.h"

/* 
  Esse código demonstra como modificar o funcionamento da WiFi do seu kit para
  que ele se conecte a uma WiFi que pode ser modificado abaixo em WiFi.begin(ssid, password);
*/

System cubeSat;

// Modificação para conectar a uma wifi
void networkConnect(){
  // Para qualquer aplicação bluetooth que possa existir
  btStop();

  // Começa WiFi se conectando ao SSID fornecido com a senha fornecida
  WiFi.begin("NomeDaSuaWiFi", "senhadaSuaWiFi");
  
  // Espera o Status de conectado
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Exibe via serial o endereço IP do seu kit na rede 
  Serial.println("");
  Serial.println("WiFi conectada");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup(){
  // Inicializa seu CubeSat, e seus periféricos 
  cubeSat.init();
}

void loop(){
  cubeSat.setRGB(BLUE);
  delay(1000);
  cubeSat.setRGB(OFF);
  delay(1000);
}