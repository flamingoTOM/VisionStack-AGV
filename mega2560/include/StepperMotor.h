#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <Arduino.h>

class StepperMotor {
  private:
    int stepPin;
    int dirPin;

  public:
    StepperMotor(int stepPin, int dirPin);
    void setup();
    void setDirection(int direction);
    void rotateSteps(int steps);
};

#endif
