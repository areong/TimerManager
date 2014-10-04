#include "TimerToSerial.h"
#include "Arduino.h"

void TimerToSerial::beginSerial(int baud) {
    Serial.begin(baud);
    Serial.println("Serial open.");
}

TimerToSerial::TimerToSerial(int id) {
    this->id = id;
}

TimerToSerial::~TimerToSerial() {

}

void TimerToSerial::onTimerCall() {
    Serial.print("Timer ");
    Serial.print(id);
    Serial.print(", ");
    Serial.print(millis());
    Serial.print(" ms\n");
}