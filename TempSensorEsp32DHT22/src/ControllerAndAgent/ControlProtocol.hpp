#ifndef CONTROLPROTOCOL_HPP
#define CONTROLPROTOCOL_HPP

#include <Arduino.h>

namespace Controlprotocol
{
    void setup(String _name);
    String getName();
    bool discoverOthers();
    void requestTemperatureReadings();
}

#endif