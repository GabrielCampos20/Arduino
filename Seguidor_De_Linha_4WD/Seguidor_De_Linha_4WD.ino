//Inclusão da biblioteca que controla os motores
#include <AFMotor.h>


//Definição dos pinos que vão controlar os motores
AF_DCMotor motorDT(1);
AF_DCMotor motorDF(2);
AF_DCMotor motorEF(3);
AF_DCMotor motorET(4);

//Variável que controla a velocidade dos motores, pode variar de 0 a 255
int speed = 255;


//Definição dos pinos em que vão estar os senosres
int sensorE = 50;
int sensorD = 51;

void setup() {
  Serial.begin(9600);

  motorDT.setSpeed(speed);
  motorDF.setSpeed(speed);
  motorEF.setSpeed(speed);
  motorET.setSpeed(speed);

  motorDT.run(RELEASE);
  motorDF.run(RELEASE);
  motorEF.run(RELEASE);
  motorET.run(RELEASE);

  pinMode(sensorE, INPUT);
  pinMode(sensorD, INPUT);
}

void loop() {
  if (digitalRead(sensorE) == 1 && digitalRead(sensorD) == 1) {
    forward();
    /*
    Se nenhum dos sensores identificar nada, o carrinho vai pra frente
    */
  } else if (digitalRead(sensorE) == 0 && digitalRead(sensorD) == 1) {
    right();
    /*
    Se o sensor da esquerda identificar algo, e o sensor da direita não
    identificar nada, o carrinho vira pra direita
    */
  } else if (digitalRead(sensorE) == 1 && digitalRead(sensorD) == 0) {
    left();
    /*
    Se o sensor da direita identificar algo, e o sensor da esquerda não
    identificar nada, o carrinho vira pra esquerda
    */
  } else if (digitalRead(sensorE) == 0 && digitalRead(sensorD) == 0) {
    stop();
    /*
    Se ambos os sensores identificarem algo, o carrinho para
    */
  }
}
/*
Métodos utilizados para funcionamento do carrinho

Em ordem-->
Frente;
Trás;
Esquerda;
Direita;
Parar;
*/
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