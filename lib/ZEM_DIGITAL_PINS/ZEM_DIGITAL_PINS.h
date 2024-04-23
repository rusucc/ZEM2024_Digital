#ifndef ZEM_DIGITAL_PINS_h
#define ZEM_DIGITAL_PINS_h
#include "Arduino.h"
const int number_sensors = 10;
const int sensor_pins[number_sensors] ={A14,A15,A16,A17,A8,A9,A10,A11,A12,A13};
const int led1 = A0;
const int led2 = A1;
const int left_1 = 29;
const int left_2 = 7;
const int right_1 = 8;
const int right_2 = 28;
const int left_encoder_1 = 6;
const int left_encoder_2 = 9;
const int right_encoder_1 = 3;
const int right_encoder_2 = 4;
const int left_vl53_xshut = 30; //digital only
const int right_vl53_xshut = 31; //digital only
const int extra_sensor_1 = 11; //pwm, 5v
const int extra_sensor_2 = 12;  //pwm, 5v
// bluetooth pe rx1/tx1
//a4,a5 i2c
#endif