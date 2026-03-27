#include "HC_SR04.h"

HC_SR04::HC_SR04(int triggerPin, int echoPin) {
  _triggerPin = triggerPin;
  _echoPin = echoPin;
}

void HC_SR04::begin() {
  pinMode(_triggerPin, OUTPUT);
  pinMode(_echoPin, INPUT);
}

float HC_SR04::getDistance() {
  digitalWrite(_triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_triggerPin, LOW);

  float duration = pulseIn(_echoPin, HIGH);
  float distance = duration * 0.034 / 2;

  return distance;
}

float HC_SR04::average_distance() {
    const int numReadings = 5;  // 使用20次测量值进行平均
    float sum = 0;

    for (int i = 0; i < numReadings; i++) {
        sum += getDistance();
        //delay(5);  // 适当的延迟，避免测量过快
    }
    Serial.println(sum / numReadings);
    return sum / numReadings;
}