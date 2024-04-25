#include "ZEM_DIGITAL_PINS.h"
#include <CONSTANTE.h>
#include <ZEM_DIGITAL_FUNCTII.h>
#include <OBSTACOLE.h>

void setup() {
  led1on(),led2on();
  delay(2000);
  led1off(),led2off();
  Serial.begin(9600);
  //while(!Serial.available());
  Serial.println("Start");
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  forward(500);
  rotate_right(950);
  stop();
}

void loop() {
  read_sensors();//citeste senzorii
  readHC();
  if(wallDistance<14 and wallDistance!=-1) led1on(),led2on(),wall();
  //led2off();
  //printSensorValues();
  if(number_read==0 and values[0]){
    forward(100);
    turnRightUntilLine();
  }
  if(number_read>=7){ // daca numarul de senzori cititi este mai mare, este intersectie
    forward(t_forward_intersection); // merge in fata t_fo... milisecunde
    read_sensors(); //citeste din nou senzorii
    if(!line){ //daca nu vede linia, e giratoriu
      roundabout(); // executa rutina de giratoriu
    }
    else{
      resetPID();
      follow_line(basePWM); //daca nu reseteaza pidul si urmareste linia
    }
  }
  else{
    read_sensors();
    if((values[9]==1) and (values[0]==0) and (number_read>=3) and (number_read<=6)){
      led1on(),led2on();
      
      forward(t_forward_chicane);
      //stop();
      turnLeftUntilLine();
    }
    else if((values[9]==0) and (values[0]==1) and (number_read>=3) and (number_read<=6)){
      led1on(),led2on();
      
      forward(t_forward_chicane);
      //stop();
      turnRightUntilLine();
    }
    //else printSensorValues();
  }
  follow_line(basePWM);
  delay(10);
}