boolean chercheUneIssueAGauche() {
  regardeAGauche();
  delay(DELAY_TO_LOOK);
  return laVoieEstLibre();
}

boolean chercheUneIssueADroite() {
  regardeADroite();
  delay(DELAY_TO_LOOK);
  return laVoieEstLibre();
}

void chercheUneIssue() {
  arret();
  if (chercheUneIssueAGauche()) {
    pivoteAGaucheFourtyFive();
  } else if (chercheUneIssueADroite()) {
    pivoteADroiteFourtyFive();
  } else {
    demiTour();
  }
  avanceEnLigneDroite();
}

void algoAntiCollision() {
  regardeToutDroit();
  if (laVoieEstLibre()) {
    regardeAGauche();
    if (laVoieEstLibre()) {
      regardeToutDroit();
      if (laVoieEstLibre()) {
        regardeADroite();
        if (laVoieEstLibre()) {
          if (!enMouvement) {
            avanceEnLigneDroite();
          }
        } else {
          chercheUneIssue();
        }
      } else {
        chercheUneIssue();
      }
    } else {
      chercheUneIssue();
    }
  } else {
    chercheUneIssue();
  }
  delay(1);  
}

