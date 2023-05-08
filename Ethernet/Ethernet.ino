#include <SPI.h>
#include <UIPEthernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 1, 250 };
EthernetServer server(80);

int ledSala = 8;
int ledCozinha = 7;
int ledQuarto = 6;
String readString = String(30);
int statusSala = 0;
int statusCozinha = 0;
int statusQuarto = 0;

void setup() {
  Ethernet.begin(mac, ip);
  server.begin();
  pinMode(ledSala, OUTPUT);
  pinMode(ledCozinha, OUTPUT);
  pinMode(ledQuarto, OUTPUT);
  digitalWrite(ledSala, LOW);
  digitalWrite(ledCozinha, LOW);
  digitalWrite(ledQuarto, LOW);
}
void loop() {
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (readString.length() < 100) {
          readString += c;
        }
        if (c == '\n') {
          if (readString.indexOf("?") < 0) {
          }
          if (readString.indexOf("ledSala=1") > 0) {
            digitalWrite(ledSala, HIGH);
            statusSala = 1;
          }
          if (readString.indexOf("ledSala=0") > 0) {
            digitalWrite(ledSala, LOW);
            statusSala = 0;
          }
          if (readString.indexOf("ledCozinha=1") > 0) {
            digitalWrite(ledCozinha, HIGH);
            statusCozinha = 1;
          }
          if (readString.indexOf("ledCozinha=0") > 0) {
            digitalWrite(ledCozinha, LOW);
            statusCozinha = 0;
          }
          if (readString.indexOf("ledQuarto=1") > 0) {
            digitalWrite(ledQuarto, HIGH);
            statusQuarto = 1;
          }
          if (readString.indexOf("ledQuarto=0") > 0) {
            digitalWrite(ledQuarto, LOW);
            statusQuarto = 0;
          }



          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<body style=background-color:#ADD8E6>");
          client.println("<center><font color='blue'><h1>TheSilentKiller - Automatic House</font></center></h1>");
          client.println("<h1><center>CONTROLE SALA</center></h1>");


          
          if (statusSala == 1) {
            client.println("<center><form method=get name=LEDSALA><input type=hidden name=ledSala value=0 /><input type=submit value=APAGAR></form></center>");
          } else {
            client.println("<center><form method=get name=LEDSALA><input type=hidden name=ledSala value=1 /><input type=submit value=ACENDER></form></center>");
          }
          client.println("<center><font size='5'>STATUS SALA: </font></center>");
          if (statusSala == 1) {
            client.println("<center><font color='green' size='5'>LIGADO</font></center>");
          } else {
            client.println("<center><font color='red' size='5'>DESLIGADO</font></center>");
          }
          client.println("<hr />");
          client.println("<hr />");
          client.println("<h1><center>CONTROLE COZINHA</center></h1>");
          if (statusCozinha == 1) {
            client.println("<center><form method=get name=LEDCOZINHA><input type=hidden name=ledCozinha value=0 /><input type=submit value=APAGAR></form></center>");
          } else {
            client.println("<center><form method=get name=LEDCOZINHA><input type=hidden name=ledCozinha value=1 /><input type=submit value=ACENDER></form></center>");
          }
          client.println("<center><font size='5'>STATUS COZINHA: </font></center>");
          if (statusCozinha == 1) {
            client.println("<center><font color='green' size='5'>LIGADO</font></center>");
          } else {
            client.println("<center><font color='red' size='5'>DESLIGADO</font></center>");
          }
          client.println("<hr />");
          client.println("<hr />");
          client.println("<h1><center>CONTROLE QUARTO</center></h1>");
          if (statusQuarto == 1) {
            client.println("<center><form method=get name=LEDQUARTO><input type=hidden name=ledQuarto value=0 /><input type=submit value=APAGAR></form></center>");
          } else {
            client.println("<center><form method=get name=LEDQUARTO><input type=hidden name=ledQuarto value=1 /><input type=submit value=ACENDER></form></center>");
          }
          client.println("<center><font size='5'>STATUS QUARTO: </font></center>");
          if (statusQuarto == 1) {
            client.println("<center><font color='green' size='5'>LIGADO</font></center>");
          } else {
            client.println("<center><font color='red' size='5'>DESLIGADO</font></center>");
          }
          client.println("</body></html>");
          readString = "";
          client.stop();
        }
      }
    }
  }
}