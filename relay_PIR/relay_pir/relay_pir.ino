#include <JeeLib.h>

const int pinRelay = 2;
const int pinPresence = 4;
int presence = -1;
int lastPresence = -1;

ISR(WDT_vect) { Sleepy::watchdogEvent(); }

void setup() {
  // put your setup code here, to run once:
pinMode(pinRelay,OUTPUT);
pinMode(pinPresence,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  presence =  digitalRead(pinPresence);
  if(lastPresence != presence) {
    digitalWrite(pinRelay, (!presence));    
    lastPresence = presence;
  }
  Sleepy::loseSomeTime(1000);
}
