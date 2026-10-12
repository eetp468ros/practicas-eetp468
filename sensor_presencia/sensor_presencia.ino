#include <SoftwareSerial.h>

SoftwareSerial ld2420(8, 9); // RX=8 (OT1), TX=9 (RX del sensor)

const int LED_MOVIMIENTO = 4;
const int LED_ESTATICO = 5;
const int BUZZER = 10;         // Buzzer PASIVO (necesita tone())
const int LED_SIN_PRESENCIA = 7; // LED verde: encendido cuando no hay nadie

String linea = "";
int rangoActual = -1;
unsigned long ultimoCambio = 0;
bool hayPresencia = false;

enum Estado { SIN_PRESENCIA, MOVIMIENTO, ESTATICO };
Estado estadoActual = SIN_PRESENCIA;
Estado estadoAnterior = SIN_PRESENCIA;

const unsigned long TIEMPO_PARA_ESTATICO = 3000; // 3 seg sin cambios = estatico

// --- Configuracion del "sonar" ---
const int RANGO_CERCA = 0;    // Rango mas cercano que reporta el sensor
const int RANGO_LEJOS = 15;   // Rango mas lejano (ajustar segun lo que veas en el Serial)
const unsigned long PAUSA_CERCA = 80;   // ms entre pitidos cuando esta muy cerca
const unsigned long PAUSA_LEJOS = 1000; // ms entre pitidos cuando esta lejos
const unsigned long DURACION_PITIDO = 50; // ms que dura cada pitido
const unsigned int FRECUENCIA_CERCA = 2500; // Hz (mas agudo cuando esta cerca)
const unsigned int FRECUENCIA_LEJOS = 1000; // Hz (mas grave cuando esta lejos)

unsigned long ultimoPitido = 0;

void setup() {
  Serial.begin(115200);
  ld2420.begin(115200);
  pinMode(LED_MOVIMIENTO, OUTPUT);
  pinMode(LED_ESTATICO, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_SIN_PRESENCIA, OUTPUT);

  // Al arrancar no hay presencia: LED verde encendido
  digitalWrite(LED_SIN_PRESENCIA, HIGH);

  // Pitido de arranque: si no se escucha, revisar conexion del buzzer
  tone(BUZZER, 2000, 200);
  delay(250);

  Serial.println("Iniciando deteccion simple...");
}

void loop() {
  leerLinea();
  actualizarEstado();
  actualizarSonar();
}

void leerLinea() {
  while (ld2420.available()) {
    char c = ld2420.read();
    if (c == '\n') {
      linea.trim();
      procesarLinea(linea);
      linea = "";
    } else if (c != '\r') {
      linea += c;
    }
  }
}

void procesarLinea(String l) {
  if (l == "ON") {
    if (!hayPresencia) {
      Serial.println(">> Presencia detectada (ON)");
    }
    hayPresencia = true;
  } else if (l == "OFF") {
    if (hayPresencia) {
      Serial.println(">> Presencia perdida (OFF)");
    }
    hayPresencia = false;
    rangoActual = -1;
  } else if (l.startsWith("Range")) {
    int r = l.substring(6).toInt();
    if (rangoActual == -1) {
      rangoActual = r;
      ultimoCambio = millis();
      Serial.print(">> Rango inicial: ");
      Serial.println(r);
    } else if (abs(r - rangoActual) > 1) {
      Serial.print(">> Rango cambio de ");
      Serial.print(rangoActual);
      Serial.print(" a ");
      Serial.println(r);
      rangoActual = r;
      ultimoCambio = millis();
    }
  }
}

void actualizarEstado() {
  if (!hayPresencia) {
    estadoActual = SIN_PRESENCIA;
  } else {
    unsigned long quieto = millis() - ultimoCambio;
    estadoActual = (quieto >= TIEMPO_PARA_ESTATICO) ? ESTATICO : MOVIMIENTO;
  }

  // Solo actuamos (y avisamos) cuando el estado realmente cambia
  if (estadoActual != estadoAnterior) {
    switch (estadoActual) {
      case SIN_PRESENCIA:
        Serial.println("### ESTADO: SIN PRESENCIA");
        digitalWrite(LED_MOVIMIENTO, LOW);
        digitalWrite(LED_ESTATICO, LOW);
        digitalWrite(LED_SIN_PRESENCIA, HIGH);
        noTone(BUZZER);
        break;
      case MOVIMIENTO:
        Serial.println("### ESTADO: MOVIMIENTO");
        digitalWrite(LED_MOVIMIENTO, HIGH);
        digitalWrite(LED_ESTATICO, LOW);
        digitalWrite(LED_SIN_PRESENCIA, LOW);
        ultimoPitido = 0; // Que el primer pitido suene enseguida
        break;
      case ESTATICO:
        Serial.println("### ESTADO: ESTATICO");
        digitalWrite(LED_MOVIMIENTO, LOW);
        digitalWrite(LED_ESTATICO, HIGH);
        digitalWrite(LED_SIN_PRESENCIA, LOW);
        noTone(BUZZER);
        break;
    }
    estadoAnterior = estadoActual;
  }
}

// Pitidos tipo sonar: mientras hay movimiento, cuanto mas cerca esta
// el objeto, mas seguidos y mas agudos son los pitidos.
// No usa delay(), asi el sensor se sigue leyendo sin perder datos.
void actualizarSonar() {
  if (estadoActual != MOVIMIENTO) {
    return;
  }

  // Si todavia no llego ningun "Range", pitamos como si estuviera lejos
  int r = (rangoActual < 0) ? RANGO_LEJOS : constrain(rangoActual, RANGO_CERCA, RANGO_LEJOS);
  unsigned long pausa = map(r, RANGO_CERCA, RANGO_LEJOS, PAUSA_CERCA, PAUSA_LEJOS);
  unsigned int frecuencia = map(r, RANGO_CERCA, RANGO_LEJOS, FRECUENCIA_CERCA, FRECUENCIA_LEJOS);

  if (ultimoPitido == 0 || millis() - ultimoPitido >= pausa + DURACION_PITIDO) {
    tone(BUZZER, frecuencia, DURACION_PITIDO);
    ultimoPitido = millis();
    Serial.print("   beep rango=");
    Serial.print(r);
    Serial.print(" frec=");
    Serial.println(frecuencia);
  }
}
