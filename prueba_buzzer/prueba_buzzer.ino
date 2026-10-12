// Prueba aislada del buzzer pasivo: sin sensor, solo pitidos.
// Si con esto no suena, el problema es de conexion o del buzzer.

const int BUZZER = 10;

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER, OUTPUT);
  Serial.println("Prueba de buzzer en pin 10");
}

void loop() {
  Serial.println("tone 1000 Hz");
  tone(BUZZER, 1000);
  delay(500);
  noTone(BUZZER);
  delay(500);

  Serial.println("tone 2500 Hz");
  tone(BUZZER, 2500);
  delay(500);
  noTone(BUZZER);
  delay(1000);
}
