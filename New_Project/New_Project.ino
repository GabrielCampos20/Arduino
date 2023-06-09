#include <AFMotor.h>

AF_DCMotor motorDF(2);
AF_DCMotor motorEF(3);
AF_DCMotor motorDT(1);
AF_DCMotor motorET(4);

int speed = 200;

#define LINHA HIGH
#define sensorD 23
#define sensorE 22

void setup() {
  Serial.begin(9600);

  motorDF.setSpeed(speed);
  motorEF.setSpeed(speed);
  motorDT.setSpeed(speed);
  motorET.setSpeed(speed);

  motorDF.run(RELEASE);
  motorEF.run(RELEASE);
  motorDT.run(RELEASE);
  motorET.run(RELEASE);

  pinMode(sensorD, INPUT);
  pinMode(sensorE, INPUT);
}

void loop() {
  if (digitalRead(sensorD) != LINHA && digitalRead(sensorE) != LINHA) {
    forward();
    Serial.println("FORWARD");
  } else if (digitalRead(sensorD) == LINHA && digitalRead(sensorE) != LINHA) {
    left();
    Serial.println("LEFT");
  } else if (digitalRead(sensorD) != LINHA && digitalRead(sensorE) == LINHA) {
    right();
    Serial.println("RIGHT");
  } else if (digitalRead(sensorD) == LINHA && digitalRead(sensorE) == LINHA) {
    stop();
    Serial.println("STOP");
  }
}

void forward() {
  motorDT.run(FORWARD);
  motorDF.run(FORWARD);
  motorEF.run(FORWARD);
  motorET.run(FORWARD);
}
void backward() {
  motorDT.run(BACKWARD);
  motorDF.run(BACKWARD);
  motorEF.run(BACKWARD);
  motorET.run(BACKWARD);
}
void right() {
  motorEF.run(FORWARD);
  motorDF.run(BACKWARD);
  motorDT.run(BACKWARD);
  motorET.run(FORWARD);
}
void left() {
  motorEF.run(BACKWARD);
  motorDF.run(FORWARD);
  motorDT.run(FORWARD);
  motorET.run(BACKWARD);
}
void stop() {
  motorDT.run(RELEASE);
  motorDF.run(RELEASE);
  motorEF.run(RELEASE);
  motorET.run(RELEASE);
}