#include <Arduino.h>

volatile int interruptCounter;
int totalInterruptCounter;

void (*callback)();
void (*callback2)();
bool set2 = false;


hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
 
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux); 
}

namespace TimerHandler
{ 

void setup(void (*fn)()) 
{
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  //timerAlarmWrite(timer, timeSeconds*1000*1000, true);
  timerAlarmWrite(timer, 5*1000*1000, true);
  timerAlarmEnable(timer);
  callback = fn;  
}

void setCallback2(void (*fn)()) 
{
  callback2 = fn;
  set2 = true;
} 

void delCallback2()
{
  callback2 = nullptr;
  set2 = false;
}

bool check() 
{
  if (interruptCounter > 0) 
  {
 
    portENTER_CRITICAL(&timerMux);
    interruptCounter--;
    portEXIT_CRITICAL(&timerMux);
 
    totalInterruptCounter++;
    callback();
    if(set2)
    {
      callback2();
    }
    return true;
  }
  return false;
}

}