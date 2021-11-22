
#include "UDPHandler.hpp"
#include "AsyncUDP.h"

// IP address to send UDP data to.
// it can be ip address of the server or
// a network broadcast address
// here is broadcast address
const int udpPort = 4444;

//create UDP instance
AsyncUDP audp;

namespace UDPHANDLER
{
    void startUDP();

    void start()
    {
        startUDP();
    }

    void sendBroadCast(uint8_t * text, int len)
    {
        audp.broadcast(text, len);
    }


    void (*callback)(AsyncUDPPacket packet);

    void setCallback(void (*fn)(AsyncUDPPacket packet))
    {
        callback = fn;
    }

    void startUDP()
    {
        if (audp.listen(4444))
        {
            audp.onPacket([](AsyncUDPPacket packet)
                          { callback(packet); });
        }
    }
}