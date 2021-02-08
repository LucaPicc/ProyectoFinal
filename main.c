/******************************************************
 * main.c
 *
 * Program Name:  hola_mundo
 *         Date:  2021-01-07
 *       Author:  YOUR_NAME
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  This is my program description..
 * 
 *****************************************************/
#include <avr/io.h>
//#define F_CPU 16000000U
#include "util/delay.h"
#include <avr/interrupt.h>
#include "USART/USART.h"
#include "ADC/ADC.h"
#include "USS/USS.h"
#include <stdlib.h>

char String[7] = "HOla";


uint32_t distance;

int main(){
	cli();
	
	USART_init();
	HCSR04_Init();
	DDRB |= (1<<DDB5);
	PORTB |= (1<<PORTB5);
	
	sei();

	while (1){
		uint32_t distance = getDistance();
		//dtostrf(distance,10,0,String);
		
		USART_putstring(String);
		if (distance < 3)
		{
			PORTB |= (1<<PORTB5);
		}
		else
		{
			PORTB &=~ (1<<PORTB5);
		}
		
	}
	return 0;
}