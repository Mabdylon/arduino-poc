#include "secrets.h"
#include "esp8266.h"

Esp8266::Esp8266() {
  Serial.begin(9600);
  //Reset the ESP8266
  Serial.println("AT+RST");
  //Wait for the WiFi module to bootup
  delay(800);
}


void Esp8266::connectWifi() {
  //Switch the chip to "client" mode
  Serial.println("AT+CWMODE=1");
  //Connect to our Wireless network NOTE: change SSID to your wireless
  //network and PASSWORD to the key used to join the network.
  String connectCmd = "AT+CWJAP=\""+Secrets::WIFI_SSID()+"\",\""+Secrets::WIFI_PASSWORD()+"\"";
  Serial.println(connectCmd);
  //Once again blink some lights because it is fun!
}

void Esp8266::getWebPage() {
  Serial.println("get a web page");
}

