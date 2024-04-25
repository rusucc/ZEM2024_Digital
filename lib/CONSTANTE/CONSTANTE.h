#ifndef CONSTANTE_h
#define CONSTANTE_h
const int basePWM=45,KP = 3.65,KI = 0.0071,KD = 4;//0.0069

const int KP_wall=2, KI_wall = 0, KD_wall = 4,wallPWM = 30;
const int max_integral = 2000;
const int min_integral = -2000;
const int turnPWM=40;
const int forward_pwm = 30;
const int roundabout_pwm = 30;
const int rotate_pwm = 30;


const int t_forward_intersection = 80, t_forward_chicane = 200, t_exit = 100,t_wall = 100;
#endif