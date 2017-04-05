
class LED {
  
 public:
  LED(int pin); 
  void setLed(bool state);
  bool getState();
  int getPinNumber();
  void reset();
  void flip();
  
 private:
  int _pin; 
  bool isOn = false;
};


