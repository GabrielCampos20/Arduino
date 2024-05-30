#include <WiFi.h>
#include <dht11.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Wifi network station credentials
#define WIFI_SSID "RIBEIRO CAMPOS"
#define WIFI_PASSWORD "jotabel0409"

// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "7133219263:AAElspWOj2TSCW8U4OTlHQWt--pAATE8JoU"
const unsigned long BOT_MTBS = 0;  // mean time between scan messages

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime;
bool Start = false;


int in1 = 17;
int in2 = 5;
int LED_PIN = 26;
int led_wifi = 16;


bool led_state = false;
bool in1_state = false;
bool in2_state = false;
//DHT Configs
dht11 DHT11;
#define DHT11PIN 4

void setup() {
  Serial.begin(115200);
  Serial.println();

  pinMode(led_wifi, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);  // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(led_wifi, HIGH);
    delay(250);
    digitalWrite(led_wifi, LOW);
    Serial.print(".");
    delay(250);
  }
  digitalWrite(led_wifi, HIGH);
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org");  // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600) {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
}



void loop() {
  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));
  int chk = DHT11.read(DHT11PIN);

  float temp = DHT11.temperature;
  float humi = DHT11.humidity;

  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    if (text == "/start") {
      bot.sendMessage(chat_id, "Hi, my name is J.A.R.V.I.S. Gabriel Campos has built me!");
      String keyboardJson = "[[\"/led\"],[\"/in1\"],[\"/in2\"],[\"/get_temp\"]]";
      bot.sendMessageWithReplyKeyboard(chat_id, "Escolha uma das opções", "", keyboardJson, true);
    }

    if (text == "/led") {
      while (1 == 1) {
        if (led_state == false) {
          digitalWrite(LED_PIN, HIGH);  // turn the LED on (HIGH is the voltage level)
          bot.sendMessage(chat_id, "Led turned on.", "");
          led_state = true;
          break;
        } else if (led_state == true) {
          digitalWrite(LED_PIN, LOW);  // turn the LED on (HIGH is the voltage level)
          bot.sendMessage(chat_id, "Led turned off.", "");
          led_state = false;
          break;
        }
      }
    }

    if (text == "/in1") {
      while (1 == 1) {
        if (in1_state == false) {
          digitalWrite(in1, HIGH);  // turn the LED on (HIGH is the voltage level)
          bot.sendMessage(chat_id, "in1 turned on.", "");
          in1_state = true;
          break;
        } else if (in1_state == true) {
          digitalWrite(in1, LOW);  // turn the LED on (HIGH is the voltage level)
          bot.sendMessage(chat_id, "in1 turned off.", "");
          in1_state = false;
          break;
        }
      }
    }

    if (text == "/in2") {
      while (1 == 1) {
        if (in2_state == false) {
          digitalWrite(in2, HIGH);  // turn the LED on (HIGH is the voltage level)
          bot.sendMessage(chat_id, "in2 turned on.", "");
          in2_state = true;
          break;
        } else if (in2_state == true) {
          digitalWrite(in2, LOW);  // turn the LED on (HIGH is the voltage level)
          bot.sendMessage(chat_id, "in2 turned off.", "");
          in2_state = false;
          break;
        }
      }
    }

    if (text == "/get_temp") {

      String temp_conv = String(temp);
      String humi_conv = String(humi);

      String message = "TEMP: " + temp_conv + " || HUMI: " + humi_conv + "";

      bot.sendMessage(chat_id, "Carregando Dados...", "");
      delay(500);
      Serial.println(message);
      bot.sendMessage(chat_id, message, "");
    }
  }
}