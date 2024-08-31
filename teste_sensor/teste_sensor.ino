int trigger = 29;
int echo = 28;

int cm = 0;
int pontos = 0;
int distanceToPoint = 10;

void setup() {
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  // calculate the distance to the target in cm
  cm = 0.01723 * readUltrasonicDistance(trigger, echo);
  // convert to inches by dividing by 2.54
  Serial.print("CM: ");
  Serial.println(cm);
  if (cm <= distanceToPoint && pontos < 5) {
    pontos++;
    Serial.println(pontos);
  } else {
    Serial.println(pontos);
  }
  delay(2000);  // Wait for 2000 millisecond(s)
}

long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}