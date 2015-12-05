#include "ledMatrix.h"

LedMatrix::LedMatrix(int aPin, int bPin, int cPin,
                     int dPin, int dataPin, int clkPin, int latchPin) {
  d = dPin;
  c = cPin;
  b = bPin;
  a = aPin;
  data = dataPin;
  clk = clkPin;
  latch = latchPin;

  pinMode (clk, OUTPUT);
  pinMode (data, OUTPUT);
  pinMode (latch, OUTPUT);
  pinMode (a, OUTPUT);
  pinMode (b, OUTPUT);
  pinMode (c, OUTPUT);
  pinMode (d, OUTPUT);

}

void LedMatrix::drawBytes(int pattern[16]) {
  for (byte i = 0; i < 16; i++) {
    digitalWrite(a, bitRead(i, 0));
    digitalWrite(b, bitRead(i, 1));
    digitalWrite(c, bitRead(i, 2));
    digitalWrite(d, bitRead(i, 3));
    digitalWrite(latch, LOW);
    shiftOut(data, clk, MSBFIRST, highByte(pattern[i]));
    shiftOut(data, clk, MSBFIRST, lowByte(pattern[i]));
    digitalWrite(latch, HIGH);
    delay(1);
  }
}

/*void LedMatrix::shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first,
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i = 0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights.
  for (i = 7; i >= 0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1 << i) ) {
      pinState = 1;
    }
    else {
      pinState = 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }
}*/

void LedMatrix::clearAll() {
  digitalWrite(latch, LOW);
    shiftOut(data, clk, MSBFIRST, 0);
    shiftOut(data, clk, MSBFIRST, 0);
    digitalWrite(latch, HIGH);
}
