// Prueba del sensor ultrasonico del minisumo, SIN motores.
// Abrir el Monitor Serie a 9600 y acercar/alejar un objeto frente al robot.

#define Echo 10
#define Trigger 9

void setup() {
  Serial.begin(9600);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  digitalWrite(Trigger, LOW);
  Serial.println("Prueba sensor minisumo");
}

void loop() {
  digitalWrite(Trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);

  unsigned long t = pulseIn(Echo, HIGH, 30000);

  Serial.print("t = ");
  Serial.print(t);
  Serial.print(" us   ->   ");
  if (t == 0) {
    Serial.println("SIN ECO");
  } else {
    Serial.print(t / 58.0);
    Serial.println(" cm");
  }
  delay(100);
}
