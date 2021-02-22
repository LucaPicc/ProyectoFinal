/*
 * MOTOR.h
 * Autor: Luca Piccinini
*/

#ifndef MOTOR_H_
#define MOTOR_H_

    #include <avr/io.h>
    void MOTORES_init(int freq, int duty);
    int MOTORES_cont(int state, int duty, int frec);
    int MOTOR_right_cont(int state, int freq, int duty);
    int MOTOR_left_cont(int state, int freq, int duty);

#endif /* MOTOR_H_ */