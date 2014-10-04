#include "TimerManager.h"
#include "List.h"

// The class which implements TimerListener.
#include "TimerToSerial.h"

void setup() {
    TimerToSerial::beginSerial(9600);
    
    // Get TimerManager instance.
    TimerManager *timerManager = TimerManager::getInstance();

    // 1st arg: set the first resolution.
    // 2nd arg: set it to 10000 microseconds, or 0.01 second.
    timerManager->setResolution(0, 10000);

    // 1st arg: use the first resolution.
    // 2nd arg: set the timer period to 1 second.
    // 3rd arg: let the timer run 10 periods.
    // 4th arg: the TimerListener to call when the timer calls at each period's end.
    timerManager->addTimerAndStart(0, 3, 7, new TimerToSerial(0));

    // Add other timers.
    timerManager->addTimerAndStart(0, 4, 5, new TimerToSerial(1));
    timerManager->addTimerAndStart(0, 5, 4, new TimerToSerial(2));
}

void loop() {
}