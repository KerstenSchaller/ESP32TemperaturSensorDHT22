#include "time.h"
#include "WiFi.h"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

namespace SystemTime
{

bool isSetUp = false;

String getTimeString()
{
  if(isSetUp == false)
  {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    isSetUp = true;
  }
  time_t rawtime;
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
   return "Failed to obtain time";
  }
  char timeStringBuff[50];
 strftime(timeStringBuff, sizeof(timeStringBuff), "%Y,%m,%d,%H,%M,%S", &timeinfo);
   return String(timeStringBuff);
}

void get()
{

  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}


}