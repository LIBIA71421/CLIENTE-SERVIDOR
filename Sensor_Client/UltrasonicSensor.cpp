#include "UltrasonicSensor.h"
#include <Arduino.h>

UltrasonicSensor::UltrasonicSensor(int trigger, int echo)
  : triggerPin(trigger), echoPin(echo) {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

long UltrasonicSensor::readDistance() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  return pulseIn(echoPin, HIGH);
}
