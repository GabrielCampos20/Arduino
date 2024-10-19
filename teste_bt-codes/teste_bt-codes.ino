#include <SoftwareSerial.h>

const int pinoTX = 52;
const int pinoRX = 53;
int dadoBluetooth = 0;

SoftwareSerial bluetooth(pinoTX, pinoRX);

int numero;

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  bluetooth.print("$");
  bluetooth.print("$");
  bluetooth.print("$");
  delay(100);
}

void loop() {
  numero = 10;
  if (bluetooth.available()) {
    dadoBluetooth = bluetooth.read();
    Serial.println(dadoBluetooth);
    if (dadoBluetooth == 70 || dadoBluetooth == 66 || dadoBluetooth == 82 || dadoBluetooth == 76 || dadoBluetooth == 83) {
      Serial.println("Normal");
    } else {
      do {
        Serial.println(dadoBluetooth);
        numero = Serial.read();
      } while (numero != 10);
    }
  }
}