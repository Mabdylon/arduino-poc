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
Esp8266* esp8266;

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
  ledMatrix = new LedMatrix(ledAPin, ledBPin,
                            ledCPin, ledDPin, ledDataPin, ledClockPin, ledLatchPin);
  Serial.begin(115200);
  esp8266 = new Esp8266();
  boolean connected = false;
  while(!connected) {
    connected = esp8266->connectWifi();
    delay(3000);
  }
}

void loop() {

  //AT+CIPSTART="TCP","93.184.220.20",80
  //  esp8266->talkMode();
    esp8266->getWebPage();
    /*ledMatrix->drawBytes(testPatern1);  
    delay(1000);*/

}
