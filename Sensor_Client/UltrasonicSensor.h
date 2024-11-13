#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

class UltrasonicSensor {
  int triggerPin;
  int echoPin;

public:
  UltrasonicSensor(int trigger, int echo);
  long readDistance();
};

#endif