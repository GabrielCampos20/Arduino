#include <LiquidCrystal_I2C.h>
#include <ezButton.h>
#include <WiFi.h>
#include <time.h>

const char* ssid = "RIBEIRO CAMPOS";
const char* password = "jotabel0409";

const char* ntpServer = "south-america.pool.ntp.org";
const long gmtOffset_sec = -14400;
const int daylightOffset_sec = 3600;

int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

ezButton button(23);

int led = 26;
bool ledState = false;

int receiver = 34;  //PINO ANALÓGICO UTILIZADO PELO FOTOTRANSISTOR
int emitter = 19;

void setup() {
  Serial.begin(9600);  //INICIALIZAÇÃO DA SERIAL

  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");

  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  pinMode(receiver, INPUT);  //DEFINE O PINO COMO ENTRADA
  pinMode(emitter, OUTPUT);

  pinMode(led, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("WELCOME TSK!");
  delay(2000);
  lcd.clear();
}

void loop() {
  button.loop();
  digitalWrite(emitter, LOW);
  printLocalTime();

  if (button.isReleased()) {
    digitalWrite(emitter, HIGH);
    alterState();
  }
}

void alterState() {
  if (analogRead(receiver) < 800 && ledState == false) {
    Serial.println("Recebendo sinal infravermelho");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ESTADO LED: ON");
    digitalWrite(led, HIGH);
    ledState = !ledState;
  } else if (analogRead(receiver) < 800 && ledState == true) {
    Serial.println("Sinal infravermelho interrompido");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ESTADO LED: OFF");
    digitalWrite(led, LOW);
    ledState = !ledState;
  }
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%H:%M");
  lcd.setCursor(0, 1);
  lcd.print(&timeinfo, "HORA:%Hh%M");
}