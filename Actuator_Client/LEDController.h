#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

class LEDController {
  const int* LEDPINS; 
  int ledCount;  

public:
  LEDController(const int PINS[], int count);
  void turnOffAll();
  void setLEDsBasedOnDistance(int distance);
};

#endif 
