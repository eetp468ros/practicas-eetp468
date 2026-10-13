// Baston inteligente para personas con discapacidad visual
// Placa: Arduino Nano o Uno (mismos pines)
//
// Mide la distancia con un HC-SR04 y avisa con:
//  - Buzzer pasivo: pitidos mas seguidos y agudos cuanto mas cerca esta el obstaculo
//  - Micro motor de vibracion: vibra mas fuerte cuanto mas cerca
//
// IMPORTANTE: el motor NO se conecta directo al pin. Va con un transistor
// (ver conexiones en el README o en la explicacion).

const int TRIG = 9;
const int ECHO = 10;
const int BUZZER = 8;   // Buzzer PASIVO (necesita tone())
const int MOTOR = 5;    // Pin PWM -> base del transistor (resistencia 1k)

// --- Zonas de distancia (en cm) ---
const int DIST_MUY_CERCA = 30;   // Menos de esto: tono continuo + vibracion maxima
const int DIST_MAXIMA = 150;     // Mas de esto: silencio
const unsigned long PAUSA_CERCA = 80;    // ms entre pitidos cerca
const unsigned long PAUSA_LEJOS = 800;   // ms entre pitidos lejos
const unsigned long DURACION_PITIDO = 50;
const unsigned int FRECUENCIA_CERCA = 2500; // Hz
const unsigned int FRECUENCIA_LEJOS = 1000; // Hz
// Motor de 3V (4x8mm) alimentado con 5V: el PWM se limita a ~60%
// para que reciba en promedio unos 3V y no se dañe. NO subir de 153.
const int VIBRACION_MIN = 70;   // PWM minimo para que el motor arranque (ajustar)
const int VIBRACION_MAX = 150;  // ~2,9V promedio

const unsigned long INTERVALO_MEDICION = 60; // ms entre mediciones (minimo recomendado del HC-SR04)

unsigned long ultimaMedicion = 0;
unsigned long ultimoPitido = 0;
int distancia = -1; // -1 = nada a la vista
bool tonoContinuo = false;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(MOTOR, OUTPUT);
  digitalWrite(TRIG, LOW);

  Serial.begin(9600);

  // Aviso de encendido: dos pitidos y una vibracion corta
  analogWrite(MOTOR, VIBRACION_MAX);
  tone(BUZZER, 1500, 100);
  delay(200);
  tone(BUZZER, 2000, 100);
  delay(200);
  analogWrite(MOTOR, 0);

  Serial.println("Baston listo");
}

void loop() {
  if (millis() - ultimaMedicion >= INTERVALO_MEDICION) {
    ultimaMedicion = millis();
    distancia = medirDistanciaFiltrada();
    actualizarVibracion();

    Serial.print("Distancia: ");
    if (distancia < 0) {
      Serial.println("libre");
    } else {
      Serial.print(distancia);
      Serial.println(" cm");
    }
  }

  actualizarSonido();
}

// Una medicion del HC-SR04. Devuelve cm, o -1 si no hay eco.
int medirDistancia() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Timeout de 25 ms (~4 m): si no vuelve el eco, no hay obstaculo
  unsigned long duracion = pulseIn(ECHO, HIGH, 25000);
  if (duracion == 0) {
    return -1;
  }
  return duracion / 58; // microsegundos -> cm
}

// Toma 3 mediciones y se queda con la del medio (mediana),
// asi una lectura erronea suelta no hace pitar al baston.
int medirDistanciaFiltrada() {
  int a = medirDistancia();
  delay(10);
  int b = medirDistancia();
  delay(10);
  int c = medirDistancia();

  // Las lecturas sin eco cuentan como "muy lejos"
  if (a < 0) a = 9999;
  if (b < 0) b = 9999;
  if (c < 0) c = 9999;

  int mediana = max(min(a, b), min(max(a, b), c));
  if (mediana > DIST_MAXIMA) {
    return -1;
  }
  return mediana;
}

void actualizarVibracion() {
  if (distancia < 0) {
    analogWrite(MOTOR, 0);
    return;
  }
  int d = constrain(distancia, DIST_MUY_CERCA, DIST_MAXIMA);
  int fuerza = map(d, DIST_MUY_CERCA, DIST_MAXIMA, VIBRACION_MAX, VIBRACION_MIN);
  analogWrite(MOTOR, fuerza);
}

void actualizarSonido() {
  // Nada cerca: silencio
  if (distancia < 0) {
    if (tonoContinuo) {
      noTone(BUZZER);
      tonoContinuo = false;
    }
    return;
  }

  // Muy cerca: tono continuo
  if (distancia <= DIST_MUY_CERCA) {
    if (!tonoContinuo) {
      tone(BUZZER, FRECUENCIA_CERCA);
      tonoContinuo = true;
    }
    return;
  }

  if (tonoContinuo) {
    noTone(BUZZER);
    tonoContinuo = false;
  }

  // Zona intermedia: pitidos tipo sonar
  unsigned long pausa = map(distancia, DIST_MUY_CERCA, DIST_MAXIMA, PAUSA_CERCA, PAUSA_LEJOS);
  unsigned int frecuencia = map(distancia, DIST_MUY_CERCA, DIST_MAXIMA, FRECUENCIA_CERCA, FRECUENCIA_LEJOS);

  if (millis() - ultimoPitido >= pausa + DURACION_PITIDO) {
    tone(BUZZER, frecuencia, DURACION_PITIDO);
    ultimoPitido = millis();
  }
}
