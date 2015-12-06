#include <SoftwareSerial.h>

#include "secrets.h"
#include "esp8266.h"

SoftwareSerial serialEsp(2, 3);

Esp8266::Esp8266() {
  serialEsp.begin(115200);
  //Reset the ESP8266
  serialEsp.println("AT+RST");
  delay(100);
  serialEsp.println("AT+CWMODE=1");
  delay(300);
  //Reset the ESP8266
  serialEsp.println("AT+RST");
  //Wait for the WiFi module to bootup
  delay(800);
}


boolean Esp8266::connectWifi() {
  
  String cmd = "AT+CWJAP=\"";
  cmd += Secrets::WIFI_SSID();
  cmd += "\",\"";
  cmd += Secrets::WIFI_PASSWORD();
  cmd += "\"";
  Serial.println(cmd);
  serialEsp.println(cmd);
  delay(500);
  if (serialEsp.find("OK"))
  {
    Serial.println("OK, Connected to WiFi.");
    return true;
  } else
  {
    Serial.println("Can not connect to the WiFi.");
    return false;
  }
}

void Esp8266::talkMode() {
  while (serialEsp.available()) {
      
        Serial.write(serialEsp.read());  // réponse de l'ESP8266 copié dans le moniteur série
    }

    while (Serial.available()) {
        serialEsp.write(Serial.read());  // vos instructions transmises à l'ESP8266
    }
}

void Esp8266::getWebPage() {
  //Open a connection to the web server
  String cmd = "AT+CIPSTART=\"TCP\",\""; //make this command: AT+CPISTART="TCP","192.168.88.35",80
  cmd +=  "93.184.220.20";
  cmd += "\",80";
  Serial.println(cmd);
  serialEsp.println(cmd);
  
  while(serialEsp.available()) {
    Serial.write(serialEsp.read());
  }

  //This is our HTTP GET Request change to the page and server you want to load.
  cmd = "GET /index.html HTTP/1.0\r\n";
  cmd += "Host:  93.184.220.20\r\n\r\n";

  //The ESP8266 needs to know the size of the GET request
  serialEsp.print("AT+CIPSEND=");
  serialEsp.println(cmd.length());
  Serial.println(cmd);
  
  while(serialEsp.available()) {
    Serial.write(serialEsp.read());
  }

  

  //Look for the > prompt from the esp8266
  if (serialEsp.find(">"))
  {
    //Send our http GET request
    serialEsp.println(cmd);
  }
  else
  {
    //Something didn't work...
    serialEsp.println("AT+CIPCLOSE");
  }

  //Check the returned header & web page. Looking for a keyword. I used YES12321

  if (serialEsp.find("Culture"))
  {
    Serial.println("We got the culture word");
  }
  else
  {
    Serial.println("Noting found");
  }
  //Wait a second for everything to settle.
  delay(1000);
  //Be great people and close our connection.
  Serial.println("AT+CIPCLOSE");

  //Introduce a delay timer before we finish and go back to the begining.
  delay (5000);
}
