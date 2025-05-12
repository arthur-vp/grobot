#include "MotorDriver.h"
#include "UltrasonicSensor.h"

#include <Wire.h>



MotorDriver::MotorDriver() {}

void MotorDriver::moveMotors(int8_t speeds[4]) 
{
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(MOTOR_FIXED_SPEED_ADDR);
    for (int i = 0; i < 4; i++)
    {
        Wire.write(speeds[i]);
    }
    Wire.endTransmission();
}

void MotorDriver::stop() 
{
    Serial.println("[Motor] stop");
    moveMotors(motorsStop);
}

void MotorDriver::moveForward() 
{
moveMotors(motorsForward);
}

void MotorDriver::moveBackward() 
{
    moveMotors(motorsBackward);
}

void MotorDriver::turnRight() 
{
    moveMotors(motorsTurn);
}

void MotorDriver::rotateQuarterTurn()
{
    Serial.println("[Motor] rotateQuarterTurn");
    turnRight();
    delay(600);
    stop();
}

void MotorDriver::rotateHalfTurn() 
{
    Serial.println("[Motor] rotateHalfTurn");
    turnRight();
    delay(1200);
    stop();
}

void MotorDriver::moveForwardUntilClose(UltrasonicSensor& sensor) 
{
    Serial.println("[Motor] moveForwardUntilClose");
    moveForward();
    unsigned long start = millis();
    while (sensor.readDistance() > 10 && millis() - start < 5000) 
    {
        delay(100);
    }
    delay(500);
    stop();
}

void MotorDriver::retreatAndTurnAround()
{
    Serial.println("[Motor] retreatAndTurnAround");
    moveBackward();
    delay(5000);
    stop();
    rotateHalfTurn();
}

void MotorDriver::turnToAngle(int angle) 
{
    if (angle > 5 || angle < -5) 
    {
        turnRight();
        delay(abs(angle) * 10);
        stop();
    }
}