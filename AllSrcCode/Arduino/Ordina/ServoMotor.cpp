#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include "ServoMotor.h"

ServoMotor::ServoMotor(int pin) {
  _pin = pin;
}

void ServoMotor::setAngle(int angle, int milliSec)  {
  servo.attach(_pin); 
  servo.write(maxAngle - angle);
  delay(milliSec);
  servo.detach();
}

void ServoMotor::reset()  {
  setAngle(maxAngle, 400);
}

