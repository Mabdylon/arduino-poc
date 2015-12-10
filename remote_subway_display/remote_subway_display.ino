#include <SoftwareSerial.h>

#include "ledMatrix.h"
#include "secrets.h"
#include "fonts.h"


const int ledDPin = 12;
const int ledCPin = 11;
const int ledBPin = 10;
const int ledAPin = 9;

const int ledDataPin = 7;
const int ledClockPin = 6;
const int ledLatchPin = 5;

LedMatrix* ledMatrix;
SoftwareSerial mySerial(2, 3); /* RX:D2, TX:D3 */

void setup() {
  ledMatrix = new LedMatrix(ledAPin, ledBPin,
                            ledCPin, ledDPin, ledDataPin, ledClockPin, ledLatchPin);

}

void loop() {
  
  //AT+CIPSTART="TCP","93.184.220.20",80
  //  esp8266->talkMode();
  //  esp8266->getWebPage();

  for(int i = 0; i < 9; i++) {
      for(int j = 0; j < 250; j++) {
        ledMatrix->drawBytes(Fonts::getNumber(i));        
      }
  }
  
}
