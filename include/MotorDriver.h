#pragma once
#include <Arduino.h>

/**
 * @brief Driver class for the motors.
 *
 */
class MotorDriver
{
public:
    MotorDriver();
    void stop();
    void moveForward();
    void moveBackward();
    void turnRight();
    void rotateHalfTurn();
    void rotateQuarterTurn();
    void moveForwardUntilClose(class UltrasonicSensor &sensor);
    void retreatAndTurnAround();
    void turnToAngle(int angle);

private:
    static const uint8_t I2C_ADDR = 0x34;
    static const uint8_t MOTOR_FIXED_SPEED_ADDR = 51;

    int8_t motorsStop[4] = {0, 0, 0, 0};
    int8_t motorsForward[4] = {-23, -23, 0, 0};
    int8_t motorsBackward[4] = {23, 23, 0, 0};
    int8_t motorsTurn[4] = {20, 20, 0, 0};

    void moveMotors(int8_t speeds[4]);
};
