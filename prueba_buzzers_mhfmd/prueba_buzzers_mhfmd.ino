// Prueba de 2 modulos buzzer MH-FMD (3 pines: VCC, I/O, GND)
// El MH-FMD se activa con nivel BAJO: LOW = suena, HIGH = silencio.

const int BUZZER1 = 7;
const int BUZZER2 = 8;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);
  digitalWrite(BUZZER1, HIGH); // HIGH = apagado
  digitalWrite(BUZZER2, HIGH);
  Serial.println("Prueba de buzzers MH-FMD");
}

void loop() {
  // Prueba 1: modo ACTIVO (solo prender/apagar)
  Serial.println("Buzzer 1 - modo activo");
  digitalWrite(BUZZER1, LOW);
  delay(500);
  digitalWrite(BUZZER1, HIGH);
  delay(500);

  Serial.println("Buzzer 2 - modo activo");
  digitalWrite(BUZZER2, LOW);
  delay(500);
  digitalWrite(BUZZER2, HIGH);
  delay(500);

  // Prueba 2: modo PASIVO (con tone), por si el buzzer resulta ser pasivo
  Serial.println("Buzzer 1 - modo pasivo (tone)");
  tone(BUZZER1, 1500);
  delay(500);
  noTone(BUZZER1);
  digitalWrite(BUZZER1, HIGH);
  delay(500);

  Serial.println("Buzzer 2 - modo pasivo (tone)");
  tone(BUZZER2, 1500);
  delay(500);
  noTone(BUZZER2);
  digitalWrite(BUZZER2, HIGH);
  delay(1500);
}
