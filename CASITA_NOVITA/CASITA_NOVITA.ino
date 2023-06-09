#include "Ultrasonic.h"

const int echoPin = 9;
const int trigPin = 8;

Ultrasonic ultrasonic(trigPin, echoPin);

int distancia;
String result;

int ledSala = 7;
int ledQuar = 6;
int ledBanh = 5;

bool statusCasa = false;

void setup() {
  Serial.begin(9600);
  pinMode(ledSala, OUTPUT);
  pinMode(ledQuar, OUTPUT);
  pinMode(ledBanh, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop() {
  hcsr04();
  Serial.println(result);
  if (distancia <= 10) {
    digitalWrite(ledBanh, HIGH);
    digitalWrite(ledQuar, HIGH);
    digitalWrite(ledSala, HIGH);
  } else {
    digitalWrite(ledBanh, LOW);
    digitalWrite(ledQuar, LOW);
    digitalWrite(ledSala, LOW);
  }
}

void hcsr04() {
  digitalWrite(trigPin, LOW);   //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
  delayMicroseconds(2);         //INTERVALO DE 2 MICROSSEGUNDOS
  digitalWrite(trigPin, HIGH);  //SETA O PINO 6 COM PULSO ALTO "HIGH"
  delayMicroseconds(10);        //INTERVALO DE 10 MICROSSEGUNDOS
  digitalWrite(trigPin, LOW);   //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
  //FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
  //RESPOSTA DO ECHO EM CENTIMETROS, E ARMAZENA
  //NA VARIAVEL "distancia"
  distancia = (ultrasonic.Ranging(CM));  //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
  result = String(distancia);            //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
  delay(500);                            //INTERVALO DE 500 MILISSEGUNDOS
}