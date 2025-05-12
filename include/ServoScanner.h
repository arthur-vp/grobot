#pragma once
#include <Servo.h>
#include "UltrasonicSensor.h"

class ServoScanner
{
public:
    ServoScanner(int servoPin, int feedbackPin, int minAngle, int maxAngle);
    void attach();
    void scan(UltrasonicSensor &sensor);
    bool hasValidTarget() const;
    int getBestAngle() const;

private:
    Servo servo;
    int servoPin, feedbackPin;
    int minAngle, maxAngle;
    int bestAngle;
    long bestDistance;
    static const int scanAttempts = 5;
};