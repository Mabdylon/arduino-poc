const char PWM_SERVO = 9;

Servo servo;
int positionDuServo = 90;

const int SERVO_LOOK_LEFT = 45;
const int SERVO_LOOK_FORWARD = 90;
const int SERVO_LOOK_RIGHT = 135;
const int DELAY_TO_LOOK = 250;

void initServo() {
  servo.attach(PWM_SERVO);
  servo.write(positionDuServo);
}

void regardeAGauche() {
  servo.write(SERVO_LOOK_LEFT);
  Serial.println("Regarde a gauche");
  delay(DELAY_TO_LOOK);
}

void regardeADroite() {
  servo.write(SERVO_LOOK_RIGHT);
  Serial.println("Regarde a droite");
  delay(DELAY_TO_LOOK);
  
}

void regardeToutDroit() {
  servo.write(SERVO_LOOK_FORWARD);
  Serial.println("Regarde tout droit");
  delay(DELAY_TO_LOOK);
}

void testServo() {
  regardeToutDroit();
  delay(DELAY_TO_LOOK);
  regardeADroite();
  delay(DELAY_TO_LOOK);
  regardeToutDroit();
  delay(DELAY_TO_LOOK);
  regardeAGauche();
  delay(DELAY_TO_LOOK);
}
