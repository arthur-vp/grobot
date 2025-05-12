#include "ServoScanner.h"

ServoScanner::ServoScanner(int pin, int feedback, int minA, int maxA)
    : servoPin(pin), feedbackPin(feedback), minAngle(minA), maxAngle(maxA) {}

void ServoScanner::attach()
{
    servo.attach(servoPin);
}

void ServoScanner::scan(UltrasonicSensor &sensor)
{
    Serial.println("[Scanner] scan start");
    bestDistance = 999;
    bestAngle = 0;

    for (int attempt = 0; attempt < scanAttempts; attempt++)
    {
        for (int angle = minAngle; angle <= maxAngle; angle += 2)
        {
            servo.write(angle + 90);
            delay(200);
            long dist = sensor.readDistance();
            if (dist > 10 && dist < 80 && dist < bestDistance)
            {
                bestDistance = dist;
                bestAngle = angle;
            }
        }
        for (int angle = maxAngle; angle >= minAngle; angle -= 2)
        {
            servo.write(angle + 90);
            delay(200);
            long dist = sensor.readDistance();
            if (dist > 10 && dist < 80 && dist < bestDistance)
            {
                bestDistance = dist;
                bestAngle = angle;
            }
        }
    }

    Serial.print("[Scanner] Best angle: ");
    Serial.print(bestAngle);
    Serial.print(" at ");
    Serial.print(bestDistance);
    Serial.println(" cm");
}

bool ServoScanner::hasValidTarget() const
{
    return bestDistance < 999;
}

int ServoScanner::getBestAngle() const
{
    return bestAngle;
}