#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // Largura da tela OLED, em pixels
#define SCREEN_HEIGHT 64 // Altura da tela OLED, em pixels

// Declaração para um display SSD1306 conectado a I2C (SDA, pinos SCL)
#define OLED_RESET     4 //Pino de reset # (ou -1 se compartilhar o pino de reset do Arduino)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//Pino ligado ao pino D0 do sensor
int pinoentrada = 2;
int rpm;

float ms;
float pi=3.1415;
float convert = 3.6;
float kmh;



volatile byte pulsos;
unsigned long millis_old;

//Altere o numero abaixo de acordo com o seu disco encoder
unsigned int pulsos_por_volta = 20;

void contador()
{
  //Incrementa contador
  pulsos++;
}

void setup()
{
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = gerar tensão de exibição de 3,3 V internamente
   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //Pino do sensor como entrada
  pinMode(pinoentrada, INPUT);
  //Interrupcao 0 - pino digital 2
  //A cada pulso, aciona o contador
  attachInterrupt(0, contador, FALLING);
  pulsos = 0;
  rpm = 0;
  millis_old = 0;
}

void loop()
{
  //Atualiza contador a cada 1000 milisegundos, ou seja, 1 segundo
  if (millis() - millis_old >= 1000)
  {
    //Desabilita interrupcao enquanto faz o calculo
    detachInterrupt(0);
    rpm = (60 * 1000 / pulsos_por_volta ) / (millis() - millis_old) * pulsos;
    millis_old = millis();
    pulsos = 0;


    
    //Mostra o valor de RPM no serial monitor
    Serial.print("RPM = ");
    Serial.print(rpm, DEC);
    ms = (2*pi*0.01*rpm)/60;
    Serial.print(" - ");
    Serial.print("m/s = ");
    Serial.print(ms);
    kmh=ms*convert;
    Serial.print(" - ");
    Serial.print("Km/h = ");
    Serial.println(kmh);
    
  display.clearDisplay();
  //display.drawRect(x, y, largura, altura, cor);
  display.drawRect( 0, 0, 40, 16, WHITE);
  display.drawRect(44, 0, 40, 16, WHITE);
  display.drawRect(88, 0, 40, 16, WHITE);
  
  display.setTextSize(1);             
  display.setTextColor(SSD1306_WHITE);       
  display.setCursor(10,3);             
  display.println(F("Rpm"));
  display.setCursor(52,3);             
  display.println(F("m/s"));
  display.setCursor(95,3);             
  display.println(F("km/h"));
  
  //display.drawRect(x, y, largura, altura, cor);
  display.drawRect( 0, 18, 40, 40, WHITE);
  display.drawRect(44, 18, 40, 40, WHITE);
  display.drawRect(88, 18, 40, 40, WHITE);
  
  display.setCursor(10,32);             
  display.println(rpm, DEC);
  display.setCursor(52,32);             
  display.println(ms, 2);
  display.setCursor(95,32);             
  display.println(kmh, 2);
  
  display.display();
  
    //Habilita interrupcao
    attachInterrupt(0, contador, FALLING);
  }
}
