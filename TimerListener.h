#ifndef TIMERMANAGER_TIMERLISTENER_H_
#define TIMERMANAGER_TIMERLISTENER_H_

class Timer;

class TimerListener {
public:
    TimerListener();
    ~TimerListener();
    void setTimer(Timer *timer);
    void stopTimer();
    virtual void onTimerCall() = 0;
private:
    Timer *timer;
};

#endif