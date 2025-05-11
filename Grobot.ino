#include <Wire.h>
#include <Servo.h>

// I2C Motor driver address
#define I2C_ADDR 0x34
#define MOTOR_FIXED_SPEED_ADDR 51

#define MOTOR_TYPE_ADDR 20
#define MOTOR_ENCODER_POLARITY_ADDR 21

// Pins capteur US
const int trigPin = 6;
const int echoPin = 7;

// Servo
Servo myServo;
const int servoSignalPin = 9;
const int servoFeedbackPin = A0;

// Constantes
const int servoMinAngle = -30;  // angle minimum réduit
const int servoMaxAngle = 30;   // angle maximum réduit
const int detectionMin = 10;
const int detectionMax = 80;
const int scanAttempts = 5;
const int forwardSpeed = -23;
const int backwardSpeed = 23;

int8_t motorsStop[4] = {0, 0, 0, 0};
int8_t motorsForward[4] = {forwardSpeed, forwardSpeed, 0, 0};
int8_t motorsBackward[4] = {backwardSpeed, backwardSpeed, 0, 0};
int8_t motorsTurnRight[4] = {20, 20, 0, 0};
int8_t motorsTurnAround[4] = {20, 20, 0, 0};

// Variables globales
int bestAngle = 0;
long bestDistance = 999;

bool WireWriteDataArray(uint8_t reg, int8_t *val, unsigned int len) {
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(reg);
  for (unsigned int i = 0; i < len; i++) Wire.write(val[i]);
  return Wire.endTransmission() == 0;
}

void moveMotors(int8_t speeds[4]) {
  WireWriteDataArray(MOTOR_FIXED_SPEED_ADDR, speeds, 4);
}

long readUltrasonicDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000);
  long distance = duration * 0.034 / 2;
  Serial.print("Distance mesurée: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

int readServoAngle() {
  int raw = analogRead(servoFeedbackPin);
  return map(raw, 0, 1023, -90, 90); // estimation approximative
}

void stopMotors() {
  Serial.println("[stopMotors] Arrêt des moteurs");
  moveMotors(motorsStop);
  Serial.println("[stopMotors] Fin");
}

void scanSurroundings() {
  Serial.println("[scanSurroundings] Début du scan");
  bestDistance = 999;
  bestAngle = 0;

  for (int attempt = 0; attempt < scanAttempts; attempt++) {
    // Aller
    for (int angle = servoMinAngle; angle <= servoMaxAngle; angle += 2) {
      myServo.write(angle + 90);
      delay(200);
      long dist = readUltrasonicDistance();
      if (dist >= detectionMin && dist <= detectionMax && dist < bestDistance) {
        bestDistance = dist;
        bestAngle = angle;
      }
    }

    delay(200); // Pause entre aller et retour

    // Retour
    for (int angle = servoMaxAngle; angle >= servoMinAngle; angle -= 2) {
      myServo.write(angle + 90);
      delay(200);
      long dist = readUltrasonicDistance();
      if (dist >= detectionMin && dist <= detectionMax && dist < bestDistance) {
        bestDistance = dist;
        bestAngle = angle;
      }
    }
  }

  Serial.print("[scanSurroundings] Meilleure distance: ");
  Serial.print(bestDistance);
  Serial.print(" cm à l'angle ");
  Serial.println(bestAngle);
  Serial.println("[scanSurroundings] Fin du scan");
}


void rotateQuarterTurn() {
  Serial.println("[rotateQuarterTurn] Rotation quart de tour");
  moveMotors(motorsTurnRight);
  delay(600);
  stopMotors();
  delay(500);
  Serial.println("[rotateQuarterTurn] Fin");
}

void rotateHalfTurn() {
  Serial.println("[rotateHalfTurn] Rotation demi-tour");
  moveMotors(motorsTurnAround);
  delay(1200);
  stopMotors();
  delay(500);
  Serial.println("[rotateHalfTurn] Fin");
}

void moveForwardUntilClose() {
  Serial.println("[moveForwardUntilClose] Avance vers l'objet");
  moveMotors(motorsForward);
  unsigned long start = millis();
  while (readUltrasonicDistance() > 10 && millis() - start < 5000) {
    delay(100);
  }
  delay(5000);
  stopMotors();
  Serial.println("[moveForwardUntilClose] Fin");
}

void retreatAndTurnAround() {
  Serial.println("[retreatAndTurnAround] Recul et demi-tour");
  moveMotors(motorsBackward);
  delay(5000);
  stopMotors();
  rotateHalfTurn();
  Serial.println("[retreatAndTurnAround] Fin");
}

void goToTarget() {
  Serial.println("[goToTarget] Ciblage et poursuite");
  int correction = bestAngle;
  if (correction > 5 || correction < -5) {
    moveMotors(motorsTurnRight);
    delay(abs(correction) * 10);
    stopMotors();
  }
  moveForwardUntilClose();
  retreatAndTurnAround();
  Serial.println("[goToTarget] Fin");
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  myServo.attach(servoSignalPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  stopMotors();
}

void loop() {
  Serial.println("[loop] Début boucle principale");
  stopMotors();
  scanSurroundings();
  if (bestDistance < 999) {
    goToTarget();
  } else {
    rotateQuarterTurn();
  }
  Serial.println("[loop] Fin boucle principale");
}
