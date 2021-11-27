#ifndef REMOTESENSOR_HPP
#define REMOTESENSOR_HPP

#include <Arduino.h>
#include "AsyncUDP.h"

#define NUMBEROFSENSORS 6
#include "Sensor.hpp"

namespace Remote
{

    class RemoteSensor
    {
    private:
        bool isActive = false;
        bool isMaster = false;
        IPAddress ip;
        String name = "noname";
        SensorDHT22::SensorData data;

    typedef union Container
    {
        SensorDHT22::SensorData data;
        uint8_t packetbytes[sizeof(SensorDHT22::SensorData)];
    } Container;

    public:
        void setIP(AsyncUDPPacket packet)
        {
            ip = packet.remoteIP();
        }
        void setIP(IPAddress _ip)
        {
            ip = _ip;
        }
        IPAddress getIP() { return ip; }

        void setName(String _name)
        {
            name = _name;
        }
        String getName() { return name; }

        void setMaster(bool value)
        {
            isMaster = value;
        }
        bool getIsMaster() { return isMaster; }

        void setIsActive(bool value)
        {
            isActive = value;
        }
        bool getIsActive() { return isActive; }

        void setData(SensorDHT22::SensorData _data)
        {
            data = _data;
        }

        SensorDHT22::SensorData getData()
        {
            return data;
        }

        void serializeSensorData(uint8_t * _data)
        {
            Container container;
            container.data = this->data;
            memcpy(_data, container.packetbytes, sizeof(SensorDHT22::SensorData));
            /*
            for (int i = 0; i < sizeof(SensorDHT22::SensorData); i++)
            {
                _data[i] = container.packetbytes[i];
            }*/
        }
        
        void deSerializeSensorData(const uint8_t* packetbytes)
        {
            Container container;
            memcpy(container.packetbytes, packetbytes, sizeof(SensorDHT22::SensorData));
            //data = container.data;
            Serial.write(String(container.data.temperature).c_str() );
            Serial.write("\n");
            memcpy(&data, &container.data, sizeof(SensorDHT22::SensorData));
        }
    };


    RemoteSensor *getSensor(int index);
    RemoteSensor *getSensor(IPAddress ip);

    RemoteSensor *getMaster();
}

#endif