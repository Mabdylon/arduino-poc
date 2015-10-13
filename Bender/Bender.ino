#include <Servo.h>
#include "Arduino.h"
#include "DriverLEDs.h"
#include "DriverMoteur.h"
#include "DriverUltraSonicSensor.h"
#include "DriverServo.h"
#include "DriverLightSensor.h"
#include "AlgoAntiCollision.h"
#include "AlgoPathLightSensor.h"

void setup() {
  initLEDs();
  initMoteur();
  initServo();
  initUltraSonicSensor();
  initLightSensors();
  Serial.begin(9600);
}

void loop() {
  //algoPathLightSensor();
  //delay(2000);
   algoAntiCollision();
}
