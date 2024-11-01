#ifndef ZEM_DIGITAL_FUNCTII_h
#define ZEM_DIGITAL_FUNCTII_h
#include <ZEM_DIGITAL_PINS.h>
#include <CONSTANTE.h>
int values[number_sensors],position=0,number_read=0;
bool line = false;
float error=0, old_error=0,P=0;
float I=0,D=0;

inline void sendPWM_left(int left_pwm=0, bool left_forward=true){
    if(left_pwm<0) left_pwm = 0;
    else if(left_pwm>255) left_pwm = 255;
    if(left_forward) analogWrite(left_1,left_pwm),digitalWrite(left_2,0);
    else analogWrite(left_2,left_pwm),digitalWrite(left_1,left_pwm);
}
inline void sendPWM_right(int right_pwm=0, bool right_forward=true){
    if(right_pwm<0) right_pwm = 0;
    else if(right_pwm>255) right_pwm = 255;
    if(right_forward) analogWrite(right_1,right_pwm),digitalWrite(right_2,0);
    else analogWrite(right_2,right_pwm),digitalWrite(right_1,right_pwm);
}
inline void read_sensors(){
    line = false;
    for(int i=0; i<number_sensors;i++){
        values[i] = digitalRead(sensor_pins[i]);
        if (values[i]){
            line = true;
        }
        
    }
}
inline void calculatePosition(){
    int sum=0,w_avg=0;
    number_read = 0;
    for(int i=1;i<number_sensors-1;i++){
        if (values[i]){
            sum++;
            number_read++;
            w_avg += (i*10) * values[i];
        }
        
    }
    if (!line)
    {
        if (position < (number_sensors-3) * 10 / 2)
            position = 0;
        else
            position = (number_sensors - 3) * 10;
    }
    else
        position = w_avg / sum;
}
inline double calculatePID(int currentPosition, int targetPosition){
    error = currentPosition-targetPosition;
    int P = KP*error;
    I += KI*error;
    if(error*old_error<=0) I = 0;
    D = KD*(error-old_error);
    old_error = error;
    return P+I+D;
}
inline void follow_line(){
  read_sensors();
  calculatePosition();
  int outpid = calculatePID(position,3500);
  sendPWM_left(basePWM-outpid);
  sendPWM_right(basePWM+outpid);
  delay(10);
}
inline void resetPID(){
    I = 0;
    error = 0;
    old_error = 0;
}
inline void led1on(){
    digitalWrite(led1,HIGH);
}
inline void led1off(){
    digitalWrite(led1,LOW);
}
inline void led2on(){
    digitalWrite(led2,HIGH);
}
inline void led2off(){
    digitalWrite(led2,LOW);
}
#endif