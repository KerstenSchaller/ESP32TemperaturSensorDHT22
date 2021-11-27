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

        uint8_t *serializeSensorData()
        {
            Container container;
            container.data = data;
            return container.packetbytes;
        }

        void deSerializeSensorData(const uint8_t* packetbytes)
        {
            Container container;
            memcpy(container.packetbytes, packetbytes, sizeof(SensorDHT22::SensorData));
            data = container.data;
        }
    };


    RemoteSensor *getSensor(int index);
    RemoteSensor *getSensor(IPAddress ip);

    RemoteSensor *getMaster();
}

#endif