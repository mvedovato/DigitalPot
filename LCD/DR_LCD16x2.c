/*
 * DR_LCD16x2.c
 *
 *  Created on: 7/9/2021
 *      Author: mariano
 */

#include "DR_LCD16x2.h"
#include "gpio.h"


void LCD_Escribir(uint8_t data , uint8_t control)
{
	int32_t q , i = 1;

	do
	{
		SetPIN(PIN_LCD16X2_D7, ( data >> ( 3 + i * 4 ) ) & 0x01);
		SetPIN(PIN_LCD16X2_D6, ( data >> ( 2 + i * 4 ) ) & 0x01) ;
		SetPIN(PIN_LCD16X2_D5, ( data >> ( 1 + i * 4 ) ) & 0x01) ;
		SetPIN(PIN_LCD16X2_D4, ( data >> ( 0 + i * 4 ) ) & 0x01) ;

		if( control )
			SetPIN(PIN_LCD16X2_RS, 0);
		else
			SetPIN(PIN_LCD16X2_RS, 1);

		SetPIN(PIN_LCD16X2_E, 1);

		for( q = 0 ; q < 400 ; q++ );

		SetPIN(PIN_LCD16X2_E, 0);

		for( q = 0 ; q < 14000 ; q++ );
	}
	while ( i-- );
}

void Display_LCD( uint8_t *msg , uint8_t r , uint8_t p )
{
	unsigned char i ;

	if( r )
        p = p + 0xc0 ;
	else
		p = p + 0x80 ;

	LCD_Escribir( p , LCD16x2_CONTROL );
	for( i = 0 ; msg[ i ] != '\0' ; i++ )
		LCD_Escribir( msg[ i ] , LCD16x2_DATA );
}


void Inicializar_LCD( void )
{
	uint32_t i, j;

	SetDIR( PIN_LCD16X2_E  , SALIDA );
	SetDIR( PIN_LCD16X2_RW  , SALIDA );
	SetDIR( PIN_LCD16X2_RS  , SALIDA );
	SetDIR( PIN_LCD16X2_D7  , SALIDA );
	SetDIR( PIN_LCD16X2_D6  , SALIDA );
	SetDIR( PIN_LCD16X2_D5  , SALIDA );
	SetDIR( PIN_LCD16X2_D4  , SALIDA );

	SetPIN( PIN_LCD16X2_E , OFF );
	SetPIN( PIN_LCD16X2_RW , OFF );
	SetPIN( PIN_LCD16X2_RS , OFF );
	SetPIN( PIN_LCD16X2_D7 , OFF );
	SetPIN( PIN_LCD16X2_D6 , OFF );
	SetPIN( PIN_LCD16X2_D5 , OFF );
	SetPIN( PIN_LCD16X2_D4 , OFF );


	for( i = 0 ; i < 3 ; i++ )
	{
		SetPIN(PIN_LCD16X2_E, 0);
		LCD_Delay( );
		SetPIN(PIN_LCD16X2_D7, 0);
		SetPIN(PIN_LCD16X2_D6, 0) ;
		SetPIN(PIN_LCD16X2_D5, 1) ;
		SetPIN(PIN_LCD16X2_D4, 1) ;

		SetPIN(PIN_LCD16X2_RS, 0);
		SetPIN(PIN_LCD16X2_E, 1);
		for( j = 0 ; j < 10000 ; j++ );//4500
		SetPIN(PIN_LCD16X2_E, 0);
	}

	SetPIN(PIN_LCD16X2_E, 0);
	LCD_Delay( );

	SetPIN(PIN_LCD16X2_D7, 0);
	SetPIN(PIN_LCD16X2_D6, 0) ;
	SetPIN(PIN_LCD16X2_D5, 1) ;
	SetPIN(PIN_LCD16X2_D4, 0) ;

	SetPIN(PIN_LCD16X2_RS, 0);
	SetPIN(PIN_LCD16X2_E, 1);
	for( j = 0 ; j < 10000 ; j++ );//4500
	SetPIN(PIN_LCD16X2_E, 0);

	// A partir de aca pasa a 4 bits
	LCD_Escribir( 0x28 , LCD16x2_CONTROL);
	LCD_Escribir( 0x08 , LCD16x2_CONTROL);	// display OFF
	LCD_Escribir( 0x01 , LCD16x2_CONTROL);	// clear display
	LCD_Escribir( 0x06 , LCD16x2_CONTROL);	// programo el LCD para mis necesidades
	LCD_Escribir( 0x0C , LCD16x2_CONTROL);	// display ON,sin cursor y blinking OFF del cursor
}

void LCD_Delay( void )
{
  uint32_t 	i;

  for ( i = 0 ; i < 500000 ; i++ ); // 300000
}







