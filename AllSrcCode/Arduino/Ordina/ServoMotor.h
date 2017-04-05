
/*
 * Servo angle: 0-179 (180 degrees).
 * Servo will be attached and detached in the setAngle() method, otherwise the servo is moving while changing RGB light.
 */

class ServoMotor  {
  
  public:
    ServoMotor(int pin);
    void setAngle(int angle, int milliSec);
    void reset();

  private:
    int _pin;
    Servo servo;

    const int maxAngle = 179;
};
