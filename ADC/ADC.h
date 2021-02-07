/*
 * ADC.h
 *
 * Created: 23/12/2020 02:59:37
 *  Author: Luca
 */ 


#ifndef ADC_H_
#define ADC_H_
	//#define F_CPU  16000000U
	#include <avr/io.h>
	#include "util/delay.h"
	void ADC_init();
	int ADC_read(int num_port);

#endif /* ADC_H_ */
