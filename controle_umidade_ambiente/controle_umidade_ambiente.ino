#include <SPI.h>
#include <Wire.h>
#include <dht11.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

dht11 DHT11;
#define DHT11PIN 19

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
  get_temp();

  display.setCursor(0, 50);
  display.println("Made by Gabriel Dev");
}

void get_temp() {
  int chk = DHT11.read(DHT11PIN);

  float temp = DHT11.temperature;
  float humi = DHT11.humidity;

  String temp_conv = String(temp);
  String humi_conv = String(humi);

  String message = "TEMP: " + temp_conv + " || HUMI: " + humi_conv + "";

  Serial.println(message);
  display.setCursor(0, 0);
  display.println("TEMPERATURA: " + temp_conv + "C");
  display.println("HUMIDADE: " + humi_conv + "%");
  display.display();
  delay(2000);
  display.clearDisplay();
}