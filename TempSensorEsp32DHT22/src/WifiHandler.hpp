#ifndef WIFIHANDLER_HPP
#define WIFIHANDLER_HPP

#include <Arduino.h>

namespace WifiHandler
{

    void ConnectWifi();

    void setUpmDNS(String hostname);

}

#endif