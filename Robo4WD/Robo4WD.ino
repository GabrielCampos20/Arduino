/* Q0357
 * Autor - BrincandoComIdeias
 * KIT ROBO 4WD ARDUCORE
 */

#include <HCSR04.h>         // INCLUI BIBLIOTECA HCSR04 
#include <AFMotor.h>        // INCLUI A BIBLIOTECA DA MOTOR SHIELD
#include <SoftwareSerial.h> // INCLUI SERIAL DO BLUETOOTH
SoftwareSerial bluetooth(A1, A0 ); // RX(TX DO MÓDULO BT), TX(RX DO MÓDULO BT)

#define FORWARD 2 //VALOR DA BIBLIOTECA 1
#define BACKWARD 1 //VALOR DA BIBLIOTECA 2

// INSTANCIANDO MOTORES
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

// INSTANCIANDO SENSOR ULTRASONICO
HCSR04 sensorDistancia( A2, A3 ); //PINO TRIGGER, PINO ECHO

// VARIÁVEL PARA RECEBER COMANDO DO BLUETOOTH
char comando = 0 ;
// VARIÁVEL PARA ARMAZENAR DISTANCIA MEDIDA NO SENSOR
float distancia;

void setup() {
  bluetooth.begin(9600); //INICIA COMUNICAÇÃO SERIAL DO BLUETOOTH
  //Serial.begin(9600);   //INICIA SERIAL MONITOR

  // VELOCIDADE DOS MOTORES
  motor1.setSpeed(180);  // 255 VELOCIDADE MAXIMA
  motor2.setSpeed(180);  // 255 VELOCIDADE MAXIMA
  motor3.setSpeed(180);  // 255 VELOCIDADE MAXIMA
  motor4.setSpeed(180);  // 255 VELOCIDADE MAXIMA

  // MOTORES INICIAM PARADOS
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  
}

void loop() {
  //ENQUANTO O BLUETOOTH ESTIVER ATIVO EXECUTA O BLOCO
  while (bluetooth.available()) { 
    comando = bluetooth.read();  // ARMAZENA NA VARIÁVEL COMANDO A LEITURA DO BLUETOOTH
    distancia = sensorDistancia.dist();
//    Serial.print("Comando: ");
//    Serial.println(comando);     // IMPRIME O COMANDO NO SERIAL MONITOR
//    Serial.print("Distancia: ");
//    Serial.println(distancia);     // IMPRIME A DISTANCIA NO SERIAL MONITOR
    if(comando == 'F' && distancia >= 20) { //MOVIMENTO PARA FRENTE (F DE FOWARD) SE A DISTANCIA FOR MAIOR QUE 20cm
      moverFrente();
    }
    else if (comando == 'B') {   // MOVIMENTO PARA TRAS     (B DE BACKWARD)
      moverTras();
    }
    else if (comando == 'L') {   // MOVIMENTO PARA ESQUERDA (L DE LEFT)
      moverEsquerda();
    }
    else if (comando == 'R') {   // MOVIMENTO PARA DIREITA  (R DE RIGHT)
      moverDireita();
    } else { // CASO RECEBA 'S' OU ALGUMA COISA NÃO ESPERADA MANTÉM PARADO
      ficarParado();
    }
  }  
}

void moverFrente() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void moverTras() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}
void moverDireita() {
  motor3.run(FORWARD);
  motor2.run(FORWARD);
  motor1.run(RELEASE);
  motor4.run(RELEASE);
}
void moverEsquerda() {
  motor3.run(RELEASE);
  motor2.run(RELEASE);
  motor1.run(FORWARD);
  motor4.run(FORWARD);
}
void ficarParado() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
