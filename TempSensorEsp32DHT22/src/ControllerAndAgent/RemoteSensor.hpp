#ifndef REMOTESENSOR_HPP
#define REMOTESENSOR_HPP

#include <Arduino.h>
#include "AsyncUDP.h"

namespace Remote
{

    class RemoteSensor
    {
    private:
        bool isActive = false;
        bool isMaster = false;
        IPAddress ip;
        String name = "noname";

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

        void setActive(bool value)
        {
            isActive = value;
        }
        bool getIsActive() { return isActive; }
    };


    RemoteSensor *getSensor(int index);

    RemoteSensor *getMaster();
}

#endif