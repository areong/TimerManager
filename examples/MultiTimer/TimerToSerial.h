#ifndef MULTITIMER_TIMERTOSERIAL_H_
#define MULTITIMER_TIMERTOSERIAL_H_

#include "TimerListener.h"

class TimerToSerial : public TimerListener {
public:
    static void beginSerial(int baud);
    TimerToSerial(int id);
    ~TimerToSerial();
    void onTimerCall();
private:
    int id;
};

#endif