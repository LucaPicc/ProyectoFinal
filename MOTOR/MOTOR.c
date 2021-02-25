/*
 * MOTOR.c
 * Autor: Luca Piccinini
 * Descripción: Libreria para el control de motores de corriente continua
*/
#include "MOTOR.h"

/* Configuración inicial del PWM necesario para el control de los motores */
void MOTORES_init(int freq, int duty)
{
    /*  Configuramos el Timer 1 para que funcione en Fast PWM sin señal de  
     * reloj habilitando PB1 y PB2 como salidas PWM
    */
    TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM11);
    TCCR1B = (1<<WGM12) | (1<<WGM13);

    /* Configuración pines de salida */
    /*
     * Los pines que necesitamos configurar como salida son el PB1 asociado
     * a OC1A y PB2 asociado a OC1B. De estos pines saldran los PWM corres-
     * pondientes a los generados por el Timer 1
    */
    DDRB |= (1<<DDB1); 
    DDRB |= (1<<DDB2);

    /* Configuramos la frecuencia y el ancho de pulso iniciales */
    ICR1 = (F_CPU/1024/freq) -1;
    OCR1A = (((F_CPU/1024/freq) -1)*duty)/100;
    OCR1B = (((F_CPU/1024/freq) -1)*duty)/100;
}


/* Control cojunto de motores */
int MOTORES_cont(int state, int freq, int duty)
{
    /*  Esta función sera la encarga de hacer control conjunto de ambos
     * motores lo que implica encenderlos apagarlos y modificar el ancho
     * de pulso para lograr variar la velocidad en forma conjunta
    */

    /*  Los estados que puede recibir son:
     *      1 = Apagar motores
     *      2 = Encender motores
     *      3 = Modificar ancho de pulso
    */ 
    if (state == 1)
    {
        /*  El metodo que usamos para apagar ambos motores es 
         * desactivando la entrada de clock
        */
        
        TCCR1B &=~ (1<<CS10);
        TCCR1B &=~ (1<<CS11);
        TCCR1B &=~ (1<<CS12);
        return 1;
    }
    else
    {
        if(state == 2)
        {
            /* Incializamos el registro de conteo en cero */
            TCNT1 = 0x0000;

            /* Configuramos la entrada de clock con un prescaler de 1024 */
            TCCR1B |=  (1<<CS10);
            TCCR1B &=~ (1<<CS11);
            TCCR1B |=  (1<<CS12);
            return 2;
        }
        else
        {
            OCR1A = (((F_CPU/1024/freq) -1)*duty)/100;
            OCR1B = (((F_CPU/1024/freq) -1)*duty)/100;
            return 3;
        }
    }
    /*  Los estados que devolvera seran:
     *      1 = Motores apagados
     *      2 = Motores encendidos
     *      3 = Ancho de pulso modificado
    */
}

/* Control de motor derecho */
int MOTOR_right_cont(int state, int duty, int freq)
{
    /* Esta función es para controlar la velocidad, por medio del ancho del
     *pulso del PWM, apagar y encender el motor
     */
    /* Las opciones que acepta seran:
     *  1 = Apaga los motor
     *  2 = Enciende el motor
     *  * = Modificamos el ancho de pulso, tenemos que tener cuidado en
     *      conservar el mismo valor de frecuencia para que la asignación del
     *      ancho de pulso funcione de manera correcta
    */
    if (state == 1)
    {
        DDRB &=~ (1<<DDB1);
        return 1;
    }
    else
    {
        if(state == 2)
        {
            DDRB |= (1<<DDB1);
            return 2;
        }
        else
        {
            OCR1A = (((F_CPU/1024/freq) -1)*duty)/100;
            return 3;
        }
    }
    /*  El valor que devuelve esta función es para que a la hora de hacer el
     * control del robot tengamos en cuenta que se hizo con el motor ante-
     * riormente y el estado de este. Los estados posibles seran, según el 
     * valor retornado por la función:
     *  1 = Motor apagado
     *  2 = Motor encendido
     *  3 = Motor con ancho de pulso modificado
    */
}

/* Control de motor izquierdo */
int MOTOR_left_cont(int state, int duty, int freq)
{
    /*  Esta función es para controlar la velocidad, por medio del ancho del
     * pulso del PWM, apagar y encender el motor
     */
    /* Las opciones que acepta seran:
     *  1 = Apaga los motor
     *  2 = Enciende el motor
     *  3 = Modificamos el ancho de pulso, tenemos que tener cuidado en
     *      conservar el mismo valor de frecuencia para que la asignación del
     *      ancho de pulso funcione de manera correcta
    */
    if (state == 1)
    {
        DDRB &=~ (1<<DDB1);
        return 1;
    }
    else
    {
        if(state == 2)
        {
            DDRB |= (1<<DDB1);
            return 2;
        }
        else
        {
            OCR1A = (((F_CPU/1024/freq) -1)*duty)/100;
            return 3;
        }
    }
    /*  El valor que devuelve esta función es para que a la hora de hacer el
     * control del robot tengamos en cuenta que se hizo con el motor ante-
     * riormente y el estado de este. Los estados posibles seran, según el 
     * valor retornado por la función:
     *  1 = Motor apagado
     *  2 = Motor encendido
     *  3 = Motor con ancho de pulso modificado
    */
}