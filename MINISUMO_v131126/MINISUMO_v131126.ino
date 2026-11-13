/*version 13NOV2026 - busqueda girando de a pasos, ataque respeta la linea*/
/*Valores modificables para el Robot*/
int VelocidadBusqueda = 100;         /*-----> Valor entre 70 y 255<----*/
int VelocidadGiroBusqueda = 120;     /*-----> Valor entre 90 y 255 (fuerza de cada pasito de giro)<----*/
int VelocidadAtaque = 230;           /*-----> Valor entre 70 y 255<----*/
int VelocidadGiro = 170;             /*-----> Antes 80 Valor entre 70 y 255<----*/
int Distanciaoponente = 40;          /*-----> Valor entre 10 y 70 (el dohyo mide 77 cm)<----*/
unsigned long PasoGiroBusqueda = 40;      /*-----> ms de cada pasito de giro (mas chico = barrido mas fino)<----*/
unsigned long TiempoGiroBusqueda = 3000;  /*-----> ms buscando en el lugar (aprox. 1 vuelta)<----*/
unsigned long TiempoAvanceBusqueda = 300; /*-----> ms avanzando antes de volver a girar<----*/
/*----------------------------------*/

/*No modificar el siguiete programa*/
#include <MotorDriver.h>

MotorDriver mD;
MotorDriver mI;

#define PinLienaI A0
#define PinLienaD A1 
#define Echo 10    //Pin servo de arriba (Servo_1)
#define Trigger 9  //Pin servo de Abajo  (Servo_2)
#define MotorDerecho 3 
#define MotorIzquierdo 4 

const unsigned long tiempoFrenado = 300; // tiempo retroceso
int tiempoLimite = 500;
unsigned long millisViejo = 0;

// Estado de la busqueda: alterna entre girar en el lugar y avanzar un poco
bool buscandoGirando = true;
unsigned long inicioFaseBusqueda = 0;


void setup() {
  //Serial.begin(9600);   //iniciar puerto serie
  pinMode(PinLienaI, INPUT);  //definir pin como entrada
  pinMode(PinLienaD, INPUT);  //definir pin como entrada
  pinMode(Trigger, OUTPUT); //Configuramoms el pin de "trigger" como salida
  pinMode(Echo, INPUT);  //Configuramoms el pin de "echo" como entrada
  digitalWrite(Trigger, LOW);//Ponemos en voltaje bajo(0V) el pin de "trigger"

}

void loop() {
  if(millis() >= 5000){
    inicioFaseBusqueda = millis();
    while(1){
      if(SensorLineaD()==1 and SensorLineaI()==1){
        //Serial.println("Giro Ambos"); 
        millisViejo=millis();
        while((millis()-millisViejo)<tiempoFrenado){Atras();}//vamos para atras 
        millisViejo=millis();
        while((millis()-millisViejo)<tiempoLimite){
          GiroDer();
          Atacar();
        }
        ReiniciarBusqueda();
      }
      else if(SensorLineaD()==1 or SensorLineaI()==1){
        if(SensorLineaD()==1){
          //Serial.println("Giro Derecho"); 
          millisViejo=millis();
          while((millis()-millisViejo)<tiempoFrenado){Atras();}//vamos para atras 
          millisViejo=millis();
          while((millis()-millisViejo)<tiempoLimite){
            GiroDer();
            Atacar();
          }
        }
        if(SensorLineaI()==1){
          //Serial.println("Giro Izquierdo"); 
          millisViejo=millis();
          while((millis()-millisViejo)<tiempoFrenado){Atras();}//vamos para atras 
          millisViejo=millis();
          while((millis()-millisViejo)<tiempoLimite){
            GiroIzq();
            Atacar();
          }
        }
        ReiniciarBusqueda();
      }
      Busqueda();
      Atacar();
    }//while
  }//If
} //Loop

