#include "ledMatrix.h"
//#include "esp8266.h"

const int ledDPin = 12;
const int ledCPin = 11;
const int ledBPin = 10;
const int ledAPin = 9;

const int ledDataPin = 7;
const int ledClockPin = 6;
const int ledLatchPin = 5;

LedMatrix* ledMatrix;

int testPatern1[16] = {
 0b0010000001111100,
 0b0110000010000010,
 0b0010000000000010,
 0b0010000001111100,
 0b0010000010000000,
 0b0010000010000000,
 0b0111000011111110,
 0b0000000000000000,
 0b0111110000001100,
 0b1000001000010100,
 0b0000001000100100,
 0b0011110001000100,
 0b0000001010000100,
 0b1000001011111110,
 0b0111110000000100,
 0b0000000000000000};

int testPatern2[16] = {
 0b0000000000000000,
 0b0111110000001100,
 0b1000001000010100,
 0b0000001000100100,
 0b0011110001000100,
 0b0000001010000100,
 0b1000001011111110,
 0b0111110000000100,
 0b0000000000000000,
 0b0010000001111100,
 0b0110000010000010,
 0b0010000000000010,
 0b0010000001111100,
 0b0010000010000000,
 0b0010000010000000,
 0b0111000011111110};

void setup() {

  Serial.begin(9600);
  ledMatrix = new LedMatrix(ledAPin, ledBPin,
                            ledCPin, ledDPin, ledDataPin, ledClockPin, ledLatchPin);

}

void loop() {
  /*digitalWrite(11, HIGH);
   digitalWrite(5, 0);
  shiftOut(7, 6, 0);
  shiftOut(7, 6, 0);
  digitalWrite(5, 1);
  delay(200);*/

  for(int i = 0; i <100; i++) {
    ledMatrix->drawBytes(testPatern1);  
  }
  for(int i = 0; i <100; i++) {
    ledMatrix->drawBytes(testPatern2);  
  }
  

}
