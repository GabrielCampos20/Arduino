//Declaração dos pinos conectados na Ponte H
int IN1 = 4;
int IN2 = 5;
int IN3 = 7;
int IN4 = 8;

/*
Declaração dos pinos que controlam quanta energia/velocidade será
enviada para os motores
*/
int velocidadeD = 6;
int velocidadeE = 9;

//Declaração dos pinos conectados nos sensores IR
int sensorE = 2;
int sensorD = 3;

/*
Variáveis de controle de velocidade
A velocidade pode ir de 0 a 255
*/
int velocidade = 120;
int parar = 0;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(velocidadeD, OUTPUT);
  pinMode(velocidadeE, OUTPUT);

  pinMode(sensorE, INPUT);
  pinMode(sensorD, INPUT);
}

void loop() {
  if (digitalRead(sensorE) == 0 && digitalRead(sensorD) == 0) {
    forward();
    /*
    Se nenhum dos sensores identificar nada, o carrinho vai pra frente
    */
  } else if (digitalRead(sensorE) == 1 && digitalRead(sensorD) == 0) {
    right();
    /*
    Se o sensor da esquerda identificar algo, e o sensor da direita não
    identificar nada, o carrinho vira pra direita
    */
  } else if (digitalRead(sensorE) == 0 && digitalRead(sensorD) == 1) {
    left();
    /*
    Se o sensor da direita identificar algo, e o sensor da esquerda não
    identificar nada, o carrinho vira pra esquerda
    */
  } else if (digitalRead(sensorE) == 1 && digitalRead(sensorD) == 1) {
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
void backward() {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  analogWrite(velocidadeD, velocidade);

  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(velocidadeE, velocidade);
}

void forward() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  analogWrite(velocidadeD, velocidade);

  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  analogWrite(velocidadeE, velocidade);
}

void right() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  analogWrite(velocidadeD, velocidade);

  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(velocidadeE, velocidade);
}

void left() {
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