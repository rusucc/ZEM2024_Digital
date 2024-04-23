#ifndef OBSTACOLE_h
#define OSBTACOLE_h
#include <ZEM_DIGITAL_FUNCTII.h>
#include <ZEM_DIGITAL_PINS.h>
inline void turnLeftUntilLine(){
    while(!(values[5] or values[6])){
        sendPWM_left(turnPWM,false);
        sendPWM_right(turnPWM,true);
        read_sensors();
        delay(10);
    }
    resetPID();
}
inline void turnRightUntilLine(){
    while(!(values[5] or values[6])){
        sendPWM_left(turnPWM,true);
        sendPWM_right(turnPWM,false);
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
inline void roundabout(){
    turnRightUntilLine(); 
      while(values[number_sensors]){
        follow_line();
      }
      forward(t_forward_intersection);
      turnRightUntilLine();
      resetPID();
}
#endif