#include "ledMatrix.h"
#include "esp8266.h"

const int ledDPin = 12;
const int ledCPin = 11;
const int ledBPin = 10;
const int ledAPin = 9;

const int ledDataPin = 7;
const int ledClockPin = 6;
const int ledLatchPin = 5;

LedMatrix* ledMatrix;

void setup() {

  Serial.begin(9600);
  ledMatrix = new LedMatrix(ledAPin, ledBPin,
                            ledCPin, ledDPin, ledDataPin, ledClockPin, ledLatchPin);

}

void loop() {

  ledMatrix->drawBytes(testPatern1);
  delay(1000);
  ledMatrix->clearAll();
  delay(1000);
  ledMatrix->drawBytes(testPatern2);
  delay(1000);
}
