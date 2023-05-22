#include <SoftwareSerial.h>
#include <AFMotor.h>

int ledsFarolDianteiro[] = { 40, 41, 42, 43 };
int ledsFarolTraseiro[] = { 36, 37, 38, 39 };

const int pinoTX = 53;
const int pinoRX = 52;
int dadoBluetooth = 0;

SoftwareSerial bluetooth(pinoTX, pinoRX);

AF_DCMotor motorDT(1);
AF_DCMotor motorDF(2);
AF_DCMotor motorEF(3);
AF_DCMotor motorET(4);

int speed = 255;

const int pinoLDR = A10;

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

  for (int i = 0; i < 4; i++) {
    pinMode(ledsFarolDianteiro[i], OUTPUT);
  }

  for (int i = 0; i < 4; i++) {
    pinMode(ledsFarolTraseiro[i], OUTPUT);
  }

  pinMode(pinoLDR, INPUT);
}

void loop() {
  if (bluetooth.available()) {
    dadoBluetooth = bluetooth.read();
    Serial.println(dadoBluetooth);

    if (dadoBluetooth == 70) {
      forward();
      Serial.println("Forward");
    } else if (dadoBluetooth == 66) {
      backward();
      Serial.println("Backward");
    } else if (dadoBluetooth == 82) {
      right();
      Serial.println("Right");
    } else if (dadoBluetooth == 76) {
      left();
      Serial.println("Left");
    } else if (dadoBluetooth == 83) {
      stop();
      Serial.println("Stop");
    } else if (dadoBluetooth == 87) {
      turnLedsFrontOn();
      Serial.println("Front leds on");
    } else if (dadoBluetooth == 119) {
      turnLedsFrontOff();
      Serial.println("Front leds off");
    } else if (dadoBluetooth == 85) {
      turnLedsBackOn();
      Serial.println("Back leds on");
    } else if (dadoBluetooth == 117) {
      turnLedsBackOff();
      Serial.println("Back leds off");
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

void turnLedsFrontOn() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledsFarolDianteiro[i], HIGH);
  }
}

void turnLedsFrontOff() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledsFarolDianteiro[i], LOW);
  }
}

void turnLedsBackOn() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledsFarolTraseiro[i], HIGH);
  }
}

void turnLedsBackOff() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledsFarolTraseiro[i], LOW);
  }
}