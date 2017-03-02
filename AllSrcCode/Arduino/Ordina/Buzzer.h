#include "arduino.h"


class Buzzer  {

 public:
  Buzzer(int pin);
  void begin();
  void alarm(Led led1, Led led2);
  void vaderJacob(Led led1, Led led2);
  void yourCustomSound();

 private:
  void checkLedStatus(Led led1, bool isOnLed1, Led led2, bool isOnLed2);
  int _pin;
  
  //Vader Jacob
  int frequence[16] = {523, 587, 659, 523, 659, 699, 784, 784, 880, 784, 699, 659, 523, 523, 659, 523};
  int beginCouplet[4] = {0, 4, 7, 13};
  int endCouplet[4] = {4, 7, 13, 16};
  int nSeconds[4] = {300, 300, 300, 600};
  int nCouplets = (sizeof(endCouplet)/sizeof(int));
  int milliSec = 100;

};

Buzzer::Buzzer(int pin) {
  _pin = pin;
}

void Buzzer::begin()  {
  pinMode(_pin, OUTPUT);
}


void Buzzer::alarm(Led led1, Led led2)  {
  bool statusLed1 = led1.getStatus();
  bool statusLed2 = led2.getStatus();
  
  long startTimer = millis();

  while (millis() - startTimer < 3000) {    //Play alarm for 3 seconds (3000 ms)
      led1.setLed('1');
      led2.setLed('1');
      tone(_pin, 1000, 500);
      delay(500);

      led1.setLed('0');
      led2.setLed('0');
      tone(_pin, 500, 500);
      delay(500);   
  }
  checkLedStatus(led1, statusLed1, led2, statusLed2);
}

void Buzzer::vaderJacob(Led led1, Led led2) {
  bool statusLed1 = led1.getStatus();
  bool statusLed2 = led2.getStatus();
  
  led1.setLed('0');
  led2.setLed('0');
  
  for(int i = 0; i < nCouplets; i++)  {
    for (int j = 0; j < 2; j++)   {
      for (int k = beginCouplet[i]; k < endCouplet[i]; k++) {
        if (k%2 == 0) {
            led1.setLed('1');
            led2.setLed('0');
        }
        else {
            led1.setLed('0');
            led2.setLed('1');
        }
        tone(_pin, frequence[k], milliSec);
        delay(nSeconds[i]);
      }
      delay(300);
    }
    delay(200);
  }
  checkLedStatus(led1, statusLed1, led2, statusLed2);
}



//CHALLENGE: CREATE YOUR CUSTOM SOUND HERE

void Buzzer::yourCustomSound()  {
   //char names[] =     { 'c', 'd', 'e', 'f', '#', 'g', 'a', 'b', 'C', 'D', 'E', 'F', 'G', 'A', 'B' };
  //int frequencies[] = {262, 294, 330, 349, 370, 392, 440, 494, 523, 587, 659, 699, 784, 880, 989};
}



  
void Buzzer::checkLedStatus(Led led1, bool wasOnLed1, Led led2, bool wasOnLed2) {
  if (wasOnLed1) {
    led1.setLed('1');
  }
  else {
    led1.setLed('0');
  }
  
  if (wasOnLed2) {
    led2.setLed('1');
  }
  else {
    led2.setLed('0');
  }
}




