#include <SD.h>
#include <SPI.h>
#include <DHT.h>;

int seconds;
int minutes;
int hours;

File myFile;
int pinoSS = 53;


#define DHTPIN01 53
#define DHTPIN02 52
#define DHTPIN03 51
#define DHTPIN04 50
#define DHTPIN05 49
#define DHTPIN06 48
#define DHTPIN07 47
#define DHTPIN08 46
#define DHTPIN09 45
#define DHTPIN10 44
#define DHTPIN11 43
#define DHTPIN12 42
#define DHTPIN13 41
#define DHTPIN14 40
#define DHTPIN15 39
#define DHTPIN16 38
#define DHTPIN17 37
#define DHTPIN18 36
#define DHTPIN19 35
#define DHTPIN20 34
#define DHTPIN21 33
#define DHTPIN22 32
#define DHTPIN23 31
#define DHTPIN24 30
#define DHTPIN25 29

DHT dht[] = {
  { DHTPIN01, DHT22 },
  { DHTPIN02, DHT22 },
  { DHTPIN03, DHT22 },
  { DHTPIN04, DHT22 },
  { DHTPIN05, DHT22 },
  { DHTPIN06, DHT22 },
  { DHTPIN07, DHT22 },
  { DHTPIN08, DHT22 },
  { DHTPIN09, DHT22 },
  { DHTPIN10, DHT22 },
  { DHTPIN11, DHT22 },
  { DHTPIN12, DHT22 },
  { DHTPIN13, DHT22 },
  { DHTPIN14, DHT22 },
  { DHTPIN15, DHT22 },
  { DHTPIN16, DHT22 },
  { DHTPIN17, DHT22 },
  { DHTPIN18, DHT22 },
  { DHTPIN19, DHT22 },
  { DHTPIN20, DHT22 },
  { DHTPIN21, DHT22 },
  { DHTPIN22, DHT22 },
  { DHTPIN23, DHT22 },
  { DHTPIN24, DHT22 },
  { DHTPIN25, DHT22 },
};

float humidity[4];
float temperature[4];

void setup() {
  Serial.begin(9600);
  for (auto& sensor : dht) {
    sensor.begin();
  }
  pinMode(pinoSS, OUTPUT);
  if (SD.begin()) {
    Serial.println("SD Card pronto para uso.");
  } else {
    Serial.println("Falha na inicialização do SD Card.");
  }
}

void loop() {
  for (int i = 0; i < 25; i++) {
    temperature[i] = dht[i].readTemperature();
    humidity[i] = dht[i].readHumidity();
  }

  for (int i = 0; i < 25; i++) {
    Serial.print(F("Temperature "));
    Serial.print(i);
    Serial.println(temperature[i]);
    Serial.print(F("Humidity "));
    Serial.print(i);
    Serial.println(humidity[i]);
  }

  /*void escreverDados() {
  float umid = dht.readHumidity();
  float temp = dht.readTemperature();
  myFile = SD.open("dados.txt", FILE_WRITE);
  if (myFile) {
    myFile.println("Temperatura: " + (String)temp + "*C | Umidade: " + (String)umid+" | Hora: "+(String)hours+"h"+(String)minutes+"m"+(String)seconds+"s");
    myFile.println("-------------------------------------------------------");
    myFile.close();
    Serial.println("Salvo.");
  } else {
    Serial.println("Arquivo não pôde ser aberto.");
  }
}*/
}

void tempo() {
  seconds = seconds + 2;
  if (seconds == 60) {
    minutes = minutes + 1;
    seconds = 0;
  } else if (minutes == 59) {
    hours = hours + 1;
    minutes = 0;
  }
}

/*void escreverDados() {
  float umid = dht.readHumidity();
  float temp = dht.readTemperature();
  myFile = SD.open("dados.txt", FILE_WRITE);
  if (myFile) {
    myFile.println("BGN --> DATA: 06/05/2023 | HORA: 18h50");
    myFile.println("SENSOR 01 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 02 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 03 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 04 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 05 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 06 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 07 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 08 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 09 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 10 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 11 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 12 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 13 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 14 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 15 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 16 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 17 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 18 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 19 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 20 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 21 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 22 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 23 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 24 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("SENSOR 25 | UMID : " + (String)umid + " | TEMP : " + (String)temp + "*C");
    myFile.println("END --> DATA: 06/05/2023 | HORA: 18h50");
    myFile.close();
    Serial.println("Salvo.");
  } else {
    Serial.println("Erro ao abrir o arquivo.");
  }
}*/