
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX = 10, TX = 11

void setup()
{
    Serial.begin(115200);
    mySerial.begin(115200);
    Serial.println("begin");
}

void loop()
{
  
    while (mySerial.available()) {
      
        Serial.write(mySerial.read());  // réponse de l'ESP8266 copié dans le moniteur série
    }

    while (Serial.available()) {
        mySerial.write(Serial.read());  // vos instructions transmises à l'ESP8266
    }
}
