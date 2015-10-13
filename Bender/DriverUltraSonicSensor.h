const char DIN_ULTRASONIC_ECHO = 12;
const char DOUT_ULTRASONIC_TRIG = 13;

float distance;

void initUltraSonicSensor() {
  pinMode(DIN_ULTRASONIC_ECHO, INPUT);
  pinMode(DOUT_ULTRASONIC_TRIG, OUTPUT);
}

// Ecrit sur le trigger ULTRASONIC en HIGH ou en LOW
void digitalWriteEchoHigh(boolean high) {
  digitalWrite(DOUT_ULTRASONIC_TRIG, (high ? HIGH : LOW));
}

// Envoi une impulsion de 10 ms au trigger pour demander une mesure
void triggerMesure() {
  digitalWriteEchoHigh(false);
  delayMicroseconds(2);
  digitalWriteEchoHigh(true);
  delayMicroseconds(10);
  digitalWriteEchoHigh(false);
}

// Retourne la distance mesuree en cm
float getDistance() {
  triggerMesure();
  return  (pulseIn(DIN_ULTRASONIC_ECHO, HIGH) / 0.58) / 100;
}

boolean laVoieEstLibre() {
  distance = getDistance();
  Serial.println(distance);
  return (distance > 30);
}

void testUltraSonic() {
  float distance2 = getDistance();
  Serial.println(distance2);
  delay(300);
}
