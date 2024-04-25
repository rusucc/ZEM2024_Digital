#ifndef OBSTACOLE_h
#define OSBTACOLE_h
#include <ZEM_DIGITAL_FUNCTII.h>
#include <ZEM_DIGITAL_PINS.h>
#include <HCSR04.h>
const int echo_pin = 0;
const int trig_pin = 1;
UltraSonicDistanceSensor distanceSensor(trig_pin, echo_pin);
int wallDistance=distanceSensor.measureDistanceCm();
inline void turnLeftUntilLine(){
    while(!(values[6] or values[5])){
        sendPWM_left(-turnPWM);
        sendPWM_right(turnPWM);
        read_sensors();
        delay(10);
    }
    resetPID();
}
inline void turnRightUntilLine(){
    while(!(values[4] or values[5])){
        sendPWM_left(turnPWM);
        sendPWM_right(-turnPWM);
        read_sensors();
        delay(10);
    }
    resetPID();
}
inline void forward(int T){
    elapsedMillis t = 0;
    while(t<=T){
        sendPWM_left(forward_pwm);
        sendPWM_right(forward_pwm);
    }
}
inline void rotate_right(int T){
    elapsedMillis t;
    while(t<T){
        sendPWM_left(rotate_pwm);
        sendPWM_right(-rotate_pwm);
    }
}
inline void roundabout(){
    turnRightUntilLine(); 
    resetPID();
    led1on(),led2on();
    while(!values[0]){
        read_sensors();
        follow_line(roundabout_pwm);
        delay(10);
    }
    led1off(),led2off();
    
    forward(t_exit);
    turnRightUntilLine();
    resetPID();
}
inline float calculatePID_wall(float current, float target){
    static float error=0, old_error=0, I=0;
    error = current - target;
    float P = KP_wall*error;
    I += KI_wall * error;
    float D = KD_wall*(error - old_error);
    return P+I+D;
}
inline void readHC(){
    wallDistance=distanceSensor.measureDistanceCm();
    if(wallDistance>=30) wallDistance = 30;
    Serial.println(wallDistance);
}
inline void wall(){
    readHC();
    while(wallDistance>=1 and wallDistance<=10){
        readHC();
        forward(10);
        delay(1);
    }
    rotate_right(500);
    read_sensors();
    while(!line){
        read_sensors();
        forward(10);
        delay(1);
    }
}
#endif