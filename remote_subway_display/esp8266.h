#ifndef ESP8266_H
#define ESP8266_H

#include <Arduino.h>

class Esp8266 {

 private :
int rxPin;
int txPin;

String content;

 public :
  
  Esp8266();

  boolean connectWifi();
  void getWebPage();
  void talkMode();

};


#endif
