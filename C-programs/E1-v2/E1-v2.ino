#include "WiFi.h"
#include <HTTPClient.h>
const char* ssid = "xxx";
const char* password =  "xxx";

#define PIN_LM35       36 
 
void setup() {
  Serial.begin(9600);
  connectWifi(); 
}

void connectWifi(){
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println("");
}

float readTemp(){
  // read the ADC value from the temperature sensor
  int adcVal = analogRead(PIN_LM35);
  // convert the ADC value to voltage in millivolt
  float tempC = (adcVal * (3300.0 / 4096.0)/10);
  return tempC;
}

int sendData(float temp){
  HTTPClient http;
  String url = "https://api.thingspeak.com/update?api_key=<HIDE>&field1="+String(temp);
  http.begin(url.c_str());
  return http.GET();
} 

void loop() {
  if( WiFi.status() == WL_CONNECTED ){
    sendData(readTemp());
   // increase to 20 seconds of delay because
   // it doesn't have a delay of connection time
    delay(20000);  
  }
}