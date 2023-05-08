#include <DallasTemperature.h>
#include <OneWire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

OneWire oneWire(7);
DallasTemperature sensors(&oneWire);
float temp;

int lamp = 10;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(lamp, OUTPUT);
}

void loop() {
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);
  /*if (temp <= 500) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperatura: ");
    lcd.setCursor(0, 1);
    lcd.print(String(temp) + "C");
    Serial.println(temp);
    digitalWrite(lamp, LOW);
    Serial.println("OFF");

  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperatura: ");
    lcd.setCursor(0, 1);
    lcd.print(String(temp) + "C");
    Serial.println(temp);
    digitalWrite(lamp, HIGH);
    Serial.println("ON");
  }*/

  digitalWrite(lamp, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura: ");
  lcd.setCursor(0, 1);
  lcd.print(String(temp) + "C");
  Serial.println(temp);
  digitalWrite(lamp, HIGH);
  Serial.println("ON");
}