#include <SoftwareSerial.h>

const int pinoRX = 11;
const int pinoTX = 12;
int dadoBluetooth = 0;

SoftwareSerial bluetooth(pinoRX, pinoTX);

int IN1 = 5;
int IN2 = 6;
int velocidadeD = 7;

int IN3 = 9;
int IN4 = 10;
int velocidadeE = 8;

int velMax = 255;
int velStp = 0;

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  bluetooth.print("$");
  bluetooth.print("$");
  bluetooth.print("$");
  delay(100);
  pinMode(velocidadeD, OUTPUT);
  pinMode(velocidadeE, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
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
    }else if(dadoBluetooth == 73){
      forwRigh();
      Serial.println("Forward and Right");
    }
     else {
      Serial.println("Comando ainda não cadastrado");
    }
  }else{
    stop();
  }
}

void forward() {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  analogWrite(velocidadeD, velMax);

  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(velocidadeE, velMax);
}

void backward() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  analogWrite(velocidadeD, velMax);

  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  analogWrite(velocidadeE, velMax);
}

void right() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  analogWrite(velocidadeD, velMax);

  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(velocidadeE, velMax);
}

void left() {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  analogWrite(velocidadeD, velMax);

  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  analogWrite(velocidadeE, velMax);
}

void stop() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  analogWrite(velocidadeD, velStp);

  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  analogWrite(velocidadeE, velStp);
}

void forwRigh() {
  forward();
  right();
}