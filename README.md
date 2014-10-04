# TimerManager

## Create as many timers as you want

On Teensy, at most three `IntervalTimer`s can be used at one time. `TimerManager`, which extends from `IntervalTimer`, enables you to create as many timers as you want. You can also make any class's member function as callback function, as long as the class implements the `TimerListener` interface.

## Project status

Basic functions are completed, though not thoroughly tested. Manuals will be available soon. (2014/10/4)

## See also

- IntervalTimer on Github, https://github.com/loglow/IntervalTimer
