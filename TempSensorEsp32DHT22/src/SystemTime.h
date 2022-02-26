#ifndef TIME_H
#define TIME_H

#include "time.h"
#include <Arduino.h>

namespace SystemTime
{
    String getTimeString();
    tm get();
    bool isSetUp();
}

#endif