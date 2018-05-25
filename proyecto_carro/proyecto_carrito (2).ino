/*
 * Natalia Isabel Hernandez Naveros
 * Leidy Yuliana Quintero Jaramillo
 * Jhon Anderson Sanchez Buritica 
 */

#include <Servo.h>  
Servo servo1;

int AngSerDer = 15;  // Angulo para la derecha
int AngSerCen = 90; // Angulo para el centro
int AngSerIzq = 165; // Angulo para la izquierda

int izqA = 5;  // Pines 5 del puente H
int izqB = 6; // Pines 6 del puente H
int derA = 7; // Pines 7 del puente H
int derB = 8; // Pines 8 del puente H
int vel = 180; // Velocidad de los motores
int estado = '1'; 

int pecho = 2; 
int ptrig = 3;
int duracion, distancia; 

int DisDer;
int DisIzq;
int DisEcoDer;
int DisEcoIzq;
int DisFrenteEco;

void setup() {
  Serial.begin(9600);    // Comunicacion con el Bluetooth
  servo1.attach(11); 
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);

  pinMode(pecho, INPUT);   
  pinMode(ptrig,OUTPUT);   
  pinMode(13,OUTPUT);

}

void loop() {

  if(Serial.available()>0){ // Lee el bluetooth y almacena en estado
    estado = Serial.read();
  }
  if(estado=='a'){ // Boton Desplazar Adelante
    servo1.write(AngSerCen);
    analogWrite(derB, 0);   
    analogWrite(izqB, 0);
    analogWrite(derA, vel); 
    analogWrite(izqA, vel);
 }
  if(estado=='b'){ // Boton Izquierda
    servo1.write(AngSerIzq);
    analogWrite(derB, vel);   
    analogWrite(izqB, 0);
    analogWrite(derA, 0); 
    analogWrite(izqA, vel);     
  }
  if(estado=='c'){ // Boton Detener
    servo1.write(AngSerCen);
    analogWrite(derB, 0);   
    analogWrite(izqB, 0);
    analogWrite(derA, 0);   
    analogWrite(izqA, 0);
  }
  if(estado=='d'){ // Boton Derecha
    servo1.write(AngSerDer);
    analogWrite(derB, 0);   
    analogWrite(izqB, vel);
    analogWrite(izqA, 0);
    analogWrite(derA, vel); 
  }

  if(estado=='e'){ // Boton Reversa
    servo1.write(AngSerCen);
    analogWrite(derA, 0);   
    analogWrite(izqA, 0);
    analogWrite(derB, vel); 
    analogWrite(izqB, vel);     
  }


  if (estado =='f'){ 

     digitalWrite(ptrig, HIGH); 
     delay(0.01);
     digitalWrite(ptrig, LOW);
    
     duracion = pulseIn(pecho, HIGH);
     distancia = (duracion/2) / 29;
     delay(10);
    
     if (distancia <= 15 && distancia >=2){
      
      digitalWrite(13,HIGH);
      //Voltear izquierda
      servo1.write(AngSerDer);
      analogWrite(derB, 0);   
      analogWrite(izqB, 0);
      analogWrite(derA, 0);   
      analogWrite(izqA, 0);
      delay(700);
      digitalWrite(ptrig, HIGH); 
      delay(0.01);
      digitalWrite(ptrig, LOW);
      duracion = pulseIn(pecho, HIGH);
      DisEcoDer = (duracion/2) / 29;
      delay(10);
      DisDer = DisEcoDer;
      delay(500);

      //Voltear izquierda
      servo1.write(AngSerIzq);
      analogWrite(derB, 0);   
      analogWrite(izqB, 0);
      analogWrite(derA, 0);   
      analogWrite(izqA, 0);
      delay(700);
      digitalWrite(ptrig, HIGH);
      delay(0.01);
      digitalWrite(ptrig, LOW);
      duracion = pulseIn(pecho, HIGH);             
      DisEcoIzq = (duracion/2) / 29;
      delay(10);
      DisIzq = DisEcoIzq;
      delay(500);

      if (DisDer > DisIzq){
        // se detiene un momento voltea, retrocede un poco y elige una direccion
        servo1.write(AngSerCen);         
        delay(400);                 
        analogWrite(derA, 0);   
        analogWrite(izqA, 0);
        analogWrite(derB, vel); 
        analogWrite(izqB, vel);
        delay(300);
        analogWrite(derB, 0);   
        analogWrite(izqB, vel);
        analogWrite(izqA, 0);
        analogWrite(derA, vel); 
        delay(500);
        analogWrite(derB, 0);   
        analogWrite(izqB, 0);
        analogWrite(derA, 0);   
        analogWrite(izqA, 0);
        delay(200);
  
      }

      if (DisDer < DisIzq){
        servo1.write(AngSerCen);
        delay(400);
        analogWrite(derA, 0);   
        analogWrite(izqA, 0);
        analogWrite(derB, vel); 
        analogWrite(izqB, vel);
        delay(300);
        analogWrite(derB, vel);   
        analogWrite(izqB, 0);
        analogWrite(derA, 0); 
        analogWrite(izqA, vel);     
        delay(500);
        analogWrite(derB, 0);   
        analogWrite(izqB, 0);
        analogWrite(derA, 0);   
        analogWrite(izqA, 0);
        delay(200);
      }

    
     }
     else{ // Si no hay obstaculos se desplaza al frente 
         analogWrite(derB, 0);   
         analogWrite(izqB, 0);
         analogWrite(derA, vel); 
         analogWrite(izqA, vel);
     }
  }
  if(estado=='1'){ // Detiene los motores queda en espera
     servo1.write(AngSerCen);
     analogWrite(derB, 0);   
     analogWrite(izqB, 0);
     analogWrite(derA, 0);   
     analogWrite(izqA, 0);
  }
}
