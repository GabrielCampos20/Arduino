#include <IRremote.h>

int ledsFarol[] = { 48, 49, 50, 51, 52, 53 };

int RECV_PIN = 11;

int IN1 = 5;
int IN2 = 6;
int velocidadeD = 7;

int IN3 = 9;
int IN4 = 10;
int velocidadeE = 8;

int velocidade = 255;
int parar = 0;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(velocidadeD, OUTPUT);
  pinMode(velocidadeE, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  for (int i = 0; i < 6; i++) {
    pinMode(ledsFarol[i], OUTPUT);
  }
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if (results.value == 0xFF18E7) {
      Serial.println("Forward");
      forward();
    }
    if (results.value == 0xFF4AB5) {
      Serial.println("Backward");
      backward();
    }
    if (results.value == 0xFF5AA5) {
      Serial.println("Right");
      right();
    }
    if (results.value == 0xFF10EF) {
      Serial.println("Left");
      left();
    }
    if (results.value == 0xFF38C7) {
      Serial.println("Stop");
      stop();
    }
    if (results.value == 0xFFA857) {
      ligarFarois();
      Serial.println("On");
    }
    if (results.value == 0xFFE01F) {
      desligarFarois();
      Serial.println("Off");
    }
    irrecv.resume();
  }
}

void forward() {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  analogWrite(velocidadeD, velocidade);

  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(velocidadeE, velocidade);
}

void backward() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  analogWrite(velocidadeD, velocidade);

  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  analogWrite(velocidadeE, velocidade);
}

void left() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  analogWrite(velocidadeD, velocidade);

  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(velocidadeE, velocidade);
}

void right() {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  analogWrite(velocidadeD, velocidade);

  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  analogWrite(velocidadeE, velocidade);
}

void stop() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  analogWrite(velocidadeD, parar);

  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  analogWrite(velocidadeE, parar);
}

void ligarFarois() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledsFarol[i], HIGH);
  }
}

void desligarFarois() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledsFarol[i], LOW);
  }
}