#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define endereco 0x27
#define colunas 16
#define linhas 2

LiquidCrystal_I2C lcd(endereco, colunas, linhas);

#define NOTE_D4 294
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_A5 880

int tons[4] = { NOTE_A5, NOTE_A4, NOTE_G4, NOTE_D4 };
int sequencia[100] = {};
int rodada_atual = 0;
int passo_atual_na_sequencia = 0;


int pinoAudio = 13;
int pinosLeds[4] = { 8, 9, 10, 11 };
int pinosBotoes[4] = { 2, 3, 4, 5 };

int botao_pressionado = 0;
int perdeu_o_jogo = false;

void setup() {

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GENIUS GAME");
  lcd.setCursor(0, 1);
  lcd.print("START!!!");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RODADA: ");
  lcd.setCursor(7, 0);
  lcd.print(rodada_atual + 1);

  for (int i = 0; i <= 3; i++) {
    pinMode(pinosLeds[i], OUTPUT);
  }

  for (int i = 0; i <= 3; i++) {
    pinMode(pinosBotoes[i], INPUT_PULLUP);
  }

  pinMode(pinoAudio, OUTPUT);

  randomSeed(analogRead(0));
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("RODADA: ");
  lcd.setCursor(7, 0);
  lcd.print(rodada_atual + 1);

  if (perdeu_o_jogo) {
    int sequencia[100] = {};
    rodada_atual = 0;
    passo_atual_na_sequencia = 0;
    perdeu_o_jogo = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RODADA: ");
    lcd.setCursor(7, 0);
    lcd.print(rodada_atual + 1);
  }

  else if (rodada_atual == 0) {
    tocarSomDeInicio();
    delay(500);
  }

  proximaRodada();
  reproduzirSequencia();
  aguardarJogador();

  delay(1000);
}

void proximaRodada() {
  int numero_sorteado = random(0, 4);
  sequencia[rodada_atual++] = numero_sorteado;
}

void reproduzirSequencia() {
  for (int i = 0; i < rodada_atual; i++) {
    tone(pinoAudio, tons[sequencia[i]]);
    digitalWrite(pinosLeds[sequencia[i]], HIGH);
    delay(500);
    noTone(pinoAudio);
    digitalWrite(pinosLeds[sequencia[i]], LOW);
    delay(100);
  }
  noTone(pinoAudio);
}

void aguardarJogador() {
  for (int i = 0; i < rodada_atual; i++) {
    aguardarJogada();
    verificarJogada();

    if (perdeu_o_jogo) {
      break;
    }

    passo_atual_na_sequencia++;
  }

  passo_atual_na_sequencia = 0;
}

void aguardarJogada() {
  bool jogada_efetuada = false;
  while (!jogada_efetuada) {
    for (int i = 0; i <= 3; i++) {
      if (digitalRead(pinosBotoes[i]) == LOW) {
        botao_pressionado = i;

        tone(pinoAudio, tons[i]);
        digitalWrite(pinosLeds[i], HIGH);
        delay(300);
        digitalWrite(pinosLeds[i], LOW);
        noTone(pinoAudio);

        jogada_efetuada = true;
      }
    }
    delay(10);
  }
}

void verificarJogada() {
  if (sequencia[passo_atual_na_sequencia] != botao_pressionado) {
    for (int i = 0; i <= 3; i++) {
      tone(pinoAudio, tons[i]);
      digitalWrite(pinosLeds[i], HIGH);
      delay(200);
      digitalWrite(pinosLeds[i], LOW);
      noTone(pinoAudio);
    }

    tone(pinoAudio, tons[3]);
    for (int i = 0; i <= 3; i++) {
      digitalWrite(pinosLeds[0], HIGH);
      digitalWrite(pinosLeds[1], HIGH);
      digitalWrite(pinosLeds[2], HIGH);
      digitalWrite(pinosLeds[3], HIGH);
      delay(100);
      digitalWrite(pinosLeds[0], LOW);
      digitalWrite(pinosLeds[1], LOW);
      digitalWrite(pinosLeds[2], LOW);
      digitalWrite(pinosLeds[3], LOW);
      delay(100);
    }
    noTone(pinoAudio);

    perdeu_o_jogo = true;
  }
}

void tocarSomDeInicio() {
  tone(pinoAudio, tons[0]);
  digitalWrite(pinosLeds[0], HIGH);
  digitalWrite(pinosLeds[1], HIGH);
  digitalWrite(pinosLeds[2], HIGH);
  digitalWrite(pinosLeds[3], HIGH);
  delay(500);
  digitalWrite(pinosLeds[0], LOW);
  digitalWrite(pinosLeds[1], LOW);
  digitalWrite(pinosLeds[2], LOW);
  digitalWrite(pinosLeds[3], LOW);
  delay(500);
  noTone(pinoAudio);
}