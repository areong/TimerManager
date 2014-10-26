#ifndef TIMERMANAGER_TIMERLISTENER_H_
#define TIMERMANAGER_TIMERLISTENER_H_

class Timer;

class TimerListener {
public:
    TimerListener();
    ~TimerListener();
    void setTimer(Timer *timer);
    void pauseTimer();
    void resumeTimer();
    void stopTimer();
    virtual void onTimerCall() = 0;
    /*
    Called when Timer.stop() is called.
    It is not purely virtual so subclass can choose to override it or not.
    */
    virtual void onTimerStopped() {}
private:
    Timer *timer;
};

#endif