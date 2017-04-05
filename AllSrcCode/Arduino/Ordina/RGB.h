class RGB {
  
  public:
    RGB(int redPin, int greenPin, int bluePin);
    void setColor(char input);
    void showGradient();
    void reset();

  private:
     int _redPin;
     int _greenPin;
     int _bluePin;

     const int off[3] = {0, 0, 0};
     const int red[3] = {255, 0, 0};
     const int yellow[3] = {255, 255, 0};
     const int green[3] = {0, 255, 0}; 
     const int aqua[3] = {0, 255, 255}; 
     const int blue[3] = {0, 0, 255}; 
     const int purple[3] = {255, 0, 255}; 
     int *allColors[7];

     void writeColor(int rgbValues[3]);
     
};


