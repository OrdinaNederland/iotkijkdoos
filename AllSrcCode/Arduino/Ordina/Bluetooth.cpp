#include <SoftwareSerial.h>

#include "Bluetooth.h"

Bluetooth::Bluetooth(int rx, int tx) : SoftwareSerial(rx, tx) {}

char Bluetooth::getNextChar() {
  int count = 0;
  char input = '\0';
  
  while (count == 0) {
    if (available() > 0) {
      input = read();
      count++;
    } 
  }
  return input;
}

int Bluetooth::getAngle() {
  String angleStr = "";
  char input = '\0';

  while (input != '\n') {
    if (available() > 0)  {
      input = read();
      if (input != '\n')  {
        angleStr += input;     
      }
    }   
  }
  return angleStr.toInt(); 
};
