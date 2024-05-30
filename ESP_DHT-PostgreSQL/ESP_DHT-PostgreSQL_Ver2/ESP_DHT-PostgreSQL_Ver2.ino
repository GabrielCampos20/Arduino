#include <WiFi.h>
#include <WiFiClient.h>
#include <SimplePgSQL.h>

int led_wifi = 5;
int led_data = 6;

#include <dht11.h>
dht11 DHT11;
#define DHT11PIN 4

float t = 0.0;
float h = 0.0;

const char *ssid = "RIBEIRO CAMPOS";
const char *pass = "jotabel0409";
WiFiClient client;

IPAddress PGIP(192, 168, 1, 6);       // your PostgreSQL server IP
const char user[] = "postgres";       // your database user
const char password[] = "123456789";  // your database password
const char dbname[] = "esp32";        // your database name
char buffer[1024];
PGconnection conn(&client, 0, 1024, buffer);
char inbuf[128];
int pg_status = 0;

unsigned long previousMillis = 0;  // variable to store the last time the task was run
const long interval = 60000;       // time interval in milliseconds (eg 1000ms = 1 second)

void setup() {
  Serial.begin(9600);

  pinMode(led_wifi, OUTPUT);
  pinMode(led_data, OUTPUT);

  WiFi.begin(ssid, pass);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(led_wifi, HIGH);
    delay(500);
    digitalWrite(led_wifi, LOW);
  }
  Serial.print("Connected to WiFi network with IP Address: ");
  digitalWrite(led_wifi, HIGH);
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 60 seconds (timerDelay variable), it will take 60 seconds before publishing the first reading.");
}

void doPg(void) {

  //Aqui ele passa os parâmetros de conexão pro SimplePgSql
  char *msg;
  int rc;
  if (!pg_status) {
    conn.setDbLogin(PGIP, user, password, dbname, "utf8");
    pg_status = 1;
    return;
  }

  //Aqui ele verifica se a conexão foi bem sucedida
  if (pg_status == 1) {
    rc = conn.status();
    if (rc == CONNECTION_BAD || rc == CONNECTION_NEEDED) {
      char *c = conn.getMessage();
      if (c) Serial.println(c);
      pg_status = -1;
      digitalWrite(led_data, HIGH);
      delay(500);
      digitalWrite(led_data, LOW);
      //Em caso negativo ele muda o status pra -1 e tenta novamente
    } else if (rc == CONNECTION_OK) {
      pg_status = 2;
      Serial.println("Starting query");
      digitalWrite(led_data, HIGH);
      //Em caso positivo ele muda o status pra 2 e exibe a mensagem acima
    }
    return;
  }

  if (pg_status == 2 && strlen(inbuf) > 0) {
    if (conn.execute(inbuf)) goto error;
    Serial.println("Working...");
    pg_status = 3;
    memset(inbuf, 0, sizeof(inbuf));
  }

  if (pg_status == 3) {
    rc = conn.getData();
    int i;
    if (rc < 0) goto error;
    if (!rc) return;
    if (rc & PG_RSTAT_HAVE_COLUMNS) {
      for (i = 0; i < conn.nfields(); i++) {
        if (i) Serial.print(" | ");
        Serial.print(conn.getColumn(i));
      }
      Serial.println("\n==========");
    } else if (rc & PG_RSTAT_HAVE_ROW) {
      for (i = 0; i < conn.nfields(); i++) {
        if (i) Serial.print(" | ");
        msg = conn.getValue(i);
        if (!msg) msg = (char *)"NULL";
        Serial.print(msg);
      }
      Serial.println();
    } else if (rc & PG_RSTAT_HAVE_SUMMARY) {
      Serial.print("Rows affected: ");
      Serial.println(conn.ntuples());
    } else if (rc & PG_RSTAT_HAVE_MESSAGE) {
      msg = conn.getMessage();
      if (msg) Serial.println(msg);
    }
    if (rc & PG_RSTAT_READY) {
      pg_status = 2;
      Serial.println("Waiting query");
    }
  }
  return;
error:
  msg = conn.getMessage();
  if (msg) Serial.println(msg);
  else Serial.println("UNKNOWN ERROR");
  if (conn.status() == CONNECTION_BAD) {
    Serial.println("Connection is bad");
    pg_status = -1;
  }
}

void loop() {
  int chk = DHT11.read(DHT11PIN);
  t = DHT11.temperature;
  h = DHT11.humidity;

  delay(50);
  doPg();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (WiFi.status() == WL_CONNECTED) {

      Serial.print("Humidity = ");
      Serial.print(h);
      Serial.print("% ");
      Serial.print("Temperature = ");
      Serial.print(t);
      Serial.println(" C ");

      sprintf(inbuf, "insert into dht_data (temp,humidity) values(%.2f,%.2f)", t, h);
      //As queries tem que ser enviadas nesse formato
    } else {
      Serial.println("WiFi Disconnected");
    }
  }
}
