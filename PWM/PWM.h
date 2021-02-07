/*
 * IncFile1.h
 *
 * Created: 22/12/2020 20:28:06
 *  Author: Luca
 */ 


#ifndef PWM_H_
#define PWM_H_
#include <avr/io.h>

	void PWM_init(int frec, int duty);
	void PWM_on();
	void PWM_off();

#endif /* PWM_H_ */