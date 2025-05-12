#pragma once
#include <Arduino.h>

class UltrasonicSensor {
public:
UltrasonicSensor(int trigPin, int echoPin);
long readDistance();

private:
int trigPin, echoPin;
};