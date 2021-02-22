/*
 * ADC.c
 * Author: Luca Piccinini
 * Descripción: Libreria para la lectura de puertos ADC del atemega 328p
 */ 

//#define F_CPU  16000000U
#include <avr/io.h>
#include "util/delay.h"
#include "ADC.h"

void ADC_init()
{
	// Ajustamos los 10bits a la drecha
	ADMUX &=~ (1<<ADLAR);
	
	// Voltaje de referecia en AVCC en nuestro caso 5V
	ADMUX |= (1<<REFS0);
	ADMUX &=~(1<<REFS1);
	
	// Configuramos el divisor de frecuencia en 128 ya que el ADC trabaja para frecuencias menores a 200kHz
	ADCSRA |= (1<<ADPS0);
	ADCSRA |= (1<<ADPS1);
	ADCSRA |= (1<<ADPS2);
}

int ADC_read(int num_port)
{
	// Seleccionamos el puerto del ADC
	ADMUX &=~ 0x0F;
	ADMUX |= num_port;
	
	// Enecendemos el ADC y esperamos un tiempo para que caliente
	ADCSRA |= (1<<ADEN);
	_delay_us(10);
	
	// Muestreamos
	ADCSRA |= (1<<ADSC);
	
	// Esperamos a que termine el muestreo viendo la bandera que marca esto
	while( !(ADCSRA & (1<<ADIF)) );
	ADCSRA |= (1<<ADEN);
	
	// Apagamos el ADC
	ADCSRA &=~ (1<<ADEN);
	
	return ADC;
}
