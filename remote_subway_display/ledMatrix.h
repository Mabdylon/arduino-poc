#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <Arduino.h>

class LedMatrix {

 private :

int d;
int c;
int b;
int a;

int data;
int clk;
int latch;

public:

LedMatrix(int, int, int, int, int, int ,int );

void drawBytes(int[]);
void clearAll();
//void shiftOut(int, int, byte);

};

#endif
