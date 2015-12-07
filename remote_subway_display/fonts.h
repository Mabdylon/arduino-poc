#ifndef FONTS_H
#define FONTS_H

#include <Arduino.h>

class Fonts
{
  private:

    static int numbers[][16];

  public:
    static int * getNumber(int);
};

#endif
