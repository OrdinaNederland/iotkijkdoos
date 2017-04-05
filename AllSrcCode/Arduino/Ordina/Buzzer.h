

class Buzzer  {
 
 public:
  Buzzer(int pin);
  void alarm(LED led1, LED led2);
  void vaderJacob(LED led1, LED led2);
  void customSound();

 private:
  void setLEDToPreviousState(LED led1, bool wasOnLED1, LED led2, bool wasOnLED2);
  int _pin;
  
  //Vader Jacob
  int frequence[16] = {523, 587, 659, 523, 659, 699, 784, 784, 880, 784, 699, 659, 523, 523, 659, 523};
  int beginCouplet[4] = {0, 4, 7, 13};
  int endCouplet[4] = {4, 7, 13, 16};
  int secondsRest[4] = {300, 300, 300, 600};
  int nCouplets = (sizeof(endCouplet)/sizeof(int));
  int milliSec = 100;
};





