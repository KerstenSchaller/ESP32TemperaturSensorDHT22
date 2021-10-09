
#include "udp_sender.h"
#include <WiFiUdp.h>

#include "AsyncUDP.h"

// IP address to send UDP data to.
// it can be ip address of the server or 
// a network broadcast address
// here is broadcast address
const char * udpAddress = "192.168.1.109";
const int udpPort = 4444;

//create UDP instance
WiFiUDP udp;
AsyncUDP audp;

void start()
{
    udp.begin(udpPort);

    if(audp.listen(4444)) 
    {
        audp.onPacket([](AsyncUDPPacket packet) 
        {
            Serial.print("UDP Packet Type: ");
            Serial.print(packet.isBroadcast()?"Broadcast":packet.isMulticast()?"Multicast":"Unicast");
            Serial.print(", From: ");
            Serial.print(packet.remoteIP());
            Serial.print(":");
            Serial.print(packet.remotePort());
            Serial.print(", To: ");
            Serial.print(packet.localIP());
            Serial.print(":");
            Serial.print(packet.localPort());
            Serial.print(", Length: ");
            Serial.print(packet.length());
            Serial.print(", Data: ");
            Serial.write(packet.data(), packet.length());
            Serial.println();
            //reply to the client
            //packet.printf("Got %u bytes of data", packet.length());
        });
    }
}

void connect()
{

}




void sendBroadCast(String text)
{
    udp.begin(4444);

    //data will be sent to server
    char buffer[256];
    text.toCharArray(buffer, 256);
    //char *udpAddress = "192.168.1.109";
    char *udpAddress = "255.255.255.255";
    int udpPort = 4444;
    udp.beginPacket(udpAddress, udpPort);
    udp.write((uint8_t *)buffer, text.length());
    udp.endPacket();
    memset(buffer, 0, 50);


}
