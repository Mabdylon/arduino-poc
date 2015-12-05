#include "unlocker.h"

Unlocker::Unlocker(int unlockerPIN) {

  pin = unlockerPIN;
  servo.attach(pin);
  
  servo.write(positionLeft);
  
}

void Unlocker::turn() {
  servo.write(positionRight, servoSpeed, true);
  servo.write(positionLeft, servoSpeed, true);
}

