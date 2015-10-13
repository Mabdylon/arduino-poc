const char DOUT_LED_VERTE = 10;
const char DOUT_LED_ORANGE = 11;
const char DOUT_LED_ROUGE = 12;

void initLEDs() {
  pinMode(DOUT_LED_VERTE, OUTPUT);
  pinMode(DOUT_LED_ORANGE, OUTPUT);
  pinMode(DOUT_LED_ROUGE, OUTPUT);
}

// Permet de passer typeLed (green, orange, red) a l'etat allumée (activated)
void switchLed(char typeLed, boolean activated) {
  if (activated) {
    digitalWrite(typeLed, HIGH);
  } else {
    digitalWrite(typeLed, LOW);
  }
}

void allumeLedRouge() {
  switchLed(DOUT_LED_ROUGE, true);
}

void eteindreLedRouge() {
  switchLed(DOUT_LED_ROUGE, false);
}

void allumeLedOrange() {
  switchLed(DOUT_LED_ORANGE, true);
}

void eteindreLedOrange() {
  switchLed(DOUT_LED_ORANGE, false);
}

void allumeLedVerte() {
  switchLed(DOUT_LED_VERTE, true);
}

void eteindreLedVerte() {
  switchLed(DOUT_LED_VERTE, false);
}



