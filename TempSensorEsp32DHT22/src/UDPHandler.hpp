#ifndef UDPHANDLER_HPP
#define UDPHANDLER_HPP

#include <Arduino.h>
#include "AsyncUDP.h"

namespace UDPHANDLER
{
    void start();
    void connect();
    void sendBroadCast(uint8_t *Text, int len);
    void sendBroadCast(String text);
    void sendUnicast(IPAddress ip, uint8_t *text, int len);

    void setCallback(void (*fn)(AsyncUDPPacket packet));
}
#endif