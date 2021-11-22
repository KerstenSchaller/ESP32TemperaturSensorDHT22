#include <WiFi.h>
#include "Credentials.h"
#include <ESPmDNS.h>

namespace WifiHandler
{

    void ConnectWifi()
    {
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, pwd);
        WiFi.setHostname("node1");
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            Serial.println("Connecting to WiFi..");
        }
        Serial.println("Wifi connected.");
    }

    void setUpmDNS(String hostname)
    {
        if (!MDNS.begin(hostname.c_str()))
        {
            Serial.println("Error starting mDNS");
            return;
        }
    }

}