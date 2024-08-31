#include <AFMotor.h>

int sensorE = 22;
int sensorM = 23;
int sensorD = 24;

AF_DCMotor motorDT(1);
AF_DCMotor motorDF(2);
AF_DCMotor motorEF(3);
AF_DCMotor motorET(4);

int speed = 180;
int turnSpeed = 180;


void setup() {
  Serial.begin(9600);

  pinMode(sensorE, INPUT);
  pinMode(sensorD, INPUT);
  pinMode(sensorM, INPUT);
}

void loop() {
  Serial.print("Sensor E: ");
  Serial.println(digitalRead(sensorE));
  Serial.print("Sensor M: ");
  Serial.println(digitalRead(sensorM));
  Serial.print("Sensor D: ");
  Serial.println(digitalRead(sensorD));
  delay(1000);
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