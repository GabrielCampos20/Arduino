#include <AFMotor.h>

int sensorE = 22;
int sensorD = 23;
int sensorM = 24;
                    
AF_DCMotor motorDT(1);
AF_DCMotor motorDF(2);
AF_DCMotor motorEF(3);
AF_DCMotor motorET(4);

int speed = 255;
int turnSpeed = 255;

void setup() {

  pinMode(sensorE, INPUT);
  pinMode(sensorD, INPUT);
  pinMode(sensorM, INPUT);

}

void loop() {
  // /1 == preto || 0 == branco/
  int valSensorE = digitalRead(sensorE);
  int valSensorD = digitalRead(sensorD);
  int valSensorM = digitalRead(sensorM);

  if (valSensorE == 0 && valSensorD == 0 && valSensorM == 1) {
    forward();
  }
  if (valSensorE == 1 && valSensorD == 0) {
    while (valSensorM == 0) {
      valSensorM = digitalRead(sensorM);
      left();
    }
  }
  if (valSensorE == 0 && valSensorD == 1) {
    while (valSensorM == 0) {
      valSensorM = digitalRead(sensorM);
      right();
    }
  }
}


void forward() {
  motorDT.setSpeed(speed);
  motorDF.setSpeed(speed);
  motorEF.setSpeed(speed);
  motorET.setSpeed(speed);

  motorDT.run(FORWARD);
  motorDF.run(FORWARD);
  motorEF.run(FORWARD);
  motorET.run(FORWARD);
}
void backward() {
  motorDT.setSpeed(speed);
  motorDF.setSpeed(speed);
  motorEF.setSpeed(speed);
  motorET.setSpeed(speed);

  motorDT.run(BACKWARD);
  motorDF.run(BACKWARD);
  motorEF.run(BACKWARD);
  motorET.run(BACKWARD);
}
void left() {
  motorDT.setSpeed(turnSpeed);
  motorDF.setSpeed(turnSpeed);
  motorEF.setSpeed(turnSpeed);
  motorET.setSpeed(turnSpeed);

  motorEF.run(FORWARD);
  motorDF.run(BACKWARD);  
  motorDT.run(BACKWARD);
  motorET.run(FORWARD);
}
void right() {
  motorDT.setSpeed(turnSpeed);
  motorDF.setSpeed(turnSpeed);
  motorEF.setSpeed(turnSpeed);
  motorET.setSpeed(turnSpeed);

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