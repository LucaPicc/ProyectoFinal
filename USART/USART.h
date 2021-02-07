/*
 * USART.h
 *
 * Created: 22/12/2020 21:00:17
 *  Author: Luca
 */ 


#ifndef USART_H_
#define USART_H_

	#include <avr/io.h>
	//#define F_CPU 16000000U
	#define BAUDRATE 9600
	#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)
	//Declaraci�n de funciones
	void USART_init(void);
	unsigned char USART_receive(void);
	void USART_send( unsigned char data);
	void USART_putstring(char* StringPtr);


#endif /* USART_H_ */