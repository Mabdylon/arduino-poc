//Pin connected to ST_CP of 74HC595
int latchPin = 5;
//Pin connected to SH_CP of 74HC595
int clockPin = 6;
////Pin connected to DS of 74HC595
int dataPin = 7;
int DPin = 12;
int CPin = 11;
int BPin = 10;
int APin = 9;

//my web site, replace with yours
#define DST_IP "93.184.220.20"

//Define the pin for the on board LED
int led = 13;

byte off = B00000000;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT); // make the clock pin an output
  pinMode(dataPin, OUTPUT);
  pinMode(DPin, OUTPUT);
  pinMode(BPin, OUTPUT);
  pinMode(CPin, OUTPUT);
  pinMode(APin, OUTPUT);

  //Enable the Onboard LED to act as a Status indicator light
  pinMode(led, OUTPUT);
  //Set the speed for communicating with the ESP8266 module
  Serial.begin(9600);
  //Send a series of flashes to show us we are in the bootup phase.
  //Reset the ESP8266
  Serial.println("AT+RST");
  //Wait for the WiFi module to bootup
  delay(1500);
  //Switch the chip to "client" mode
  Serial.println("AT+CWMODE=1");
  //Connect to our Wireless network NOTE: change SSID to your wireless
  //network and PASSWORD to the key used to join the network.
  Serial.println("AT+CWJAP=\"SSID\",\"PASS\"");
  //Once again blink some lights because it is fun!
  blinkcode ();
}

void loop() {

  //Open a connection to the web server
  String cmd = "AT+CIPSTART=\"TCP\",\""; //make this command: AT+CPISTART="TCP","93.184.220.20",80
  cmd += DST_IP;
  cmd += "\",80";
  Serial.println(cmd);

  //wait a little while for 'Linked'
  delay(300);

  //This is our HTTP GET Request change to the page and server you want to load.
  cmd = "GET /index.html HTTP/1.0\r\n";
  cmd += "Host: 93.184.220.20\r\n\r\n";

  //The ESP8266 needs to know the size of the GET request
  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length());

  //Look for the > prompt from the esp8266
  if (Serial.find(">"))
  {
    //Send our http GET request
    Serial.println(cmd);
    blinkcode ();
  }
  else
  {
    //Something didn't work...
    Serial.println("AT+CIPCLOSE");
  }

  //Check the returned header & web page. Looking for a keyword. I used YES12321

  if (Serial.find("mo"))
  {
    Serial.print("win");
    //If the string was found we know the page is up and we turn on the LED status
    //light to show the server is ONLINE
    digitalWrite(led, HIGH);
  }
  else
  {
    //If the string was not found then we can assume the server is offline therefore
    //we should turn of the light.
    digitalWrite(led, LOW);
  }
  //Wait a second for everything to settle.
  delay(1000);
  //Be great people and close our connection.
  Serial.println("AT+CIPCLOSE");

  //Introduce a delay timer before we finish and go back to the begining.
  delay (5000);

}

void blinkcode ()
{
  //Simply loop a few times flashing the status light (this is used during boot up)
  int i;
  for (i = 1; i <= 10; i++) {
    delay (100);
    digitalWrite(led, HIGH);
    delay (100);
    digitalWrite(led, LOW);
  }
}

void testLedLCD() {
  //function that blinks all the LEDs
  //gets passed the number of blinks and the pause time
  blinkAll_2Bytes(1, 500);

  // light each pin one by one using a function A
  for (int j = 0; j < 8; j++) {

    digitalWrite(DPin, (j % 2 == 0));
    digitalWrite(CPin, (j % 3 == 0));
    digitalWrite(BPin, (j % 4 == 0));
    digitalWrite(APin, (j % 8 == 0));
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //red LEDs
    lightShiftPinA(7 - j);
    //green LEDs
    lightShiftPinA(j);
    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
    delay(1000);
  }

  // light each pin one by one using a function A
  for (int j = 0; j < 8; j++) {
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //red LEDs
    lightShiftPinB(j);
    //green LEDs
    lightShiftPinB(7 - j);
    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
    delay(1000);
  }

}

//This function uses bitwise math to move the pins up
void lightShiftPinA(int p) {
  //defines a local variable
  int pin;

  //this is line uses a bitwise operator
  //shifting a bit left using << is the same
  //as multiplying the decimal number by two.
  pin = 1 << p;

  //move 'em out
  shiftOut(dataPin, clockPin, pin);

}

//This function uses that fact that each bit in a byte
//is 2 times greater than the one before it to
//shift the bits higher
void lightShiftPinB(int p) {
  //defines a local variable
  int pin;

  //start with the pin = 1 so that if 0 is passed to this
  //function pin 0 will light.
  pin = 1;

  for (int x = 0; x < p; x++) {
    pin = pin * 2;
  }
  //move 'em out
  shiftOut(dataPin, clockPin, pin);
}


// the heart of the program
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first,
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i = 0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights.
  for (i = 7; i >= 0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1 << i) ) {
      pinState = 1;
    }
    else {
      pinState = 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}


//blinks both registers based on the number of times you want to
//blink "n" and the pause between them "d"
//starts with a moment of darkness to make sure the first blink
//has its full visual effect.
void blinkAll_2Bytes(int n, int d) {
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0);
  shiftOut(dataPin, clockPin, 0);
  digitalWrite(latchPin, 1);
  delay(200);
  for (int x = 0; x < n; x++) {
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 255);
    shiftOut(dataPin, clockPin, 255);
    digitalWrite(latchPin, 1);
    delay(d);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 0);
    shiftOut(dataPin, clockPin, 0);
    digitalWrite(latchPin, 1);
    delay(d);
  }
}


