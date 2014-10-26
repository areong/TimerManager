#ifndef TIMERMANAGER_TIMER_H_
#define TIMERMANAGER_TIMER_H_

class TimerListener;

class Timer {
public:
    Timer(int resolution, double period, int numPeriods, TimerListener *listener);
    ~Timer();
    void tick();
    void pause();
    void resume();
    void stop();
    /*
    Remember to pause before setResolution,
    and resume after setResolution.
    resolution is in microseconds.
    */
    void setResolution(int resolution);
private:
    /*
    Period between timer call. Unit is second.
    */
    double period;
    /*
    Period between timer call. Unit is tick.
    One tick is one IntervalTimer call.
    */
    int periodInTicks;
    /*
    Timer runs a number of periods and then stops.
    */
    int numPeriods;
    int countTicks;
    int countPeriods;
    /*
    True if the timer pauses.
    */
    bool paused;
    /*
    True if Timer.stop() has been called.
    */
    bool stopped;
    bool nonStop;
    TimerListener *listener;
};

#endif