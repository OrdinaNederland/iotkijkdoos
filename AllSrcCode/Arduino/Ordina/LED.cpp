#include <Arduino.h>
#include <SoftwareSerial.h>
#include "LED.h"

LED::LED(int pin)  {
  _pin = pin;
  pinMode(_pin, OUTPUT);
}


void LED::setLed(bool state) {
  isOn = state;
  digitalWrite(_pin, isOn ? HIGH : LOW);
}


int LED::getPinNumber() {
  return _pin;
}

bool LED::getState() {
  return isOn;
}

void LED::reset()  {
  digitalWrite(_pin, LOW);
  isOn = false;
}

