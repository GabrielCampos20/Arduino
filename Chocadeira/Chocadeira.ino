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
  Serial.println(temp);
  digitalWrite(lamp, HIGH);
  delay(5000);
  digitalWrite(lamp, LOW);
  delay(5000);
}