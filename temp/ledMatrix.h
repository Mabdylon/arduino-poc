#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <Arduino.h>

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

};

#endif
