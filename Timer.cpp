#include "Timer.h"
#include "TimerListener.h"
#include "TimerManager.h"

Timer::Timer(int resolution, double period, int numPeriods, TimerListener *listener) {
    this->period = period;

    // resolution: time (microseconds) between two IntervalTimer calls (or ticks).
    // period: time (seconds) between two Timer call.
    // periodInTicks: number of ticks between two Timer call, which is
    // calculated by dividing period by resolution.
    periodInTicks = (int)(period / ((double)resolution / 1000000.0));
    
    this->numPeriods = numPeriods;
    countTicks = 0;
    countPeriods = 0;
    paused = false;
    stopped = false;
    nonStop = (numPeriods <= 0 ? true : false);
    this->listener = listener;
    if (listener != 0)  // User might input a null pointer.
        listener->setTimer(this);
}

Timer::~Timer() {

}

void Timer::tick() {
    if (paused) return;

    countTicks++;
    if (countTicks >= periodInTicks) {
        countPeriods++;
        if (listener != 0)  // Listener is null if it is deleted.
            listener->onTimerCall();
        if (!nonStop && countPeriods >= numPeriods)
            stop();
        countTicks = 0;
    }
}

void Timer::pause() {
    paused = true;
}

void Timer::resume() {
    paused = false;
}

void Timer::stop() {
    if (stopped)    // Cannot stop again if Timer.stop() has been called before.
        return;

    paused = true;
    stopped = true;
    TimerManager::getInstance()->addStoppedTimer(this);
    if (listener != 0)  // Listener is null if it is deleted.
        listener->onTimerStopped();
}

void Timer::setResolution(int resolution) {
    double ratioOfCount = (double)countTicks / (double)periodInTicks;
    periodInTicks = (int)(period / ((double)resolution / 1000000.0));
    countTicks = (int)(periodInTicks * ratioOfCount);
}