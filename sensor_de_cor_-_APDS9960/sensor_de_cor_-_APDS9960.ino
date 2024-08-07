/***************************************************************************
  This is a library for the APDS9960 digital proximity, ambient light, RGB, and gesture sensor

  This sketch puts the sensor in color mode and reads the RGB and clear values.

  Designed specifically to work with the Adafruit APDS9960 breakout
  ----> http://www.adafruit.com/products/3595

  These sensors use I2C to communicate. The device's I2C address is 0x39

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Dean Miller for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds1;
Adafruit_APDS9960 apds2;

void setup() {
  Serial.begin(115200);

  if (!apds1.begin() || !apds2.begin()) {
    Serial.println("failed to initialize device! Please check your wiring.");
  } else Serial.println("Device initialized!");

  //enable color sensign mode
  apds1.enableColor(true);
  apds2.enableColor(true);
}

void loop() {
  //create some variables to store the color data in
  uint16_t r1, r2, g1, g2, b1, b2, c1, c2;

  //wait for color data to be ready
  while (!apds1.colorDataReady() || !apds2.colorDataReady()) {
    delay(5);
  }

  //get the data and print the different channels
  apds1.getColorData(&r1, &g1, &b1, &c1);
  apds2.getColorData(&r2, &g2, &b2, &c2);

  Serial.print("red 1: ");
  Serial.print(r1);
  Serial.print("red 2: ");
  Serial.print(r2);

  Serial.print(" green 1: ");
  Serial.print(g1);
  Serial.print(" green 2: ");
  Serial.print(g2);

  Serial.print(" blue 1: ");
  Serial.print(b1);
  Serial.print(" blue 2: ");
  Serial.print(b2);

  Serial.print(" clear 1: ");
  Serial.print(c1);
  Serial.print(" clear 2: ");
  Serial.println(c2);
  Serial.println();

  delay(5000);
}