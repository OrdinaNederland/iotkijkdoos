#include <Arduino.h>
#include <SoftwareSerial.h>
#include "RGB.h"

RGB::RGB(int redPin, int greenPin, int bluePin) {
  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;

  pinMode(_redPin, OUTPUT);
  pinMode(_greenPin, OUTPUT);
  pinMode(_bluePin, OUTPUT);

  //Create one array with all colors 
  allColors[0] = off;
  allColors[1] = red;
  allColors[2] = yellow;
  allColors[3] = green;
  allColors[4] = aqua;
  allColors[5] = blue;
  allColors[6] = purple;
}


void RGB::setColor(char input)  { 
  int index = input - '0';
  int nColors = (sizeof(allColors)/3) / sizeof(int);
  
  if (index >= 0 && index < nColors)  {
    writeColor(allColors[index]);
  }
}

void RGB::writeColor(int rgbValues[3])  {
  analogWrite(_redPin, rgbValues[0]);
  analogWrite(_greenPin, rgbValues[1]);
  analogWrite(_bluePin, rgbValues[2]);
}

//Challenge III "Gradient"
void RGB::showGradient()  {
  int nColors = (sizeof(allColors)/3) / sizeof(int);
  //Add your code here
}

void RGB::reset() {
  writeColor(off);
}