// Busqueda: gira en el lugar para "barrer" el dohyo con el sensor.
// Si da una vuelta sin ver al rival, avanza un poco y vuelve a girar.
void Busqueda(){
  unsigned long transcurrido = millis() - inicioFaseBusqueda;

  if(buscandoGirando){
    // Gira un pasito, frena y espera a que el sensor este listo:
    // asi la medicion siguiente se hace con el robot quieto, apuntando a un angulo fijo.
    // (Girando sin parar, el HC-SR04 mide pocas veces por segundo y el rival "se le pasa")
    mD.motor(MotorDerecho,BACKWARD, VelocidadGiroBusqueda);
    mI.motor(MotorIzquierdo,FORWARD, VelocidadGiroBusqueda);
    delay(PasoGiroBusqueda);
    Frenar();
    SensorLibre(200);
    if(transcurrido >= TiempoGiroBusqueda){
      buscandoGirando = false;
      inicioFaseBusqueda = millis();
    }
  }
  else{
    mD.motor(MotorDerecho,FORWARD, VelocidadBusqueda);
    mI.motor(MotorIzquierdo,FORWARD, VelocidadBusqueda);
    if(transcurrido >= TiempoAvanceBusqueda){
      buscandoGirando = true;
      inicioFaseBusqueda = millis();
    }
  }
}

// Despues de esquivar la linea, la busqueda vuelve a empezar girando
void ReiniciarBusqueda(){
  buscandoGirando = true;
  inicioFaseBusqueda = millis();
}

// Ataca mientras vea al rival, pero corta apenas detecta la linea del borde
// (antes el ataque no miraba la linea y el robot se podia salir del dohyo).
// Para empezar a atacar pide 2 lecturas seguidas, asi un eco falso no lo dispara.
void Atacar(){
  if(HayLinea()){return;}
  if(SensorOponente()==0){return;}
  if(SensorOponente()==0){return;}
  while(!HayLinea() and SensorOponente()==1){Ataque();}
}

int HayLinea(){
  if(SensorLineaD()==1 or SensorLineaI()==1){return 1;}
  return 0;
}

void Frenar(){
  mD.motor(MotorDerecho,FORWARD, 0);
  mI.motor(MotorIzquierdo,FORWARD, 0);
}

void Ataque(){
  mD.motor(MotorDerecho,FORWARD, VelocidadAtaque);
  mI.motor(MotorIzquierdo,FORWARD, VelocidadAtaque);
}

void GiroIzq(){
  mD.motor(MotorDerecho,FORWARD, VelocidadGiro);
  mI.motor(MotorIzquierdo,BACKWARD, VelocidadGiro);
}

void GiroDer(){
  mD.motor(MotorDerecho,BACKWARD, VelocidadGiro);
  mI.motor(MotorIzquierdo,FORWARD, VelocidadGiro);
}

void Atras(){
  mD.motor(MotorDerecho,BACKWARD, 255);
  mI.motor(MotorIzquierdo,BACKWARD, 255);
}

int SensorLineaI(){
  if (digitalRead(PinLienaI) == LOW){
    delay(1);
    if(digitalRead(PinLienaI) == LOW){return 1;}
  }
  return 0;
}

int SensorLineaD(){
  if (digitalRead(PinLienaD) == LOW){
    delay(1);
    if(digitalRead(PinLienaD) == LOW){return 1;}
  }
  return 0;
}

// Espera a que el HC-SR04 termine la medicion anterior (pin Echo en LOW).
// Mientras Echo esta en HIGH el sensor ignora los disparos nuevos.
bool SensorLibre(unsigned long maxEspera){
  unsigned long inicio = millis();
  while(digitalRead(Echo) == HIGH){
    if(millis() - inicio >= maxEspera){return false;}
  }
  return true;
}

int SensorOponente(){
  unsigned long t; 
  float d; 

  if(!SensorLibre(60)){return 0;} // sensor todavia ocupado: no se puede medir

  digitalWrite(Trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10); // el HC-SR04 necesita al menos 10 us
  digitalWrite(Trigger, LOW);
  
  // Timeout amplio: algunos HC-SR04 tardan varios ms en empezar el eco,
  // y con un timeout corto nunca llegaban a medir
  t = pulseIn(Echo, HIGH, 25000);
  if (t == 0){return 0;} // sin eco = no hay rival (antes contaba como distancia 0)

  d = t * 0.000001 * 34300.0 / 2.0; 

  if (d <= Distanciaoponente){return 1;}
  return 0;
}
