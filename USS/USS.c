/*
 * USS.c
 * Autor: Luca Piccinini
 * Descripción: Libreria dedicada a la utilización de un un sensor HCSR04 con un atmega328p
*/

#ifndef F_CPU
#define F_CPU 16000000
#endif //F_CPU

#include <avr/io.h>
#include <avr/interrupt.h>
#include "USS.h"

static volatile uint32_t first_reading = 0;
static volatile uint32_t second_reading = 0;
static volatile uint32_t duty_cycle = 0;

void Ultrasonico_init(){
	
    /*Configuramos el modo Fast PWM*/
	
    DDRD |= (1<<DDD6); 											//PD6 como salida
	TCCR0A = (1<<COM0A1)|(1<<COM0A0)|(1<<WGM01)|(1<<WGM00);
	TCCR0B |= (1<<CS01); 										//prescaler = 8 
	OCR0A = 235; 												//10uS trigger, 118uS tiempo en bajo (128uS de periodo)
	
    /*Configuración de captura de entrada*/
	
    //Timer 1 en normal mode
	
    DDRB &= ~(1<<DDB0); 										//PB0 como entrada (ICP1)(echo)
	TCCR1B = (1<<ICNC1)|(1<<ICES1)|(1<<CS11); 					//activamos cancelación de ruido y ponemos configuramos para que se detecte el flanco de subida Prescaler = 8.
	TIMSK1 |= (1<<ICIE1); 										//habilitamos la captura de la interrución del timer1 
}

uint32_t getDistance(){
	static uint32_t echo_pulse_uS;
	static uint32_t distance_cm;
        //32768uS = 65536 clock ticks para el Timer 1 con prescaler = 8
	echo_pulse_uS = (float)duty_cycle * 32768 / 65536;
	distance_cm = echo_pulse_uS * 0.034 / 2;
	return distance_cm;
}

ISR(TIMER1_CAPT_vect){
	if ((TCCR1B & (1<<ICES1)) == (1<<ICES1)){
		first_reading = ICR1;
	}
	else{
		second_reading = ICR1;
	}
	
	if (first_reading != 0 && second_reading != 0){
		duty_cycle = second_reading - first_reading;
		first_reading = 0;
		second_reading = 0;
	}
	
	TCCR1B ^= (1<<ICES1); 										//detección de flanco de bajada
	TIFR1 = (1<<ICF1);											//Limpiamos bandera de captura
}