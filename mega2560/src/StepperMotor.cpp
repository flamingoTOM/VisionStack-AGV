#include "StepperMotor.h"


StepperMotor::StepperMotor(int stepPin, int dirPin) {
  this->stepPin = stepPin;
  this->dirPin = dirPin;

}

void StepperMotor::setup() {
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void StepperMotor::setDirection(int direction) {
  digitalWrite(dirPin, direction);
}

void StepperMotor::rotateSteps(int steps) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(150); // Adjust the delay as per you motor's speed
    digitalWrite(stepPin, LOW);
    delayMicroseconds(150); // Adjust the delay as per your motor's speed
  }
}