#ifndef UNLOCKER_H
#define UNLOCKER_H

#include <Arduino.h>
#include <VarSpeedServo.h>

class Unlocker {

private:
  int pin;
  VarSpeedServo servo;
  int positionLeft = 0;
  int positionRight = 180;
  int servoSpeed = 70;
  boolean tangoCount = 0;
/*  
  bool forward;
  int intervalForward;
  int intervalBackward;
  int moveForward;
  int moveBackward;
  unsigned int lastTime;
*/
public:
  Unlocker(int);

  void turn();

};

#endif
