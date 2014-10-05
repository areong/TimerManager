# TimerManager

## Run as many timers as you want

On Teensy, at most three `IntervalTimer`s can be active at one time. `TimerManager`, which benefits from `IntervalTimer`, enables you to run as many timers as you want simultaneously. Moreover, you can also set any class's member function as a callback function, as long as the class implements the `TimerListener` interface.

### Example

First implements the `TimerListener` in `DoSomething.h` and override `onTimerCall()`:

``` cpp
#include "TimerListener.h"

class DoSomething : public TimerListener {
public:
    void onTimerCall(); // Remember to write the function body.
};
```

Then in `main.ino`:

``` cpp
// 1.
#include "TimerManager.h"
#include "List.h"
#include "DoSomething.h"

void setup() {
    // 2.
    TimerManager *timerManager = TimerManager::getInstance();
    // 3.
    timerManager->setResolution(0, 100000);
    // 4.
    timerManager->addTimerAndStart(0, 1, 10, new DoSomething());
}

void loop() {
}
```

1. Include the first two headers for TimerManager. Then include the third, which is the class you want to call when timer calls.
2. Get the instance of `TimerManager`.
3. Set the first resolution to 0.1 second. The period of a timer will be a interger multiple of the resolution.
4. Add a timer using the first resolution, with period of 1 second, running 10 periods, and listened by `DoSomething`. The timer starts immediately.

In this example, a timer will call `DoSomething::onTimerCall()` every one second and call ten times totally.

For detailed information please refer to the user manual (available soon).

## Project status

Basic functions are completed, though not thoroughly tested. Manuals will be available soon. (2014/10/4)

## See also

- IntervalTimer on Github, https://github.com/loglow/IntervalTimer
