/*version 13NOV2026 - busqueda girando en el lugar*/
/*Valores modificables para el Robot*/
int VelocidadBusqueda = 100;         /*-----> Valor entre 70 y 255<----*/
int VelocidadGiroBusqueda = 120;     /*-----> Valor entre 70 y 255 (si gira muy rapido no ve al rival)<----*/
int VelocidadAtaque = 230;           /*-----> Valor entre 70 y 255<----*/
int VelocidadGiro = 170;             /*-----> Antes 80 Valor entre 70 y 255<----*/
int Distanciaoponente = 40;          /*-----> Valor entre 10 y 70 (el dohyo mide 77 cm)<----*/
unsigned long TiempoGiroBusqueda = 900;   /*-----> ms girando en el lugar buscando (aprox. 1 vuelta)<----*/
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
          while(SensorOponente()==1){Ataque();}
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
            while(SensorOponente()==1){Ataque();}
          }
        }
        if(SensorLineaI()==1){
          //Serial.println("Giro Izquierdo"); 
          millisViejo=millis();
          while((millis()-millisViejo)<tiempoFrenado){Atras();}//vamos para atras 
          millisViejo=millis();
          while((millis()-millisViejo)<tiempoLimite){
            GiroIzq();
            while(SensorOponente()==1){Ataque();}
          }
        }
        ReiniciarBusqueda();
      }
      Busqueda();
      while(SensorOponente()==1){Ataque();}
    }//while
  }//If
} //Loop

// Busqueda: gira en el lugar para "barrer" el dohyo con el sensor.
// Si da una vuelta sin ver al rival, avanza un poco y vuelve a girar.
void Busqueda(){
  unsigned long transcurrido = millis() - inicioFaseBusqueda;

  if(buscandoGirando){
    mD.motor(MotorDerecho,BACKWARD, VelocidadGiroBusqueda);
    mI.motor(MotorIzquierdo,FORWARD, VelocidadGiroBusqueda);
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

int SensorOponente(){
  unsigned long t; 
  float d; 

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
