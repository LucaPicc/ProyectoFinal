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
#include <stdlib.h>

char String[20] = "HOla";


int main(void)
{
	cli();
	ADC_init();
	DDRB |= (1<<DDB5);
	USART_init();
	PORTB |= (1<<PORTB5);
	
	sei();
	
	
	while (1)
	{
		float adcV = ADC_read(0);
		dtostrf(adcV,10,0,String);
		USART_putstring(String);

		if (adcV < 300)
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