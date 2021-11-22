
#include "Sensor.hpp"

SensorDHT22::SensorDHT22(uint8_t pin) : dht(pin, 22)
{
    dht.begin();
}

SensorDHT22::SensorData SensorDHT22::readValues()
{

    SensorDHT22::SensorData data;

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    
    // Check if any reads failed and exit early (to try again).
    if (isnan(t))
    {
        Serial.println(F("Failed to read temperature from DHT sensor!"));
        data.temperatureValid = false;
    }
    else
    {
        data.temperatureValid = true;
    }

    
    if (isnan(h))
    {
        Serial.println(F("Failed to read humidity from DHT sensor!"));
        data.humidityValid = false;
    }
    else
    {
        data.humidityValid = true;
    }

    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);

    if (isnan(hic))
    {
        Serial.println(F("Failed to compute heat index from DHT sensor!"));
        data.heatIndexValid = false;
    }
    else
    {
        data.heatIndexValid = true;
    }


    // return values
    data.temperature = t;
    data.humidity = h;
    data.heatIndexCelsius = hic;
    return data;
}
