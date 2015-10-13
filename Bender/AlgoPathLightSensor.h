void algoPathLightSensor () {
  int lightLeft = getLightSensorValue(DIN_LIGHT_SENSOR_LEFT);
  int lightMiddle = getLightSensorValue(DIN_LIGHT_SENSOR_MIDDLE);
  int lightRight = getLightSensorValue(DIN_LIGHT_SENSOR_RIGHT);
  if (lightRight == 1) {
    pivoteADroite();
  } else if (lightLeft == 1 ) {
    pivoteAGauche();
  } else if(lightMiddle == 1 && lightLeft == 0 && lightRight == 0){
    avanceEnLigneDroite();
  } else {
    arret();
    }
}
