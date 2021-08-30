#pragma once

#include "Arduino.h"
#include "DHT.h"

//#define DHTPIN 4     // Digital pin connected to the DHT sensor
//#define DHTTYPE    // DHT 22  (AM2302), AM2321


class SensorDHT22
{
private:
    DHT dht;
    struct SensorData
    {
        float temperature;
        float humidity;
        float heatIndexCelsius;
        uint8_t valid;
    };
    

public:

    SensorDHT22(uint8_t pin);


    SensorData readValues();
};

