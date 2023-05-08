#include <SD.h>
#include <SPI.h>

int seconds;
int minutes;
int hours;

File myFile;
int pinoSS = 53;

#include <DHT.h>;

#define DHTPIN 7
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(pinoSS, OUTPUT);
  dht.begin();

  if (SD.begin()) {
    Serial.println("SD Card pronto para uso.");
  } else {
    Serial.println("Falha na inicialização do SD Card.");
  }
}

void loop() {
  float umid = dht.readHumidity();
  float temp = dht.readTemperature();
  Serial.println("Temperatura: " + (String)temp + "*C | Umidade: " + (String)umid+" | Hora: "+(String)hours+"h"+(String)minutes+"m"+(String)seconds+"s");
  escreverDados();
  tempo();
  Serial.println("-------------------------------------------------------");
  delay(2000);
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

void escreverDados(){
  float umid = dht.readHumidity();
  float temp = dht.readTemperature();
  myFile = SD.open("dados.txt", FILE_WRITE);
  if (myFile){
    myFile.println("BGN --> DATA: 06/05/2023 | HORA: 18h50");
    myFile.println("SENSOR 01 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 02 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 03 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 04 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 05 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 06 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 07 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 08 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 09 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 10 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 11 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 12 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 13 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 14 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 15 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 16 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 17 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 18 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 19 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 20 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 21 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 22 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 23 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 24 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("SENSOR 25 | UMID : "+(String)umid+" | TEMP : "+(String)temp+"*C");
    myFile.println("END --> DATA: 06/05/2023 | HORA: 18h50");
    myFile.close();
    Serial.println("Salvo.");
  }else{
    Serial.println("Erro ao abrir o arquivo.");
  }
}