#ifndef TEMPERATURHANDLER_HPP
#define TEMPERATURHANDLER_HPP

#include "Sensor.hpp"

namespace TemperaturHandler
{
    float getTemperature();
    float getHumidity();
    float getHeatIndex();
    SensorDHT22::SensorData getSensorData();
    SensorDHT22::SensorData update();
}

#endif