
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>

#include "LED.h"
#include "RGB.h"
#include "Buzzer.h"
#include "ServoMotor.h"
#include "Bluetooth.h"

//Instance variables with the pin numbers as parameters
Bluetooth bluetooth(10, 11);   //RX BLE to TX arduino(11), TX BLE to RX arduino(10)

ServoMotor servo(3);
Buzzer buzzer(4);
RGB rgbLed(9, 6, 5);
LED led1(8);
LED led2(12);

int angle;

void setup()  {
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  if (bluetooth.available() > 0) {
    char input = bluetooth.read(); 
    
    switch (input)  {
    case 'a':
      led1.setLed(bluetooth.getNextChar() == '1');
      break;
    case 'b':
      led2.setLed(bluetooth.getNextChar() == '1');
      break;
    case'c':
      rgbLed.setColor(bluetooth.getNextChar());
      break;
    case 'd':
      buzzer.alarm(led1, led2);
      break;
    case 'e':
      buzzer.vaderJacob(led1, led2);
      break;
    case 'f':
      buzzer.customSound();
      break;
    case 'g':
      angle = bluetooth.getAngle();
      servo.setAngle(angle, 50);
      break;
    case 'h':
      rgbLed.showGradient();
      break;
    case 'i':
      //Add here the call to the method for challenge IV
      break;
    case 'r':
      resetAllComponents();
      break;
    default:
      break;
    }
  }   
}

void resetAllComponents()  {
  led1.reset();
  led2.reset();
  rgbLed.reset();
  servo.reset();
  bluetooth.println("y"); //Central is waiting for "y" before it will disconnect
}









