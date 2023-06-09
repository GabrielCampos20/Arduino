#include <Wire.h>
#include "Adafruit_TCS34725.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725();
/* initialize with specific int time and gain values */
//Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

int pinoR = 11;  //PINO DIGITAL EM QUE O TERMINAL 'R' ESTÁ CONECTADO
int pinoG = 10;  //PINO DIGITAL EM QUE O TERMINAL 'G' ESTÁ CONECTADO
int pinoB = 9;   //PINO DIGITAL EM QUE O TERMINAL 'B' ESTÁ CONECTADO

void setup(void) {
  Serial.begin(9600);
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1)
      ;
  }
  pinMode(pinoR, OUTPUT);  //DEFINE O PINO COMO SAÍDA
  pinMode(pinoG, OUTPUT);  //DEFINE O PINO COMO SAÍDA
  pinMode(pinoB, OUTPUT);  //DEFINE O PINO COMO SAÍDA
}

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;
  tcs.getRawData(&r, &g, &b, &c);
  Serial.print("R: ");
  Serial.print(r, DEC);
  Serial.print(" ");
  Serial.print("G: ");
  Serial.print(g, DEC);
  Serial.print(" ");
  Serial.print("B: ");
  Serial.print(b, DEC);
  Serial.print(" ");
  Serial.print("C: ");
  Serial.print(c, DEC);
  Serial.print(" ");
  Serial.println(" ");
  delay(100);
}

void setColor(int vermelho, int verde, int azul) {

#ifdef COMMON_ANODE           //SE O LED RGB FOR DEFINIDO COMO ANODO COMUM, FAZ
  vermelho = 255 - vermelho;  //VARIÁVEL RECEBE O RESULTADO DA OPERAÇÃO '255 MENOS O PARÂMETRO (vermelho) INFORMADO' NA CHAMADA DA FUNÇÃO
  verde = 255 - verde;        //VARIÁVEL RECEBE O RESULTADO DA OPERAÇÃO '255 MENOS O PARÂMETRO (verde) INFORMADO' NA CHAMADA DA FUNÇÃO
  azul = 255 - azul;          //VARIÁVEL RECEBE O RESULTADO DA OPERAÇÃO '255 MENOS O PARÂMETRO (azul) INFORMADO' NA CHAMADA DA FUNÇÃO
#endif
  analogWrite(pinoR, vermelho);  //DEFINE O BRILHO DO LED DE ACORDO COM O VALOR INFORMADO PELA VARIÁVEL 'vermelho'
  analogWrite(pinoG, verde);     //DEFINE O BRILHO DO LED DE ACORDO COM O VALOR INFORMADO PELA VARIÁVEL 'verde'
  analogWrite(pinoB, azul);      //DEFINE O BRILHO DO LED DE ACORDO COM O VALOR INFORMADO PELA VARIÁVEL 'azul'
}