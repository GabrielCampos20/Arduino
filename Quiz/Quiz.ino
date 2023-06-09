#define btnYes 5
#define btnNop 4
#define btnNxt 6

int ledRight = 3;
int ledWrong = 2;

int answer = 0;
long randNumber;

bool state = false;

String perguntas[] = {
  "O Brasil é o maior país da América do Sul?",
  "A capital do Brasil é Brasília?",
  "A China é o país mais populoso do mundo?",
  "A Mona Lisa foi pintada por Leonardo da Vinci?",
  "A água ferve a 100 graus Celsius?",
  "A Lua emite luz própria?",
  "O Polo Norte é a região mais quente do planeta?",
  "A água é composta por dois elementos: carbono e oxigênio?",
  "O Rio Nilo é o maior rio do mundo?",
  "O Brasil faz fronteira com 10 países?",
  "O presidente do Brasil governa por tempo ilimitado?",
  "A Antártida é um continente coberto por vegetação exuberante?",
  "A França é um país da América do Sul?",
  "O Sol gira em torno da Terra?",
  "A Estátua da Liberdade está localizada em Paris?"
};

int respostas[] = { 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2 };

void setup() {
  Serial.begin(9600);
  pinMode(ledRight, OUTPUT);
  pinMode(ledWrong, OUTPUT);
  pinMode(btnYes, INPUT);
  pinMode(btnNop, INPUT);
  pinMode(btnNxt, INPUT);

  randomSeed(analogRead(0));
}

void loop() {
  if (digitalRead(btnNxt) == HIGH) {
    state = true;
    randNumber = random(15);
    Serial.println(perguntas[randNumber]);
    //Serial.println(respostas[randNumber]);
    while (state == true) {
      if (digitalRead(btnYes) == HIGH && digitalRead(btnNop) == LOW) {
        Serial.println("YES PRESSED");
        delay(500);
        answer = 1;
        if (answer == respostas[randNumber]) {
          Serial.println("RIGHT");
          digitalWrite(ledRight, HIGH);
          delay(1000);
          digitalWrite(ledRight, LOW);
          answer = 0;
          state = false;
        } else {
          Serial.println("WRONG");
          digitalWrite(ledWrong, HIGH);
          delay(1000);
          digitalWrite(ledWrong, LOW);
          answer = 0;
          state = false;
        }
      } else if (digitalRead(btnYes) == LOW && digitalRead(btnNop) == HIGH) {
        Serial.println("NOP PRESSED");
        delay(500);
        answer = 2;
        if (answer == respostas[randNumber]) {
          Serial.println("RIGHT");
          digitalWrite(ledRight, HIGH);
          delay(1000);
          digitalWrite(ledRight, LOW);
          answer = 0;
          state = false;
        } else {
          Serial.println("WRONG");
          digitalWrite(ledWrong, HIGH);
          delay(1000);
          digitalWrite(ledWrong, LOW);
          answer = 0;
          state = false;
        }
      }
    }
  }
}