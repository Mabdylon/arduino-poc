const char DIN_LIGHT_SENSOR_LEFT = 10;
const char DIN_LIGHT_SENSOR_MIDDLE = 11;
const char DIN_LIGHT_SENSOR_RIGHT = 2;


void initLightSensors() {
  pinMode(DIN_LIGHT_SENSOR_LEFT, INPUT);
  pinMode(DIN_LIGHT_SENSOR_MIDDLE, INPUT);
  pinMode(DIN_LIGHT_SENSOR_RIGHT, INPUT);
}

int getLightSensorValue(int type) {
  int value = digitalRead(type);
  Serial.print(type);
  Serial.print(" - ");
  Serial.println(value);
  return value;
  }

void testLightSensors() {
  getLightSensorValue(DIN_LIGHT_SENSOR_LEFT);
  getLightSensorValue(DIN_LIGHT_SENSOR_MIDDLE);
  getLightSensorValue(DIN_LIGHT_SENSOR_RIGHT);
}
