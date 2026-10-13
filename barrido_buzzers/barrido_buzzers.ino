// Barrido de frecuencias para encontrar el tono donde cada buzzer suena mas fuerte.
// Mira el Monitor Serie (9600) y anota la frecuencia que mas se escucha en cada uno.

const int BUZZER1 = 7;
const int BUZZER2 = 8;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);
  digitalWrite(BUZZER1, HIGH); // MH-FMD: HIGH = silencio
  digitalWrite(BUZZER2, HIGH);
}

void barrido(int pin, const char* nombre) {
  Serial.print("=== ");
  Serial.println(nombre);
  for (unsigned int f = 500; f <= 5000; f += 250) {
    Serial.print(f);
    Serial.println(" Hz");
    tone(pin, f);
    delay(400);
  }
  noTone(pin);
  digitalWrite(pin, HIGH);
  delay(1500);
}

void loop() {
  barrido(BUZZER1, "Buzzer 1");
  barrido(BUZZER2, "Buzzer 2");
}
