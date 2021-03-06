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
    shiftOut(data, clk, LSBFIRST, highByte(pattern[i]));
    shiftOut(data, clk, LSBFIRST, lowByte(pattern[i]));
    digitalWrite(latch, HIGH);
    delay(1);
  }
}

void LedMatrix::clearAll() {
  digitalWrite(latch, LOW);
    shiftOut(data, clk, MSBFIRST, 0);
    shiftOut(data, clk, MSBFIRST, 0);
    digitalWrite(latch, HIGH);
}
