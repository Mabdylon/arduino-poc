#include "ledMatrix.h"

LedMatrix::LedMatrix(int a, int b, int c,
                     int d, int data, int clk, int latch) {

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
    digitalWrite(latch, LOW);
    shiftOut(data, clk, MSBFIRST, 0);
    shiftOut(data, clk, MSBFIRST, 0);
    digitalWrite(latch, HIGH);
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

void LedMatrix::clearAll() {
  digitalWrite(latch, LOW);
  shiftOut(data, clk, MSBFIRST, 0);
  shiftOut(data, clk, MSBFIRST, 0);
  digitalWrite(latch, HIGH);
}
