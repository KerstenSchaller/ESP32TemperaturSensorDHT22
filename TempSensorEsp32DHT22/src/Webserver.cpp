

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "TemperaturHandler.hpp"
#include "ControllerAndAgent/RemoteSensor.hpp"
#include "ControllerAndAgent/ControlProtocol.hpp"

namespace Webserver
{

AsyncWebServer server(80);
int requestCounter = 0;

bool datavalid = false;
int countAttempts = 0;

void requestCallback(AsyncWebServerRequest *request)
{
    Serial.println("Received http get");
    countAttempts++;
    Serial.println("Reading from sensor attempt" + String(countAttempts));
    Controlprotocol::requestTemperatureReadings();
    delay(2*1000);
    String returnText = Controlprotocol::getName() + " Temperature: " + String(TemperaturHandler::getTemperature()) + "\n";
    for (int i = 0; i < NUMBEROFSENSORS; i++)
    {
        auto sensor = Remote::getSensor(i);
        if (sensor->getIsActive())
        {
            returnText += sensor->getName() + " Temperature: " + String(sensor->getData().temperature) + "\n";
        }
    }


    Serial.println("Answering with: " + returnText);
    requestCounter++;
    request->send(200, "text/plain", returnText);
}

void startWebserver()
{

    server.on("/", HTTP_GET, requestCallback);
    server.begin();
}

    void start()
    {   
        startWebserver();
    }

    void end()
    {
        server.end();       
    }
}