#include "ControlProtocol.hpp"
#include "UDPHandler.hpp"
#include "AsyncUDP.h"
#include "TimerHandler.hpp"
#include "RemoteSensor.hpp"

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
        MEASUREMENTRESPONSE
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
        currentSensorID++;
    }

    void dispatch(AsyncUDPPacket packet)
    {
        MessageContainer mc;
        memcpy(mc.packetbytes, packet.data(), sizeof(Message));
        Message message = mc.message;
        switch (message.type)
        {
        case Type::ANYBODYTHERE:
            Serial.write("Received ANYBODYTHERE ... from ");
            Serial.write(mc.message.payload);
            Serial.write("\n");
            addRemoteSensor(packet.remoteIP(), false, mc.message.payload);
            replyToDiscovery(&packet);
            break;
        case Type::IAMHERE:
            Serial.write("Received IAMHERE ... from ");
            Serial.write(mc.message.payload);
            Serial.write("\n");
            addRemoteSensor(packet.remoteIP(), false, mc.message.payload);
        case Type::IAMMASTER:
            params.timeoutRunning = false;
            TimerHandler::delCallback2();
            Serial.write("Received IAMMASTER ... from ");
            Serial.write(mc.message.payload);
            Serial.write("\n");
            addRemoteSensor(packet.remoteIP(), true, mc.message.payload);
            break;
        default:
            break;
        }
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

    void timeout()
    {
        Serial.write("Becoming master \n");
        params.isMaster = true;
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
    void setup()
    {
        params.name = "Wohnzimmer";
        UDPHANDLER::start();
        UDPHANDLER::setCallback(onReceivePacket);
        TimerHandler::setCallback2(timerCallback);
    }


}