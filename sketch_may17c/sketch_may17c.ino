#include <ArduinoJson.h>
#include "DHT.h"
#define NUM_SENSORES 5
#define DHTTYPE DHT22
// int sensorPins[NUM_SENSORES] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12};
int sensorPins[NUM_SENSORES] = { 3, 4, 5, 6, 7 };

DHT* dht[NUM_SENSORES];

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORES; i++) {
    dht[i] = new DHT(sensorPins[i], DHTTYPE);
    dht[i]->begin();

    // Serial.print("Sensor da porta ");
    // Serial.print(sensorPins[i]);
    // Serial.println(" Ok!");
  }
}

void loop() {
  // if (Serial.available() > 0) {
  //   String hora = Serial.readStringUntil('\n');
  //   Serial.print("Hora recebida: ");
  //   Serial.println(hora);
  // }

  for (int i = 0; i < NUM_SENSORES; i++) {
    float humidity = dht[i]->readHumidity();
    float temperature = dht[i]->readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      // Serial.print("Falha ao ler o sensor ");
      // Serial.println(i);
      continue;
    } else {
      Serial.print("/S");
      Serial.print(i);
      Serial.print("/U");
      Serial.print(humidity);
      Serial.print("/T");
      Serial.print(temperature);
      Serial.println("");
    }

    delay(2000);
  }
  // Serial.println("");
}
