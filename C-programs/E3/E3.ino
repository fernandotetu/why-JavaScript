#include "WiFi.h"
#include <WebServer.h>

const char* ssid = "xxx";
const char* password =  "xxx";
const int magnet_switch = 5;     // Magnet switch
WebServer server(80);
 
void setup() {
  Serial.begin(9600);
  pinMode(magnet_switch, INPUT_PULLUP);

  connectWifi(); 
  server.on("/", handle_root);
  server.begin();
}

void connectWifi(){
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
  }
}

void loop() {
  if( WiFi.status() == WL_CONNECTED ){
    server.handleClient();
  }
}
void handle_root() {
  int sensorData = digitalRead(magnet_switch);
  server.send(200, "text/plain", String(sensorData));
}
