class Bluetooth: public SoftwareSerial {
  
  public:
   Bluetooth(int rx, int tx);
   char getNextChar();
   int getAngle();

  
};

