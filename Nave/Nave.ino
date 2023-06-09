//#include<nome da biblioteca.h>
//LiquidCrystal "nome desejado"(RS, E, DB4, DB5, DB6, DB7);
#include <LiquidCrystal.h>

#define botao_cima 8
#define botao_baixo 9
#define botao_tiro 10

//"nome desejado"    (RS, E, DB4, DB5, DB6, DB7);
LiquidCrystal display(12, 11, 5, 4, 3, 2);

//Variaveis do programa
int velocidade = 120;                          //100;
int posicao_X_nave, posicao_Y_nave;            //posições X e Y da nave
int posicao_X_asteroide, posicao_Y_asteroide;  //posições X e Y do asteroide
int posicao_X_energia, posicao_Y_energia;      //posições X e Y da energia
int posicao_X_tiro, posicao_Y_tiro;            //posições X e Y do tiro
bool game, desenha_tiro, desenha_pilha;
int pontos;
double gasolina;
int vtela;
int pontos_maximos = 10;

//Caracteres especiais
byte Nave[8] = { B11111, B00100, B00110, B01111, B01111, B00110, B00100, B11111 };
byte Asteroide[8] = { B00000, B00100, B01110, B10111, B11101, B01110, B00100, B00000 };
byte Explosao[8] = { B10001, B10101, B01010, B10100, B00101, B01010, B10101, B10001 };
byte Energia[8] = { B01110, B11011, B10001, B10101, B10101, B10101, B10001, B11111 };
byte Tiro[8] = { B00000, B00000, B00000, B00111, B00111, B00000, B00000, B00000 };

void setup() {
  //Inicialiaando as variaveis
  posicao_X_nave = posicao_Y_nave = 0;
  posicao_Y_asteroide = 0;  //posições X e Y do asteroide
  posicao_X_energia = posicao_Y_energia = 0;
  posicao_Y_tiro = 0;
  posicao_X_tiro = -1;
  posicao_X_asteroide = 12;
  gasolina = 100;
  vtela = 0;

  //Criando os caracteres
  display.createChar(1, Nave);
  display.createChar(2, Asteroide);
  display.createChar(3, Explosao);
  display.createChar(4, Energia);
  display.createChar(5, Tiro);
  display.begin(16, 2);
  display.clear();
  game = false;  //game = true;
  desenha_tiro = desenha_pilha = false;

  //Define essas portas como entrada
  pinMode(botao_cima, INPUT);
  pinMode(botao_baixo, INPUT);
  pinMode(botao_tiro, INPUT);
}

