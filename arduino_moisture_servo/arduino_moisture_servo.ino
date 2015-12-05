#include <VarSpeedServo.h>
#include <JeeLib.h>

const int pinMoistureAnalog = A0;
const int pinMoistureDigital = 5;
const int pinSerovMesure = 7;
const int pinSerovAlert = 6;
VarSpeedServo servoMesure;
VarSpeedServo servoAlert;
int mappedMoisture = 0;
int lastMappedMoisture = 0;
int digitalMoisture = 0;
int analogMoisture = 600;
int maxMappedMoisture = 950;
int minMappedMoisture = 350;
int amountNeededToMove = 5;
boolean DEBUG = false;

ISR(WDT_vect) {
  Sleepy::watchdogEvent();
}

void debugOutput() {
  if (DEBUG) {
    Serial.print("Last mapped moisture : ");
    Serial.println(lastMappedMoisture);
    Serial.print("MappedMoisture : ");
    Serial.println(mappedMoisture);
    Serial.print("Analog Moisture : ");
    Serial.println(analogMoisture);
    Serial.print("Digital Moisture : ");
    Serial.println(digitalMoisture);
    Serial.println("-----------------------");
  }
}

void readInputs() {
  analogMoisture = analogRead(pinMoistureAnalog);
  digitalMoisture = digitalRead(pinMoistureDigital);
}

void ifExceedModifyMinMax() {
  if (analogMoisture < minMappedMoisture) {
    minMappedMoisture = analogMoisture;
  }
  if (analogMoisture > maxMappedMoisture) {
    maxMappedMoisture = analogMoisture;
  }
}

void computeMappedMoisture() {
  mappedMoisture = map(analogMoisture, minMappedMoisture, maxMappedMoisture, 0, 180);
}

void ifDiffIsEnoughMoveServo() {
  if (abs(lastMappedMoisture - mappedMoisture) > amountNeededToMove) {
    servoMesure.write(mappedMoisture, 20, true);
    lastMappedMoisture = mappedMoisture;
    int flagAlertPosition = (digitalMoisture == 1 ? 90 : 180);
    servoAlert.write(flagAlertPosition, 50, true);
  }
}

void setup() {
  pinMode(pinMoistureAnalog, INPUT);
  pinMode(pinMoistureDigital, INPUT);
  servoMesure.attach(pinSerovMesure);
  servoAlert.attach(pinSerovAlert);
  Serial.begin(9600);
}

void loop() {

  readInputs();
  ifExceedModifyMinMax();
  computeMappedMoisture();
  debugOutput();
  ifDiffIsEnoughMoveServo();


  Sleepy::loseSomeTime(3000);


}



