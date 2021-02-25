/*
 * US.c
 * Autor: Luca Piccinini
 * Descripción: Libreria dedicada a la utilización del sensor HCSR04 con un
 * atmenga328p
*/

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include "SU.h"

extern char interrupcion;
static volatile uint32_t med_seg = 0;

void SU_init(void)
{
    /* Primero generaremos un PWM que pueda funcionar como señal de Trigger
     * para esto usaremos el timer 0 en modo fast PWM con un prescaler de 8
     * y un ancho de pulso de 10us y la duración del periodo . Para esto
     * configuraremos para que el conteo llegue al valor maximo es decir 0xFF
     * y que en alto cuente hasta el 20 = 255(0xFF) - 235
    */
    TCCR0A = (1<<COM0A1) |(1<<COM0A0) | (1<<WGM01) | (1<<WGM00);
    TCCR0B |= (1<<CS01);
    OCR0A = 235;
    DDRD |= (1<<DDD6);

    /*  Configuramos inicialmente el timer 2 para poderlo inciarlizar
     * rapidamente y dejamos configurada la interrupción INT0 para detectar
     * un flanco de subida
    */
    
    DDRD &=~ (1<<DDD2);
    PORTD |= (1<<PORTD2);
    EICRA = (1<<ISC01) | (1<<ISC00);
    EIMSK |= (1<<INT0);

    //TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS20); 

}

uint32_t getDistance(void)
{
    static uint32_t echo_us = 0;
    static uint32_t med_cm = 0;
    echo_us = med_seg * 16320 / 255;
    med_cm = (float)echo_us /58;
    return med_cm;
}


ISR(INT0_vect)
{
    if (interrupcion == 0)
    {
        interrupcion = 1;
        TCNT2 = 0x00;
        TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS20);

        //TCCR2B |= (1<<CS20)
        EICRA &=~ (1<<ISC00);
    }
    else
    {
        med_seg = TCNT2;

        TCCR2B &=~ (1<<CS20);
        TCCR2B &=~ (1<<CS21);
        TCCR2B &=~ (1<<CS22);

        EICRA |= (1<<ISC00);
        interrupcion = 0;
    }
    
}

ISR(TIMER2_OVF_vect)
{
    med_seg = 255;
    TCCR2B &=~ (1<<CS20);
    TCCR2B &=~ (1<<CS21);
    TCCR2B &=~ (1<<CS22);

    EICRA &=~ (1<<ISC00);
    interrupcion = 0;
}