void loop() {
  //Se a variavel for verdadeira executa o jogo
  if (game) {
    gasolina -= 0.25;
    display.clear();
    if (gasolina <= 0) {
      game = false;
      //desenha_Explosao_Nave(posicao_X_nave, posicao_Y_nave);
      vtela = 2;
    }
    painel(13);
    if (digitalRead(botao_cima) == HIGH) {
      posicao_Y_nave = 0;
    }
    if (digitalRead(botao_baixo) == HIGH) {
      posicao_Y_nave = 1;
    }
    if (digitalRead(botao_tiro) == HIGH) {
      posicao_X_tiro = 1;
      desenha_tiro = true;
      posicao_Y_tiro = posicao_Y_nave;
    }
    posicao_X_asteroide -= 1;
    desenha_Nave(posicao_X_nave, posicao_Y_nave);
    desenha_Asteroide(posicao_X_asteroide, posicao_Y_asteroide);
    if (desenha_tiro) {
      desenha_Tiro(posicao_X_tiro, posicao_Y_tiro);
      posicao_X_tiro += 1;
    }
    if (posicao_X_asteroide < 0) {
      posicao_X_asteroide = 12;
      posicao_Y_asteroide = random(0, 2);
    }
    if (posicao_X_tiro > 16) {
      desenha_tiro = false;
      posicao_X_tiro = -1;
    }
    if (((posicao_X_tiro == posicao_X_asteroide + 1) && (posicao_Y_tiro == posicao_Y_asteroide)) || ((posicao_X_tiro == posicao_X_asteroide) && (posicao_Y_tiro == posicao_Y_asteroide))) {
      desenha_tiro = false;
      posicao_X_tiro = -1;
      desenha_Explosao_Asteroide(posicao_X_asteroide, posicao_Y_asteroide);
      posicao_Y_asteroide = random(0, 2);
      posicao_X_asteroide = 12;
      pontos += 2;
      //if(pontos>=100)
      if (pontos >= pontos_maximos) {
        game = false;
        vtela = 1;
      }
    }
    if ((posicao_X_nave == posicao_X_asteroide) && (posicao_Y_nave == posicao_Y_asteroide)) {
      game = false;
      desenha_Explosao_Nave(posicao_X_nave, posicao_Y_nave);
      vtela = 2;
    }
    if (desenha_pilha == false) {
      if (random(0, 60) > 30) {
        posicao_X_energia = 12;
        desenha_pilha = true;
        posicao_Y_energia = random(0, 2);
      }
    } else {
      posicao_X_energia -= 1;
      desenha_Energia(posicao_X_energia, posicao_Y_energia);
      if (((posicao_X_nave == posicao_X_energia + 1) && (posicao_Y_nave == posicao_Y_energia)) || ((posicao_X_nave == posicao_X_energia) && (posicao_Y_nave == posicao_Y_energia))) {
        desenha_pilha = false;
        posicao_X_energia = -1;
        gasolina += 50;
      }
    }


    delay(velocidade);
  } else  //Se a variavel for falsa chama a tela de menu
  {
    tela(vtela);
    if (digitalRead(botao_tiro) == HIGH) {
      reset();
    }
  }

  /*display.clear();
  display.print("Desligado");
  delay(500);
  display.clear();
  display.print("Ligado");
  delay(500);
  if(digitalRead(botao_cima) == HIGH)
  {
    display.clear();
    display.print("Manda Salve");
    delay(2000);
  }*/
}

//Funções do código
void desenha_Nave(int px, int py) {
  display.setCursor(px, py);
  display.write(1);
}

void desenha_Asteroide(int px, int py) {
  display.setCursor(px, py);
  display.write(2);
}

void desenha_Energia(int px, int py) {
  display.setCursor(px, py);
  display.write(4);
}

void desenha_Tiro(int px, int py) {
  display.setCursor(px, py);
  display.write(5);
}

void desenha_Explosao_Nave(int px, int py) {
  display.clear();
  display.setCursor(px, py);
  display.write(3);
  delay(1000);
  display.clear();
}

void desenha_Explosao_Asteroide(int px, int py) {
  //display.clear();
  display.setCursor(px, py);
  display.write(3);
  delay(1000);
  //display.clear();
}

void reset() {
  pontos = 0;
  gasolina = 100;
  game = true;
  vtela = 0;
}

void painel(int px) {
  display.setCursor(px, 0);
  display.print(pontos);
  display.setCursor(px, 1);
  display.print(gasolina);
}

void tela(int condicao)  //0 = Tela Inicial | 1 = Ganhou | 2 = Perdeu
{
  //char texto[6] = {};
  if (condicao < 1) {
    display.setCursor(3, 0);
    display.print("FOGUETE");
    display.setCursor(0, 1);
    display.print("Pressione Tiro");
  } else {
    display.setCursor(9, 0);
    display.print("pts:");
    display.setCursor(13, 0);
    display.print(pontos);
    display.setCursor(1, 0);
    if (condicao == 2)  //se a variavel condicao for igual a 0 vc perde
    {
      display.print("PERDEU");
    } else if (condicao == 1)  //se a variavel condicao for igual a 1 vc venceu
    {
      display.print("GANHOU");
    }
    display.setCursor(0, 1);
    display.print("Pressione Tiro");
  }
}