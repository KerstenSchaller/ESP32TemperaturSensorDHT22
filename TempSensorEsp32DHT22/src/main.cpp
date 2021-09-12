/*

#include "Arduino.h"


void setup() 
{
  //sensor = SensorDHT22(4);
  Serial.begin(115200);
}

void loop() 
{
  // Wait a few seconds between measurements.
  delay(2000);
  sensor.readValues();

}

*/

#include <ESPmDNS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#include "Sensor.hpp"

#include "Credentials.h"
  
AsyncWebServer server(80);
int requestCounter = 0;

SensorDHT22 sensor(4);


void requestCallback(AsyncWebServerRequest *request)
{
  Serial.println("Received http get");
  SensorDHT22::SensorData data;


  bool datavalid = false;
  int countAttempts = 0;
  while(!datavalid && (countAttempts < 15))
  {
    countAttempts++;
    Serial.println("Reading from sensor attempt" + String(countAttempts));
    data = sensor.readValues();
    datavalid = data.valid;
  }
/*  
data = sensor.readValues();
*/

  String returnText = (data.valid ? "Temperatur: " + String(data.temperature)+ "C   Luftfeuchte: " + String(data.humidity) + "%" : "Could not read from sensor");
  
  Serial.println("Answering with: " + returnText);
  requestCounter++;
  request->send(200, "text/plain", returnText);
}

void setup(){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  WiFi.setHostname("node1");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
 
  if(!MDNS.begin("esp32")) {
     Serial.println("Error starting mDNS");
     return;
  }

  
  Serial.println(WiFi.localIP());
  
  server.on("/", HTTP_GET, requestCallback);
  
  server.begin();

  // Add service to MDNS-SD
  //MDNS.addService("http", "tcp", 80);
}
  
void loop(){}