/*
 * main.c
 * Author: Luca Piccinini
 * Descripción: Programa principal para proyecto de robot seguidor de linea
*/




#include <avr/io.h>
//#define F_CPU 16000000U
#include "util/delay.h"
#include <avr/interrupt.h>
#include "USART/USART.h"
#include "ADC/ADC.h"
#include "USS/USS.h"
#include "MOTOR/MOTOR.h"
#include <stdlib.h>

char String[10] = "HOla";

/*
uint32_t distance;
*/
int main(){
	cli();
	
	USART_init();
	//Ultrasonico_init();
	DDRB |= (1<<DDB5);
	PORTB |= (1<<PORTB5);
	ADC_init();
	MOTORES_init(100,50);
	MOTORES_cont(2,100,100);
	sei();
	

	while (1){
		//uint32_t distance = getDistance();
		float adcV = ADC_read(0);
		dtostrf(adcV,10,0,String);
		USART_putstring(String);
		
		if (adcV > 400 )
		{
			PORTB |= (1<<PORTB5);
			MOTOR_right_cont(1,100,100);
		}
		else
		{
			PORTB &=~ (1<<PORTB5);
			MOTOR_right_cont(2,100,100);
		}
		
	}
	return 0;
}