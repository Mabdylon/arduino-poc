const char DOUT_MOTEUR_GAUCHE_1 = 3;
const char DOUT_MOTEUR_GAUCHE_2 = 4;
const char DOUT_MOTEUR_GAUCHE_EN = 5;

const char DOUT_MOTEUR_DROITE_1 = 6;
const char DOUT_MOTEUR_DROITE_2 = 7;
const char DOUT_MOTEUR_DROITE_EN = 8;

const int MOTOR_DC_VELOCITY_GAUCHE = 250;
const int MOTOR_DC_VELOCITY_DROITE = 128;
const int MOTOR_DC_ROUE_DROITE = 1;
const int MOTOR_DC_ROUE_GAUCHE = 2;
const int MOTOR_DC_DELAY_PIVOT = 200;
const int MOTOR_DC_DELAY_PIVOT_180 = 500;

boolean enMouvement = false;

void initMoteur() {
  pinMode(DOUT_MOTEUR_GAUCHE_1, OUTPUT);
  pinMode(DOUT_MOTEUR_GAUCHE_2, OUTPUT);
  pinMode(DOUT_MOTEUR_GAUCHE_EN, OUTPUT);
  
  pinMode(DOUT_MOTEUR_DROITE_1, OUTPUT);
  pinMode(DOUT_MOTEUR_DROITE_2, OUTPUT);
  pinMode(DOUT_MOTEUR_DROITE_EN, OUTPUT);
  
  digitalWrite(DOUT_MOTEUR_GAUCHE_1, LOW);
  digitalWrite(DOUT_MOTEUR_GAUCHE_2, LOW);
  analogWrite(DOUT_MOTEUR_GAUCHE_EN, 0);
  
  digitalWrite(DOUT_MOTEUR_DROITE_1, LOW);
  digitalWrite(DOUT_MOTEUR_DROITE_2, LOW);
  analogWrite(DOUT_MOTEUR_DROITE_EN, 0);
}

// Permet un mouvement de typeRoue GAUCHE/DROITE dans le sensMouvement Avant/Arriere
void mouvementRoue(int typeRoue, boolean sensMouvement) {
  enMouvement = true;
  int DOUT1 = (sensMouvement ? HIGH : LOW);
  int DOUT2 = (sensMouvement ? LOW : HIGH);
  if (typeRoue == MOTOR_DC_ROUE_DROITE) {
    digitalWrite(DOUT_MOTEUR_GAUCHE_1, DOUT1);
    digitalWrite(DOUT_MOTEUR_GAUCHE_2, DOUT2);
    analogWrite(DOUT_MOTEUR_GAUCHE_EN, MOTOR_DC_VELOCITY_GAUCHE);
  } else if (typeRoue ==  MOTOR_DC_ROUE_GAUCHE) {
    digitalWrite(DOUT_MOTEUR_DROITE_1, DOUT1);
    digitalWrite(DOUT_MOTEUR_DROITE_2, DOUT2);
    analogWrite(DOUT_MOTEUR_DROITE_EN, MOTOR_DC_VELOCITY_DROITE);
  }
  enMouvement = false;
}

void avanceEnLigneDroite() {
  mouvementRoue(MOTOR_DC_ROUE_DROITE, true);
  mouvementRoue(MOTOR_DC_ROUE_GAUCHE, true);
  Serial.println("avance tout droit");
}

void arret() {
  analogWrite(DOUT_MOTEUR_DROITE_EN, 0);
  analogWrite(DOUT_MOTEUR_GAUCHE_EN, 0);
  Serial.println("arret");
  enMouvement = false;
}

void pivoter(boolean gauche, int delay_pivot) {
  mouvementRoue(MOTOR_DC_ROUE_DROITE, (gauche ? false : true));
  mouvementRoue(MOTOR_DC_ROUE_GAUCHE, (gauche ? true : false));
  delay(delay_pivot);
}

void pivoteAGaucheFourtyFive() {
  Serial.println("pivot gauche");
  pivoter(true, MOTOR_DC_DELAY_PIVOT);
}

void pivoteADroiteFourtyFive() {
  Serial.println("pivot droit");
  pivoter(false, MOTOR_DC_DELAY_PIVOT);
}

void pivoteAGauche() {
  Serial.println("pivot gauche");
  pivoter(true, 0);
}

void pivoteADroite() {
  Serial.println("pivot droit");
  pivoter(false, 0);
}

void demiTour() {
  Serial.println("demi tour !");
  pivoter(true, MOTOR_DC_DELAY_PIVOT_180);
}
