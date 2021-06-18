#include <Arduino.h>

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "_config.h"
#include "_types.h"

#include "webpage.h"

#include "PION_System.h"
#include "PION_Network.h"
#include "PION_Sensors.h"
#include "PION_Storage.h"
#include "PION_Interface.h"

// External Objects
AsyncWebServer server(80);

char ssidId[32];                          // Final ssid buffer
uint32_t chipId;                          // chipId Holder
String baseName = "PION Satélite ";       // WiFi Base SSID to have the id string added
const char* password = "meusatpion";      // Default WiFi Password

TaskHandle_t Network::netTask;

void sendDataWs();
void NetworkTask(void *pvParameters);
void onEvent(AsyncWebSocket *, AsyncWebSocketClient *, AwsEventType , void *, uint8_t *, size_t );

AsyncWebSocket ws("/ws");

const char* sdStatusMessage[] = {"NO_SD","SD_CONNECTED","SD_RECORDING","SD_ERROR"};
const char* sirenMessage[] = {"ALARM_OFF","ALARM_SIREN","ALARM_ERROR","ALARM_LOW_BATTERY"};

__attribute__((weak)) void networkConnect(){

  // Transforms serial number into a string
  String id = String(System::getSerialNumber());

  // Create new string with
  String ssidTest = baseName + id;

  // Stores string into char buffer
  ssidTest.toCharArray(ssidId, sizeof(ssidId));

  btStop();

  // Starts WiFi Access Poinnt with custom ssid + id and default password
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssidId, password);
  WiFi.setHostname("PION Satelite");

}

__attribute__((weak)) void serverResponse(){
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    // Send File
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", DASH_HTML, DASH_HTML_SIZE);
    response->addHeader("Content-Encoding","gzip");
    request->send(response);
  });
}

void Network::init(){

  networkConnect();

  serverResponse();

  ws.onEvent(onEvent);
  server.addHandler(&ws);

  // Start Web Server
  server.begin(); 

  xTaskCreatePinnedToCore(NetworkTask, "NetworkTask", 8192, NULL, 1, &Network::netTask, ARDUINO_RUNNING_CORE);

}

void Network::deInit(){
  vTaskSuspend(Network::netTask);
  // server.reset();
  server.end();
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void NetworkTask(void *pvParameters){
  (void) pvParameters;

  for (;;){
    sendDataWs();
    vTaskDelay(1000);
  }
}

__attribute__((weak)) void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if (strcmp((char*)data, "toggleRGB") == 0) {
      Interface::shouldChangeRGB = true;
    } else if (strcmp((char*)data, "toggleLED") == 0) {
      Interface::shouldChangeLed = true;
    } else if (strcmp((char*)data, "toggleSiren") == 0) {
      Interface::toggleSiren();
    } else if (strcmp((char*)data, "toggleSD1") == 0) {
      Storage::toggleSD(0);
    } else if (strcmp((char*)data, "toggleSD2") == 0) {
      Storage::toggleSD(1);
    } else if (strcmp((char*)data, "reboot") == 0) {
      ESP.restart();
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket cliente #%u conectado do %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket cliente #%u desconectado\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    default:
      break;
  }
}

__attribute__((weak)) void sendDataWs() {
  DynamicJsonDocument jsonBuffer(4096);
  jsonBuffer["bateria"] = System::battery;
  jsonBuffer["pressao"] = Sensors::pressure;
  jsonBuffer["temperatura"] = Sensors::temperature;
  jsonBuffer["humidade"] = Sensors::humidity;
  jsonBuffer["co2"] = Sensors::CO2Level;
  jsonBuffer["luminosidade"] = Sensors::luminosity;
  JsonArray accel = jsonBuffer.createNestedArray("acelerometro");
    accel.add(Sensors::accel[0]);
    accel.add(Sensors::accel[1]);
    accel.add(Sensors::accel[2]);
  JsonArray gyro = jsonBuffer.createNestedArray("giroscopio");
    gyro.add(Sensors::gyro[0]);
    gyro.add(Sensors::gyro[1]);
    gyro.add(Sensors::gyro[2]);  
  JsonArray mag = jsonBuffer.createNestedArray("magnetometro");
    mag.add(Sensors::mag[0]);
    mag.add(Sensors::mag[1]);
    mag.add(Sensors::mag[2]);
  jsonBuffer["sdCard"] = sdStatusMessage[Storage::sdStatus];
  jsonBuffer["siren"] = sirenMessage[Interface::sirenAction];

  size_t len = measureJson(jsonBuffer);
  AsyncWebSocketMessageBuffer * buffer = ws.makeBuffer(len); //  creates a buffer (len + 1) for you.
  if (buffer) {
    serializeJson(jsonBuffer,(char *)buffer->get(), len + 1);
    ws.textAll(buffer);
  }
}


