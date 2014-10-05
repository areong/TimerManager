#include "TimerListener.h"
#include "Timer.h"

TimerListener::TimerListener() {
    timer = 0;
}

TimerListener::~TimerListener() {

}

void TimerListener::setTimer(Timer *timer) {
    this->timer = timer;
}

void TimerListener::stopTimer() {
    timer->stop();
}
