#include "time.h"
#include "WiFi.h"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

namespace SystemTime
{

bool isSetUp = false;

void get()
{
  if(isSetUp == false)
  {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    isSetUp = true;
  }
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}


}