
#include <ESPmDNS.h>
#include <WiFi.h>

#include <ESPAsyncWebServer.h>

#include "Sensor.hpp"
#include "udp_sender.h"

#include "Credentials.h"
  
AsyncWebServer server(80);
int requestCounter = 0;

SensorDHT22 sensor(4);

SensorDHT22::SensorData data;

  bool datavalid = false;
  int countAttempts = 0;

void sendData()
{
  data = sensor.readValues();
  if (data.valid)
  {
    String text = "t," + String(data.temperature) + ",h," +  String(data.humidity);
    sendBroadCast(text.c_str());
  }

}

void requestCallback(AsyncWebServerRequest *request)
{
  Serial.println("Received http get");
  // Try to read values from sensor up to 15 times
  while(!datavalid && (countAttempts < 15))
  {
    countAttempts++;
    Serial.println("Reading from sensor attempt" + String(countAttempts));
    data = sensor.readValues();
    datavalid = data.valid;
  }

  

  String returnText = (data.valid ? "Temperatur: " + String(data.temperature)+ "C   Luftfeuchte: " + String(data.humidity) + "%" : "Could not read from sensor");
  
  Serial.println("Answering with: " + returnText);
  requestCounter++;
  request->send(200, "text/plain", returnText);
}

void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);
  WiFi.setHostname("node1");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
 
  if(!MDNS.begin("esp32")) {
     Serial.println("Error starting mDNS");
     return;
  }
  
  start();
    
  server.on("/", HTTP_GET, requestCallback);
  server.begin();
}
  
void loop()
{
  sendData();
  //delay(1000);
}