const int pinRelay = 5;
const int pinPir = 8;

void setup() {
  pinMode(pinRelay, OUTPUT);
  pinMode(pinPir, INPUT);
  Serial.begin(9600);
}

void loop() {
  int presence = digitalRead(pinPir);
  digitalWrite(pinRelay, (presence ? LOW : HIGH));
  delay(3000);
}
