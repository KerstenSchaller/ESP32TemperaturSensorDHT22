#include <Arduino.h>
#include "SystemTime.h"
#include "Webserver.hpp"

#include "UDPHandler.hpp"
#include "WifiHandler.hpp"
#include "TemperaturHandler.hpp"
#include "TimerHandler.hpp"

#include "ControllerAndAgent/ControlProtocol.hpp"

//#include "Deepsleep.h"

void sendData()
{
    String timeInfo = SystemTime::getTimeString();

    //String text = timeInfo +  ",t," + String(TemperaturHandler::getTemperature()) + ",h," +  String(TemperaturHandler::getHumidity());
    //UDPHANDLER::sendBroadCast(text.c_str());


}

void timerCallback()
{
  //TemperaturHandler::update();
  sendData();
}

void setup()
{
  Serial.begin(115200);
  
  WifiHandler::ConnectWifi();
  WifiHandler::setUpmDNS("esp32");
  //UDPHANDLER::start();
  //Webserver::start(); // now in controlprotokol.cpp
  TemperaturHandler::update();
  TimerHandler::setup(timerCallback);
  SystemTime::get();
  Controlprotocol::setup("Wohnzimmer");

  Controlprotocol::discoverOthers();
}
  
void loop()
{
  // must run to check for interrupts, which causes callback 
  TimerHandler::check(); 
}