#include "BluetoothSerial.h"

// Check if Bluetooth configs are enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Bluetooth Serial object
BluetoothSerial SerialBT;

// GPIO where LED is connected to
const int ledPin = 12;
bool led_state = false;

// Handle received and sent messages
String message = "";
char incomingChar;
String temperatureString = "";

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(115200);
  // Bluetooth device name
  SerialBT.begin("ESP32");
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  // Read received messages (LED control command)
  if (SerialBT.available()) {
    Serial.println("BT ta on");
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n') {
      message += String(incomingChar);
    } else {
      message = "";
    }
    Serial.write(incomingChar);
  }
  // Check received message and control output accordingly
  if (message == "led_on" || message == "1") {
    Serial.println("Chegou onde liga");
    digitalWrite(ledPin, HIGH);
  } else if (message == "led_off" || message == "2") {
    Serial.println("Chegou onde desliga");
    digitalWrite(ledPin, LOW);
  }
  delay(20);
}

bool check_state(bool item) {
  return item;
}