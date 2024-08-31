#include <AFMotor.h>

#define pinoSensorE 22
#define pinoSensorD 24
#define pinoSensorM 23
#define pinoSensorDist 16

#define pinoSensorI A8
#define INTERVALO 5000

#define D 0  //NÃO ALTERAR
#define E 1  //NÃO ALTERAR

#define PRETO 1   //NÃO ALTERAR
#define BRANCO 0  //NÃO ALTERAR

#define LADO_DESVIO D  //Configurar lado pelo qual o robô vai desviar de um obstáculo

AF_DCMotor motorD1(1);
AF_DCMotor motorD2(2);
AF_DCMotor motorE1(3);
AF_DCMotor motorE2(4);

int velocidadeFrente = 80;    //Velocidade para andar à frente
int velocidadeManobra = 190;  //Velocidade para ajustar percurso

int valSensorD, valSensorE, valSensorM, valSensorDist, valSensorI;

int portaLed = A10;

void setup() {
  // Serial.begin(9600);

  pinMode(pinoSensorE, INPUT);
  pinMode(pinoSensorD, INPUT);
  pinMode(pinoSensorM, INPUT);
  pinMode(pinoSensorDist, INPUT);
  pinMode(pinoSensorI, INPUT);
  pinMode(portaLed, OUTPUT);

  delay(500);
}

//OBS: Esta sequência de Serial.println deixa o código mais lento. Usar apenas para testes.
void loop() {
  valSensorD = digitalRead(pinoSensorD);
  valSensorE = digitalRead(pinoSensorE);
  valSensorM = digitalRead(pinoSensorM);
  valSensorDist = digitalRead(pinoSensorDist);
  valSensorI = digitalRead(pinoSensorI);

  if (valSensorI == 0) {
    irParaFrente(255, 255);
  } if (valSensorDist == 0) {
    digitalWrite(portaLed, 1);
    desviar(500);
  } else
    digitalWrite(portaLed, 0);

  if (valSensorM == 1) {
    irParaFrente(velocidadeFrente, velocidadeFrente);
  }

  else if (valSensorM == 1 && valSensorE == valSensorD) {
    irParaFrente(velocidadeFrente, velocidadeFrente);
  }
  // Sensor esquerdo detecta a linha preta
  else if (valSensorE == 1 && valSensorD == 0) {
    esquerda(velocidadeManobra, velocidadeManobra);
  }
  // Sensor direito detecta a linha preta
  else if (valSensorE == 0 && valSensorD == 1) {
    direita(velocidadeManobra, velocidadeManobra);
  }
}

void desviar(int tempoAjuste) {
  parar();
  delay(1000);
  if (LADO_DESVIO == E) {
    direita(velocidadeManobra, velocidadeManobra);
    delay(tempoAjuste);
    parar();
    delay(1000);
    irParaFrente(velocidadeManobra * 1.2, velocidadeManobra);
    irParaFrente(velocidadeManobra * 1.2, velocidadeManobra);
    irParaFrente(velocidadeManobra * 1.2, velocidadeManobra);
    do {
      irParaFrente(velocidadeManobra * 1.2, velocidadeFrente / 3);  //andar em curva para a esquerda
      valSensorM = digitalRead(pinoSensorM);
    } while (valSensorM == BRANCO);

  } else {  //Desviar pela esquerda
    esquerda(velocidadeManobra, velocidadeManobra);
    delay(tempoAjuste);
    parar();
    delay(1000);

    irParaFrente(velocidadeFrente / 3, velocidadeManobra * 1.2);  //andar em curva para a direita
    irParaFrente(velocidadeFrente / 3, velocidadeManobra * 1.2);  //andar em curva para a direita
    irParaFrente(velocidadeFrente / 3, velocidadeManobra * 1.2);  //andar em curva para a direita
    do {
      irParaFrente(velocidadeFrente / 3, velocidadeManobra * 1.2);  //andar em curva para a direita
      valSensorM = digitalRead(pinoSensorM);
    } while (valSensorM == BRANCO);
  }
}

void irParaFrente(int velocidadeMotorEsquerdo, int velocidadeMotorDireito) {
  motorE1.setSpeed(velocidadeMotorEsquerdo);
  motorE2.setSpeed(velocidadeMotorEsquerdo);
  motorD1.setSpeed(velocidadeMotorDireito);
  motorD2.setSpeed(velocidadeMotorDireito);

  motorD1.run(FORWARD);
  motorD2.run(FORWARD);
  motorE1.run(FORWARD);
  motorE2.run(FORWARD);
}

void marcha_re(int velocidadeMotorEsquerdo, int velocidadeMotorDireito) {
  motorE1.setSpeed(velocidadeMotorEsquerdo);
  motorE2.setSpeed(velocidadeMotorEsquerdo);
  motorD1.setSpeed(velocidadeMotorDireito);
  motorD2.setSpeed(velocidadeMotorDireito);

  motorD1.run(BACKWARD);
  motorD2.run(BACKWARD);
  motorE1.run(BACKWARD);
  motorE2.run(BACKWARD);
}

void esquerda(int velocidadeMotorEsquerdo, int velocidadeMotorDireito) {
  motorE1.setSpeed(velocidadeMotorEsquerdo);
  motorE2.setSpeed(velocidadeMotorEsquerdo);
  motorD1.setSpeed(velocidadeMotorDireito);
  motorD2.setSpeed(velocidadeMotorDireito);

  motorE1.run(FORWARD);
  motorE2.run(FORWARD);
  motorD1.run(BACKWARD);
  motorD2.run(BACKWARD);
}

void direita(int velocidadeMotorEsquerdo, int velocidadeMotorDireito) {
  motorE1.setSpeed(velocidadeMotorEsquerdo);
  motorE2.setSpeed(velocidadeMotorEsquerdo);
  motorD1.setSpeed(velocidadeMotorDireito);
  motorD2.setSpeed(velocidadeMotorDireito);

  motorD1.run(FORWARD);
  motorD2.run(FORWARD);
  motorE1.run(BACKWARD);
  motorE2.run(BACKWARD);
}

void parar() {
  motorE1.setSpeed(RELEASE);
  motorE2.setSpeed(RELEASE);
  motorD1.setSpeed(RELEASE);
  motorD2.setSpeed(RELEASE);
}                          