

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "TemperaturHandler.hpp"

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


    String returnText = "Temperatur: " + String(TemperaturHandler::getTemperature()) + "C   Luftfeuchte: " + String(TemperaturHandler::getHumidity());

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