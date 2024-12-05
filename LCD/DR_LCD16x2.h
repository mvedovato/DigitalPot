/*
 * DR_LCD16x2.h
 *
 *  Created on: 7/9/2021
 *      Author: mariano
 */

#ifndef SOURCES_DRIVERS_TK_H_DR_LCD16X2_H_
#define SOURCES_DRIVERS_TK_H_DR_LCD16X2_H_

#include 	<stdint.h>
#define 	LCD16x2_CONTROL		1
#define 	LCD16x2_DATA		0

#define 	ON					1
#define 	OFF					0

#define		PIN_LCD16X2_RS		PORTH,1		//OK
#define		PIN_LCD16X2_RW		PORTH,0		//OK
#define		PIN_LCD16X2_E		PORTE,6		//OK
#define		PIN_LCD16X2_D7		PORTD,5		//OK
#define		PIN_LCD16X2_D6		PORTD,6		//OK
#define		PIN_LCD16X2_D5		PORTD,7		//OK
#define		PIN_LCD16X2_D4		PORTC,2		//OK
#define		PIN_LCD16X2_D3		PORTC,3		//OK
#define		PIN_LCD16X2_D2		PORTB,4		//OK
#define		PIN_LCD16X2_D1		PORTB,5		//OK
#define		PIN_LCD16X2_D0		PORTE,5		//OK

void LCD_Escribir(uint8_t , uint8_t );
void Display_LCD( uint8_t * , uint8_t  , uint8_t  );
void Inicializar_LCD( void );
void LCD_Delay( void );



#endif /* SOURCES_DRIVERS_TK_H_DR_LCD16X2_H_ */
