#ifndef HC_SR04_h
#define HC_SR04_h

#include <Arduino.h>

class HC_SR04 {
  public:
    HC_SR04(int triggerPin, int echoPin);
    void begin();
    float getDistance();
    float average_distance();

  private:
    int _triggerPin;
    int _echoPin;
};

#endif