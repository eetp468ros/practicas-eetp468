// Sensor de gas MQ-5 Grupo Milena
// Placa: Arduino Uno
const int sensorGas = 2; // Pin DO del MQ-5
const int buzzer = 8;    // Buzzer PASIVO (necesita tone())
const int led = 13;      // LED de alarma de gas
const int ledEncendido = 7; // LED que indica que el equipo esta encendido

const unsigned long TIEMPO_CALENTAMIENTO = 60000; // 1 minuto para que el MQ-5 se estabilice

int estadoAnterior = -1;

void setup() {
  pinMode(sensorGas, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(ledEncendido, OUTPUT);

  // LED de encendido: queda prendido mientras la placa funcione
  digitalWrite(ledEncendido, HIGH);

  Serial.begin(9600);

  // Pitido corto de arranque: confirma que el buzzer funciona
  tone(buzzer, 2000, 200);

  // El MQ-5 necesita calentarse antes de dar lecturas confiables
  Serial.println("Calentando sensor MQ-5...");
  while (millis() < TIEMPO_CALENTAMIENTO) {
    digitalWrite(led, (millis() / 500) % 2); // LED parpadea mientras calienta
  }
  digitalWrite(led, LOW);
  Serial.println("Sensor listo");
}

void loop() {

  int estadoGas = digitalRead(sensorGas);

  if (estadoGas == LOW) { // El sensor detectó gas
    digitalWrite(led, HIGH);
    // Sirena: alterna entre un tono agudo y uno grave
    tone(buzzer, 2000);
    delay(250);
    tone(buzzer, 1000);
    delay(250);
  } else { // No hay gas
    digitalWrite(led, LOW);
    noTone(buzzer);
    delay(500);
  }

  // Solo escribimos en el Monitor Serie cuando cambia el estado
  if (estadoGas != estadoAnterior) {
    if (estadoGas == LOW) {
      Serial.println("¡Gas detectado!");
    } else {
      Serial.println("Sin detección de gas");
    }
    estadoAnterior = estadoGas;
  }
}
