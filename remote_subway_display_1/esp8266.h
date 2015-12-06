#ifndef ESP8266_H
#define ESP8266_H

#include <Arduino.h>

class Esp8266 {

 private :

String content;

 public :
  
  Esp8266();

  void connectWifi();
  void getWebPage();

};


#endif
