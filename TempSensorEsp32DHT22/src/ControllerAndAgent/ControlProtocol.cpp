#include "ControlProtocol.hpp"
#include "UDPHandler.hpp"
#include "AsyncUDP.h"
#include "TimerHandler.hpp"
#include "RemoteSensor.hpp"
#include "Webserver.hpp"
#include "TemperaturHandler.hpp"

#define BUFSIZE 512

namespace Controlprotocol
{
    typedef struct Parameters
    {
        bool isMaster = false;
        bool timeoutRunning = false;
        String name;

    } Parameters;
    Parameters params;

    enum Type
    {
        ANYBODYTHERE,
        IAMHERE,
        IAMMASTER,
        BEMASTER,
        MEASUREMENTREQUEST,
        TEMPERATURE
    };

    typedef struct Message
    {
        Type type;
        char payload[BUFSIZE];
    } Message;

    typedef union MessageContainer
    {
        Message message;
        uint8_t packetbytes[sizeof(message)];
    } MessageContainer;

    void sendDataTo(IPAddress ip, Type type, String data);
    void replyToSender(AsyncUDPPacket *packet, MessageContainer mc);

    void requestTemperatureReadings()
    {
        for (size_t i = 0; i < NUMBEROFSENSORS; i++)
        {
            auto sensor = Remote::getSensor(i);
            if (sensor->getIsActive())
            {
                sendDataTo(sensor->getIP(), MEASUREMENTREQUEST, "");
            }
        }
        
    }

    void receiveTemperatureReadings(AsyncUDPPacket packet, char* data)
    {
        auto sensor = Remote::getSensor(packet.remoteIP());
        if (sensor->getIsActive())
        {
            sensor->deSerializeSensorData((uint8_t *)data);
        }
    }

    void replyToTemperatureReadingRequest(AsyncUDPPacket packet)
    {
        auto data = TemperaturHandler::getSensorData();
        Remote::RemoteSensor sensor;
        sensor.setData(data);
        auto serialized_data = sensor.serializeSensorData();

        MessageContainer mc;
        mc.message.type = TEMPERATURE;
        memcpy(mc.message.payload, serialized_data, sizeof(serialized_data));
        replyToSender(&packet, mc);
    }

    bool discoverOthers()
    {
        MessageContainer mc;
        for (size_t i = 0; i < sizeof(mc.packetbytes); i++)
        {
            mc.packetbytes[i] = 0;
        }

        mc.message.type = Type::ANYBODYTHERE;
        strcpy(mc.message.payload, params.name.c_str());
        UDPHANDLER::sendBroadCast(mc.packetbytes, sizeof(mc.packetbytes));
        params.timeoutRunning = true;
        return true;
    }

    void replyToSender(AsyncUDPPacket *packet, MessageContainer mc)
    {
        // reply to sender of packet
        packet->write(mc.packetbytes, sizeof(mc.packetbytes));
    }

    void sendDataTo(IPAddress ip, Type type, String data)
    {
        MessageContainer mc;
        for (size_t i = 0; i < sizeof(mc.packetbytes); i++)
        {
            mc.packetbytes[i] = 0;
        }

        mc.message.type = type;
        strcpy(mc.message.payload, data.c_str());
        UDPHANDLER::sendUnicast( ip, mc.packetbytes, sizeof(mc.packetbytes));
    }

    void replyToDiscovery(AsyncUDPPacket *packet)
    {
        MessageContainer mc;
        for (size_t i = 0; i < sizeof(mc.packetbytes); i++)
        {
            mc.packetbytes[i] = 0;
        }
        if (params.isMaster)
        {
            mc.message.type = Type::IAMMASTER;
        }
        else
        {
            mc.message.type = Type::IAMHERE;
        }
        strcpy(mc.message.payload, params.name.c_str());
        replyToSender(packet, mc);
    }

    void addRemoteSensor(IPAddress ip, bool isMaster,String name)
    {
        static int currentSensorID = 0;
        Remote::RemoteSensor *sensor = Remote::getSensor(currentSensorID);
        sensor->setIP(ip);
        sensor->setMaster(isMaster);
        sensor->setName(name);
        sensor->setIsActive(true);
        currentSensorID++;
    }

    void dispatch(AsyncUDPPacket packet)
    {
        //deserialize packet to message
        MessageContainer mc;
        memcpy(mc.packetbytes, packet.data(), sizeof(Message));
        Message message = mc.message;
        
        switch (message.type)
        {
        case Type::ANYBODYTHERE:
            Serial.write("Received ANYBODYTHERE ... from ");
            addRemoteSensor(packet.remoteIP(), false, mc.message.payload);
            replyToDiscovery(&packet);
            break;
        case Type::IAMHERE:
            Serial.write("Received IAMHERE ... from ");
            addRemoteSensor(packet.remoteIP(), false, mc.message.payload);
        case Type::IAMMASTER:
            params.timeoutRunning = false;
            TimerHandler::delCallback2();
            Serial.write("Received IAMMASTER ... from ");
            addRemoteSensor(packet.remoteIP(), true, mc.message.payload);
            break;
        case Type::MEASUREMENTREQUEST:
            replyToTemperatureReadingRequest(packet);
            Serial.write("Received MEASUREMENTREQUEST ");
            break;
        case Type::TEMPERATURE:
            receiveTemperatureReadings(packet, mc.message.payload);
            Serial.write("Received TEMPERATURE ");
           break;
        default:
            break;
        }
        Serial.write(mc.message.payload);
        Serial.write("\n");
    }

    void onReceivePacket(AsyncUDPPacket packet)
    {

        if (packet.length() == sizeof(Message))
        {
            dispatch(packet);
        }
        else
        {
            Serial.write("Received message has unknown size \n");
        }
    }

    void becomeMaster()
    {
        Serial.write("Becoming master \n");
        Webserver::start();
        params.isMaster = true;
    }

    void timeout()
    {
        becomeMaster();
    }

    void timerCallback()
    {
        static uint32_t count = 0;
        uint32_t timerthreshold = 5;

        if (params.timeoutRunning)
        {
            if (count > timerthreshold)
            {
                timeout();
                count = 0;
                params.timeoutRunning = false;
                TimerHandler::delCallback2();
            }
            else
            {
                count++;
            }
        }
    }

    void setup(String _name)
    {
        params.name = _name;
        UDPHANDLER::start();
        UDPHANDLER::setCallback(onReceivePacket);
        TimerHandler::setCallback2(timerCallback);
    }


}