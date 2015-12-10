#include <ESP8266.h>
#include <ESP8266Client.h>

#include <SoftwareSerial.h>

#include "ESP8266.h"

SoftwareSerial esp8266Serial = SoftwareSerial(2, 3);
ESP8266 wifi = ESP8266(esp8266Serial);
String data;

void setup()
{
  Serial.begin(115200);
  esp8266Serial.begin(115200);
  delay(1000);
  esp8266Serial.write("AT\n");
  delay(100);
  
  Serial.println("begin setup");
  while (esp8266Serial.available() > 0 ) {
    char ch = esp8266Serial.read();
      Serial.println(ch);
    data = "";
  }
  Serial.println("end setup");
}

void loop()
{
  
  while (Serial.available() > 0 ) {
    int toSend = Serial.read();
    esp8266Serial.write(toSend);
    Serial.write(toSend);
  }
  while (esp8266Serial.available() > 0 ) {
    char ch = esp8266Serial.read();
    data.concat(ch);
      Serial.println(data);
    data = "";
    delay(100);
  }
}



