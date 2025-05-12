#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int trig, int echo)
    : trigPin(trig), echoPin(echo)
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

long UltrasonicSensor::readDistance()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000);
    long distance = duration * 0.034 / 2;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    return distance;
}