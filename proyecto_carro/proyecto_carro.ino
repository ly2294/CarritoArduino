/*
 * Natalia Isabel Hernandez Naveros
 * Leidy Yuliana Quintero Jaramillo
 * Jhon Anderson Sanchez Buritica 
 */

#include <Servo.h>  
Servo servo1;

int AngSerDer = 15;  ////Voltear para la derecha
int AngSerCen = 90; ////// Voltear para el centro
int AngSerIzq = 165; /////Voltear para la izquierda

int izqA = 5;      //// pines 5,6,7 y 8 al puente H
int izqB = 6;
int derA = 7;
int derB = 8;
int vel = 180;            // Velocidad de los motores se puede variar (0-255)
int estado = '1';         // inicia en espera

int pecho = 2;            
int ptrig = 3;           
int duracion, distancia;  //  Calcular la distancia

int DisDer;
int DisIzq;
int DisEcoDer;
int DisEcoIzq;
int DisFrenteEco;

void setup() 
{
  Serial.begin(9600);    // inicia el puerto serial para comunicacion con el Bluetooth
  servo1.attach(11);   //// servo1 se conecta al pin 11.
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);

  pinMode(pecho, INPUT);   // el pin 2 se utiliza como entrada (pecho)
  pinMode(ptrig,OUTPUT);   // el pin 3 se utiliza como salida  (ptrig)
  pinMode(13,OUTPUT);

}

void loop() 

{

  if(Serial.available()>0){        // lee el bluetooth y almacena en estado
    estado = Serial.read();
  }
  if(estado=='a')
{           // Boton desplazar al Frente
    servo1.write(AngSerCen);
    analogWrite(derB, 0);   
    analogWrite(izqB, 0);
    analogWrite(derA, vel); 
    analogWrite(izqA, vel);
 }
  if(estado=='b')
{          // Boton IZQUIERDA
    servo1.write(AngSerIzq);
    analogWrite(derB, vel);   
    analogWrite(izqB, 0);
    analogWrite(derA, 0); 
    analogWrite(izqA, vel);     
  }
  if(estado=='c')
{         // Boton Parar
    servo1.write(AngSerCen);
    analogWrite(derB, 0);   
    analogWrite(izqB, 0);
    analogWrite(derA, 0);   
    analogWrite(izqA, 0);
  }
  if(estado=='d')
{          // Boton DERECHA
    servo1.write(AngSerDer);
    analogWrite(derB, 0);   
    analogWrite(izqB, vel);
    analogWrite(izqA, 0);
    analogWrite(derA, vel); 
  }

  if(estado=='e')
{          // Boton Reversa
    servo1.write(AngSerCen);
    analogWrite(derA, 0);   
    analogWrite(izqA, 0);
    analogWrite(derB, vel); 
    analogWrite(izqB, vel);     
  }

}
