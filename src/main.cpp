#include <Arduino.h>

#include <Wire.h>
#include <Servo.h>
#include "MotorDriver.h"
#include "UltrasonicSensor.h"
#include "ServoScanner.h"
#include "Screen.h"

MotorDriver motors;
UltrasonicSensor sensor(6, 7);        // trig, echo
ServoScanner scanner(9, A0, -30, 30); // servo pin, feedback pin, min/max angle

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  //motors.stop();
  //scanner.attach();

  // Test of the screen
  Screen screen;

  screen.begin();
  screen.clear();

  screen.drawSmiley(64, 32);
  screen.display();
  
  delay(2000);
  screen.clear();

}

void loop()
{
  /*
  Serial.println("[loop] Début boucle principale");
  motors.stop();

  scanner.scan(sensor);
  if (scanner.hasValidTarget())
  {
    // Screen animation: show scanning result
    static Screen screen;
    screen.begin();
    screen.clear();
    screen.drawText(0, 10, "Distance:");
    screen.drawText(0, 30, String(sensor.readDistance()).c_str());
    screen.drawText(0, 50, String(scanner.getBestAngle()).c_str());
    screen.drawSmiley(64, 32);
    screen.display();

    motors.turnToAngle(scanner.getBestAngle());
    motors.moveForwardUntilClose(sensor);
    motors.retreatAndTurnAround();
  }
  else
  {
    motors.rotateQuarterTurn();
  }

  Serial.println("[loop] Fin boucle principale");
  delay(500);
  */
}