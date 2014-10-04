#ifndef TIMERMANAGER_TIMERMANAGER_H_
#define TIMERMANAGER_TIMERMANAGER_H_

#include "List.h"

class IntervalTimer;
class Timer;
class TimerListener;

class TimerManager {
public:
    ~TimerManager();
    static TimerManager *instance;
    static TimerManager *getInstance();
    /*
    @param ithRes Indicate which resolution to set. Range from zero to
                    the number of hardware IntervalTimer available.
    */
    bool setResolution(int ithRes, int resolution);
    /*
    @param ithRes Indicate which resolution to set. Range from zero to
                    the number of hardware IntervalTimer available.
    */
    int getResolution(int ithRes);
    /*
    @param ithRes Indicate which resolution to set. Range from zero to
                    the number of hardware IntervalTimer available.
    */
    void addTimerAndStart(int ithRes, double period, int numPeriods, TimerListener *listener);
    void addStoppedTimer(Timer *timer);
    void onIntervalTimer0Call();
    void onIntervalTimer1Call();
    void onIntervalTimer2Call();
private:
    /*
    For the two constants please refer to IntervalTimer:
    https://github.com/loglow/IntervalTimer
    */
    const int NUM_INTERVALTIMERS;
    const int RESOLUTION_UPPERBOUND;

    /*
    Interrupt occuring in high frequency may cause problems,
    so add lower bound on resolution.
    */
    const int RESOLUTION_LOWERBOUND;

    IntervalTimer **intervalTimers;
    /*
    Unit is microsecond.
    */
    int *resolutions;
    List<Timer *> **timers;
    List<Timer *> *stoppedTimers;
    TimerManager();
    void beginIntervalTimer(int ithRes);
    void deleteStoppedTimers();
};

#endif