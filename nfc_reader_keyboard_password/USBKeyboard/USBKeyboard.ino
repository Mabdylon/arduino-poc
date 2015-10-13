#include "Keyboard.h"
#include "HID.h"

boolean intruderDetected = false;


void setup() {
  // Start the Serial1 which is connected with the IO MCU.
  // Make sure both baud rates are the same
  // you can go up to 2000000 for very fast data transmission.
  Serial1.begin(115200);
  
  // Sends a clean report to the host. This is important on any Arduino type.
  Keyboard.begin();

  // Start the USB Serial for debugging
  Serial.begin(115200);
  Serial.print("I'm alive");
}

void loop() {
  // Check if any Serial data from the IO MCU was received
  char serialString = Serial1.read();
  Serial.println(serialString);
  if (serialString == 'i') {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('l');
    Keyboard.releaseAll();
    Keyboard.press(KEY_BACKSPACE);
    Keyboard.releaseAll();
    Keyboard.press(KEY_RIGHT_CTRL);
    Keyboard.press(KEY_RIGHT_ALT);
    Keyboard.press(KEY_DELETE);
    Keyboard.releaseAll();
    delay(600);
    Keyboard.print("yourpassword!");
    Keyboard.write(KEY_RETURN);
    if (intruderDetected) {
      delay(2000);
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.releaseAll();
      delay(1000); 
      Keyboard.println("notepad");
      Keyboard.write(KEY_RETURN);
      delay(2000);
      Keyboard.println("TENTATIVE D'INTRUSION DETECTEE");
      intruderDetected = false;
    }
  } else if (serialString == 'o') {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('l');
    Keyboard.releaseAll();
  } else if (serialString == 'b') {
    intruderDetected = true;
  }
  delay(200);
}
