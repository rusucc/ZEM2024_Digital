#include "ZEM_DIGITAL_PINS.h"
#include <CONSTANTE.h>
#include <ZEM_DIGITAL_FUNCTII.h>
#include <OBSTACOLE.h>

void setup() {
  led1on(),led2on();
  delay(2000);
  led1off(),led2off();
  Serial.begin(9600);
  Serial.println("Start");
}

void loop() {
  read_sensors();//citeste senzorii
  if(number_read>=6){ // daca numarul de senzori cititi este mai mare, este intersectie
    forward(t_forward_intersection); // merge in fata t_fo... milisecunde
    read_sensors(); //citeste din nou senzorii
    if(!line){ //daca nu vede linia, e giratoriu
      roundabout(); // executa rutina de giratoriu
    }
    else{
      resetPID();
      follow_line(); //daca nu reseteaza pidul si urmareste linia
    }
  }else{
    if(values[0]){
      forward(t_forward_chicane);
      turnLeftUntilLine();
    }
    else if(values[number_sensors-1]){
      forward(t_forward_chicane);
      turnRightUntilLine();
    }
  }
  //follow_line();

  Serial.println();
  Serial.println(position);

  delay(10);
}