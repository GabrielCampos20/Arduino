#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <Servo.h>

const int pinoTX = 52;
const int pinoRX = 53;
int dadoBluetooth = 0;

SoftwareSerial bluetooth(pinoTX, pinoRX);
AF_DCMotor motorDT(1);
AF_DCMotor motorDF(2);
AF_DCMotor motorEF(3);
AF_DCMotor motorET(4);
int speed = 255;

Servo myservo1;
Servo myservo2;
bool state1 = false;
bool state2 = false;

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  bluetooth.print("$");
  bluetooth.print("$");
  bluetooth.print("$");
  delay(100);
  motorDT.setSpeed(speed);
  motorDF.setSpeed(speed);
  motorEF.setSpeed(speed);
  motorET.setSpeed(speed);
  motorDT.run(RELEASE);
  motorDF.run(RELEASE);
  motorEF.run(RELEASE);
  motorET.run(RELEASE);
}

void loop() {
  if (bluetooth.available()) {
    dadoBluetooth = bluetooth.read();
    Serial.println(dadoBluetooth);

    switch (dadoBluetooth) {
      case 70:
        forward();
        Serial.println("Forward");
        break;
      case 66:
        backward();
        Serial.println("Backward");
        break;
      case 82:
        left();
        Serial.println("Left");
        break;
      case 76:
        right();
        Serial.println("Right");
        break;
      case 83:
        stop();
        Serial.println("Stop");
        break;
      case 88:
        myservo1.attach(9);
        myservo2.attach(10);
        myservo1.write(180);  // Define a rotação contínua
        myservo2.write(180);  // Define a rotação contínua
        break;
      case 120:
        myservo1.detach();  // Desanexa para garantir que pare
        myservo2.detach();  // Desanexa para garantir que pare
        break;
      default:
        // Caso não previsto
        break;
    }
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
