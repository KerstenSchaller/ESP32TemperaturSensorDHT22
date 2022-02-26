#include <Arduino.h>
#include "SystemTime.h"

#include "UDPHandler.hpp"
#include "WifiHandler.hpp"
#include "TemperaturHandler.hpp"
//#include "TimerHandler.hpp"

//#include "ControllerAndAgent/ControlProtocol.hpp"
#include "Deepsleep.h"

String name = "Wohnzimmer";

bool sendData()
{
    String timeInfo = SystemTime::getTimeString();
    if(timeInfo == "failure")
    {
        Serial.println("Getting time info failed");
        return false;
    }
    String text = name + "," + timeInfo +  ",t," + String(TemperaturHandler::getTemperature()) + ",h," +  String(TemperaturHandler::getHumidity());
    UDPHANDLER::sendBroadCast(text);
    return true;
}

void timerCallback()
{
  auto data = TemperaturHandler::update();
  if(data.temperatureValid)
  {
    bool succes = sendData();
    if(succes)
    {
      Serial.println("Going to sleep");
      Deepsleep::startSleep(5*60);
    }
  }
  else
  {
    Serial.println("Temperature not valid");
  }
}

void setup()
{
  Serial.begin(115200);
  
  WifiHandler::ConnectWifi();
  //WifiHandler::setUpmDNS("esp32");
  SystemTime::get();
  UDPHANDLER::start();
  //Webserver::start(); // now in controlprotokol.cpp
  TemperaturHandler::update();
  //TimerHandler::setup(timerCallback);
  
  //Controlprotocol::setup(name);
  //Controlprotocol::discoverOthers();
}
  

void loop()
{
  timerCallback();
  if(SystemTime::isSetUp())
  {
  }
  else
  {
    SystemTime::get();
  }
  // must run to check for interrupts, which causes callback 
  //TimerHandler::check(); 
}