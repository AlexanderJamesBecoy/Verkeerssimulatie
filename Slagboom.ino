#include <Servo.h>

// Attributes
Servo slagboom;
const int SLAGBOOM_PIN = 11;
const int MIN_ANGLE = 0;
const int MAX_ANGLE = 90;
const long TIME_INTERVAL_SLAGBOOM = 15;

int slagboomVal = MAX_ANGLE;

// Operations
void servoSetup() {
  slagboom.attach(SLAGBOOM_PIN);
  slagboom.write(slagboomVal);
}

void servoUpwards() {
  while(slagboomVal < MAX_ANGLE) {
    slagboomVal = MAX_ANGLE;
    slagboom.write(MAX_ANGLE);
  }
}

void servoDownwards() {
  while(slagboomVal > MIN_ANGLE) {
    slagboomVal = MIN_ANGLE;
    slagboom.write(MIN_ANGLE);
  }
}

boolean servoIsMax() {
  return (slagboomVal >= MAX_ANGLE);
}

boolean servoIsMin() {
  return (slagboomVal <= MIN_ANGLE);
}

