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
//#include "SU/SU.h"
#include <stdlib.h>

char String[10] = "HOla";
char interrupcion = 0;
uint32_t distance;


int main(){
	
	USART_init();
	DDRB |= (1<<DDB5);
	PORTB |= (1<<PORTB5);

	/* En este main se correran dos programas principales a modo de prueba
	 * como ya se menciono en el informe no pudimos lograr hacer funcionar
	 * las libreria de los motores y del sensor HC-SR04 debido a que debemos
	 * mejorar esta ultima para que no utilice el timer 1 del micro
	*/

	/* Conexionado para las pruebas */
	/* En el caso de los sensores las alimentaciones se obtiene directamente
	 * de los pines de 5V y GND del arduino.
	 * 
	 * Sensores infrarrojos:
	 * 	Se uso el circuito de prueba expuesto en su hoja de datos y luego se
	 * 	uso el pin A0 y A2 para la lectura de la tensión de los sensores 
	 * 	entre el emisor y tierra.
	 * 
	 * HC-SR04:
	 * 	Para el triger tenemos que conectarlo al pin 6 (PD6) del arduino y
	 *  el echo en el pin 8(PB0)
	 * 
	 * Motores:
	 * 	La alimentación no se puede obtener desde el arduino por lo que usa-
	 * 	mos una fuente externa, asi sera necesario un transistor de usos
	 * 	generales, usamos el C337, donde el motor tendra uno de sus pines a 
	 *  la tensión de +5V y el otro al colector. Luego ponemos el emisor a 
	 * 	tierra de la fuente y tambien al del arduino. Por ultimo conectamos 
	 * 	el pin 9 (PB1) para uno de los motores y el pin 10(PB2) a la base 
	 * 	por medio de una resistencia de 220
	*/

	/* Inicialización de Motores y ADC */
	
	/**/
/*
	cli();
	

	ADC_init();
	MOTORES_init(100,100);
	MOTORES_cont(2,100,100);
	
	sei();
	

	while (1)
	{
/*
		int sensor_1 = ADC_read(0);
		dtostrf(sensor_1,10,0,String);
		USART_putstring(String);
		
		int sensor_2 = ADC_read(2);
		dtostrf(sensor_2,10,0,String);
		USART_putstring(String);

		if(sensor_1 > 300 && sensor_2 > 300 )
		{
			MOTORES_cont(2,100,100);
		}
		else
		{
			if (sensor_1 < 300 && sensor_2 > 300)
			{
				MOTOR_right_cont(1,50,100);
				MOTOR_left_cont(3,100,100);
			}
			else
			{
				if (sensor_1 > 300 && sensor_2 < 300)
				{
					MOTOR_right_cont(3,100,100);
					MOTOR_left_cont(1,50,100);
				}
				else
				{
					MOTORES_cont(1,100,100);
				}
				
			}
		
		}
*/
/*
		MOTOR_right_cont(2,100,100);
		_delay_us(1000000);
		MOTOR_right_cont(1,100,100);
		_delay_us(1000000);

	}
*/
/*
		if (sensor_1 < 300)
		{
			MOTOR_right_cont(2,100,100);
		}
		else
		{
			MOTOR_right_cont(1,100,100);
		}
	}
		
*/
	/**/
	
	/* Programa de prueba sensor ultrasonico */
	/* Como se puede ver se tiene una librería USS y SU las dos estan desti-
	 * nadas al manejo del sensor HC-SR04 pero la unica funcional hasta el 
	 * momento es la USS la cual entra en conflicto con la libreria de MOTOR
	 * En esta prueba la usaremos para prender y apagar el led del kit segun
	 * una cota de distancia  
	*/
	

	cli();
	
	Ultrasonico_init();

	sei();
	

	while (1){
		uint32_t d_cm = 0;
		d_cm = getDistance();


		if (d_cm < 4)
		{
			PORTB |= (1<<PORTB5);
		}
		else
		{
			PORTB &=~ (1<<PORTB5);
		}

		dtostrf(d_cm,10,0,String);
		USART_putstring(String);
	}


	return 0;
}