#ifndef TIMERHANDLER_HPP
#define TIMERHANDLER_HPP
namespace TimerHandler
{
    void setup( void (*fn)());
    void setCallback2(void (*fn)());
    void delCallback2();
    bool check();
}
#endif
