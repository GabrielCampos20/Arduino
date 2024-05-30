// Libraries einbinden
#include <dht11.h>

dht11 DHT11;
#define DHT11PIN 4

void setup() {
  Serial.begin(9600);
}

void loop() {
  get_temp();
}

void get_temp() {
  int chk = DHT11.read(DHT11PIN);

  float temp = DHT11.temperature;
  float humi = DHT11.humidity;

  String temp_conv = String(temp);
  String humi_conv = String(humi);

  // Serial.print("TEMP: ");
  // Serial.print(temp_conv);

  // Serial.print(" || ");

  // Serial.print("HUMI: ");
  // Serial.println(humi_conv);

  String message = "TEMP: " + temp_conv + " || HUMI: " + humi_conv + "";

  Serial.println(message);

  delay(2000);
}