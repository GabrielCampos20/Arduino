#include <Keypad.h>

const byte qtdLinhas = 4;
const byte qtdColunas = 4;

//CONSTRUÇÃO DA MATRIZ DE CARACTERES
char matriz_teclas[qtdLinhas][qtdColunas] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};


byte PinosqtdLinhas[qtdLinhas] = { 3, 4, 5, 6 };
byte PinosqtdColunas[qtdColunas] = { 8, 9, 10, 11 };

int ledSala = 12;
int statusSala = 0;
int ledQuar = 13;
int statusQuar = 0;
int ledBanh = 7;
int statusBanh = 0;

Keypad meuteclado = Keypad(makeKeymap(matriz_teclas), PinosqtdLinhas, PinosqtdColunas, qtdLinhas, qtdColunas);

void setup() {
  Serial.begin(9600);
  Serial.println("Aperte uma tecla...");
  Serial.println();
  pinMode(ledSala, OUTPUT);
  pinMode(ledQuar, OUTPUT);
  pinMode(ledBanh, OUTPUT);
}

void loop() {
  char tecla_pressionada = meuteclado.getKey();

  if (tecla_pressionada == 1 && statusSala == 0) {
    Serial.println(tecla_pressionada);
    statusSala = 1;
    digitalWrite(ledSala, HIGH);
    Serial.println("Led Sala Ligado");
  } else if (tecla_pressionada == 1 && statusSala == 1) {
    Serial.println(tecla_pressionada);
    statusSala = 0;
    digitalWrite(ledSala, LOW);
    Serial.println("Led Sala Desligado");
  } else if (tecla_pressionada == 2 && statusQuar == 0) {
    Serial.println(tecla_pressionada);
    statusQuar = 1;
    digitalWrite(ledQuar, HIGH);
    Serial.println("Led Quarto Ligado");
  } else if (tecla_pressionada == 2 && statusQuar == 1) {
    Serial.println(tecla_pressionada);
    statusQuar = 0;
    digitalWrite(ledQuar, LOW);
    Serial.println("Led Quarto Desligado");
  } else if (tecla_pressionada == 3 && statusBanh == 0) {
    Serial.println(tecla_pressionada);
    statusBanh = 1;
    digitalWrite(ledBanh, HIGH);
    Serial.println("Led Banheiro Ligado");
  } else if (tecla_pressionada == 3 && statusBanh == 1) {
    Serial.println(tecla_pressionada);
    statusBanh = 0;
    digitalWrite(ledBanh, LOW);
    Serial.println("Led Banheiro Ligado");
  }
}