#include "TimerManager.h"
#include "IntervalTimer.h"
#include "Timer.h"

void ISRIntervalTimer0();
void ISRIntervalTimer1();
void ISRIntervalTimer2();

TimerManager *TimerManager::instance = 0;

TimerManager::~TimerManager() {
    for (int i = 0; i < NUM_INTERVALTIMERS; i++) {
        delete intervalTimers[i];
        for (int j = 0; j < timers[i]->getLength(); j++) {
            delete timers[i]->get(j);
        }
        delete timers[i];
    }
    delete stoppedTimers;
}

TimerManager *TimerManager::getInstance() {
    if (TimerManager::instance == 0) {
        TimerManager::instance = new TimerManager();
    }
    return TimerManager::instance;
}

bool TimerManager::setResolution(int ithRes, int resolution) {
    // If resolution is not valid, return false.
    if (resolution <= RESOLUTION_LOWERBOUND ||
        resolution >= RESOLUTION_UPPERBOUND)
        return false;

    resolutions[ithRes] = resolution;

    // Stop InvervalTimer.
    intervalTimers[ithRes]->end();

    for (int i = 0; i < timers[ithRes]->getLength(); i++) {
        Timer *timer = timers[ithRes]->get(i);
        timer->pause();
        timer->setResolution(resolution);
        timer->resume();
    }

    // Begin InvervalTimer.
    beginIntervalTimer(ithRes);  

    return true;
}

int TimerManager::getResolution(int ithRes) {
    return resolutions[ithRes];
}

void TimerManager::addTimerAndStart(int ithRes, double period, int numPeriods, TimerListener *listener) {
    Timer *timer = new Timer(resolutions[ithRes], period, numPeriods, listener);
    timers[ithRes]->add(timer);
}

void TimerManager::addStoppedTimer(Timer *timer) {
    stoppedTimers->add(timer);
}

void TimerManager::onIntervalTimer0Call() {
    for (int i = 0; i < timers[0]->getLength(); i++) {
        timers[0]->get(i)->tick();
    }
    // Only the first IntervalTimer is responsible for
    // delete the stopped timers.
    deleteStoppedTimers();
}

void TimerManager::onIntervalTimer1Call() {
    for (int i = 0; i < timers[1]->getLength(); i++) {
        timers[1]->get(i)->tick();
    }
}

void TimerManager::onIntervalTimer2Call() {
    for (int i = 0; i < timers[2]->getLength(); i++) {
        timers[2]->get(i)->tick();
    }
}

// Private

TimerManager::TimerManager() :
    NUM_INTERVALTIMERS(3),
    RESOLUTION_UPPERBOUND(89478485),
    RESOLUTION_LOWERBOUND(100) {

    intervalTimers = new IntervalTimer *[NUM_INTERVALTIMERS];
    resolutions = new int[NUM_INTERVALTIMERS];
    timers = new List<Timer *> *[NUM_INTERVALTIMERS];

    // Lists.
    for (int i = 0; i < NUM_INTERVALTIMERS; i++) {
        timers[i] = new List<Timer *>();
    }
    stoppedTimers = new List<Timer *>();

    // Initiate resolutions with default values.
    for (int i = 0; i < NUM_INTERVALTIMERS; i++) {
        resolutions[i] = 1000000;
    }

    // Create IntervalTimers.
    for (int i = 0; i < NUM_INTERVALTIMERS; i++) {
        intervalTimers[i] = new IntervalTimer();
    }
    
    // Begin the IntervalTimers.
    for (int i = 0; i < NUM_INTERVALTIMERS; i++) {
        beginIntervalTimer(i);
    }    
}

void TimerManager::beginIntervalTimer(int ithRes) {
    // Assume there are three IntervalTimer available.
    switch (ithRes) {
    case 0:
        intervalTimers[0]->begin(ISRIntervalTimer0, resolutions[0]);
        break;
    case 1:
        intervalTimers[1]->begin(ISRIntervalTimer1, resolutions[1]);
        break;
    case 2:
        intervalTimers[2]->begin(ISRIntervalTimer2, resolutions[2]);
        break;
    default:
        break;
    }    
}

void TimerManager::deleteStoppedTimers() {
    if (stoppedTimers->getLength() > 0) {
        for (int i = stoppedTimers->getLength() - 1; i >= 0 ; i++) {
            // Iterate stoppedTimers from the last,
            // because the order of Timers in stoppedTimers
            // is the same in Timers lists and removing from
            // the last is more time efficient.
            Timer *timer = stoppedTimers->get(i);
            // Remove from timers lists.
            for (int j = 0; j < NUM_INTERVALTIMERS; j++) {
                timers[j]->remove(timer);
            }
            // Delete timer.
            delete timer;
        }
        stoppedTimers->clear(); // Clear the remaining pointers.
    }
}

// ISR only used by TimerManager.
// They call the corresponding functions in TimerManager
// to inform it one of the IntervalTimer has called.

void ISRIntervalTimer0() {
    TimerManager::getInstance()->onIntervalTimer0Call();
}

void ISRIntervalTimer1() {
    TimerManager::getInstance()->onIntervalTimer1Call();
}

void ISRIntervalTimer2() {
    TimerManager::getInstance()->onIntervalTimer2Call();
}