#include "Sensor.hpp"

namespace TemperaturHandler
{

    SensorDHT22 sensor(4);
    SensorDHT22::SensorData data;

    float getTemperature()
    {
        return data.temperature;
    }
    float getHumidity()
    {
        return data.humidity;
    }
    float getHeatIndex()
    {
        return data.heatIndexCelsius;
    }

    SensorDHT22::SensorData getSensorData()
    {
        return data;
    }
    
    void update()
    {
        data = sensor.readValues();
    }
}