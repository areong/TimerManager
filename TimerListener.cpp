#include "TimerListener.h"
#include "Timer.h"

TimerListener::TimerListener() {
    timer = 0;
}

TimerListener::~TimerListener() {
    // Stop the timer or the timer will call a null listener.
    // It is possible the pointer to Timer is null, check first.
    if (timer != 0)
        timer->stop();
}

void TimerListener::setTimer(Timer *timer) {
    this->timer = timer;
}

void TimerListener::pauseTimer() {
    if (timer != 0)
        timer->pause();
}

void TimerListener::resumeTimer() {
    if (timer != 0)
        timer->resume();
}

void TimerListener::stopTimer() {
    if (timer != 0)
        timer->stop();
}
