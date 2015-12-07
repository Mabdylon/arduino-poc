#include <doxygen.h>
#include <ESP8266.h>

#include "ledMatrix.h"
#include "secrets.h"
#include "fonts.h"

#define HOST_NAME   "www.baidu.com"
#define HOST_PORT   (80)


const int ledDPin = 12;
const int ledCPin = 11;
const int ledBPin = 10;
const int ledAPin = 9;

const int ledDataPin = 7;
const int ledClockPin = 6;
const int ledLatchPin = 5;

LedMatrix* ledMatrix;
SoftwareSerial mySerial(2, 3); /* RX:D2, TX:D3 */
ESP8266 wifi(mySerial);

void setup() {
  ledMatrix = new LedMatrix(ledAPin, ledBPin,
                            ledCPin, ledDPin, ledDataPin, ledClockPin, ledLatchPin);
  /*Serial.begin(115200);

    Serial.print("setup begin\r\n");

    Serial.print("FW Version:");
    Serial.println(wifi.getVersion().c_str());

    if (wifi.setOprToStationSoftAP()) {
        Serial.print("to station + softap ok\r\n");
    } else {
        Serial.print("to station + softap err\r\n");
    }

    if (wifi.joinAP(Secrets::WIFI_SSID(), Secrets::WIFI_PASSWORD())) {
        Serial.print("Join AP success\r\n");

        Serial.print("IP:");
        Serial.println( wifi.getLocalIP().c_str());       
    } else {
        Serial.print("Join AP failure\r\n");
    }
    
    if (wifi.disableMUX()) {
        Serial.print("single ok\r\n");
    } else {
        Serial.print("single err\r\n");
    }
    
    Serial.print("setup end\r\n");*/

}

void loop() {
  /*Serial.println("begin loop");
  uint8_t buffer[1024] = {0};

    if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
        Serial.print("create tcp ok\r\n");
    } else {
        Serial.print("create tcp err\r\n");
    }

    char *hello = "GET / HTTP/1.1\r\nHost: www.baidu.com\r\nConnection: close\r\n\r\n";
    wifi.send((const uint8_t*)hello, strlen(hello));

    uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);
    if (len > 0) {
        Serial.print("Received:[");
        for(uint32_t i = 0; i < len; i++) {
            Serial.print((char)buffer[i]);
        }
        Serial.print("]\r\n");
    }

    if (wifi.releaseTCP()) {
        Serial.print("release tcp ok\r\n");
    } else {
        Serial.print("release tcp err\r\n");
    }*/


  //AT+CIPSTART="TCP","93.184.220.20",80
  //  esp8266->talkMode();
  //  esp8266->getWebPage();

  for(int i = 0; i < 9; i++) {
      for(int j = 0; j < 250; j++) {
        ledMatrix->drawBytes(Fonts::getNumber(i));        
      }
  }
  
}
