/*
 * PWM.c
 * Author: Luca Piccinini
 * Descripción: Libreria para la generación de pulsos PWM en atemega328p(Reemplazada por MOTOR)
 */ 

#include "PWM.h"
//#define F_CPU 16000000U

void PWM_init(int frec, int duty)
{
	//habilitamos modo fast PWM con TOP 0xFF y en modo no invertido
	TCCR0A = 0b10100011;
	TCCR0B = 0b00000101;
	
	
	OCR0A = ((F_CPU/1024/frec)-1)*duty/100;
	OCR0B = ((F_CPU/1024/frec)-1)*duty/100;
}

// Encendido de los PWM
void PWM_on()
{
	TCNT0 = 0x00;
	//Habilitamos los puertos del PWM en salida
	DDRD |= (1<<DDD5);
	DDRD |= (1<<DDD6);
}

// Apagado de los PWM
void PWM_off()
{
	DDRD &=~ (1<<DDD5);
	DDRD &=~ (1<<DDD6);
}

// Apagados individuales
void PWM_off_5()
{
    DDRD &=~ (1<<DDD5);
}

void PWM_off_6()
{
    DDRD &=~ (1<<DDD6);
}
