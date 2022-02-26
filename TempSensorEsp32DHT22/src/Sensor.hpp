#ifndef SENSOR_HPP
#define SENSOR_HPP

#include "Arduino.h"
#include "DHT.h"

class SensorDHT22
{
private:
    DHT dht;
public:

    SensorDHT22(uint8_t pin);
    struct SensorData
    {
        float temperature;
        float humidity;
        float heatIndexCelsius;
        bool temperatureValid = false;
        bool humidityValid= false;
        bool heatIndexValid= false;
    };

    SensorData readValues();
};

#endif