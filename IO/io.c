/*******************************************************************************************************************************//**
 * @details		Proyecto: TK18101-Empanadas
 * @file		DR_Entradas.c
 * @brief		DESCRIPCION ---------------
 * @date		24/4/2017
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <io.h>
#include <uart.h>
#include "gpio.h"

#include "init.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
#define 	CANTsALIDAS		3
#define 	CANTeNTRADAS	1
#define 	ACEPTAReSTADO	10

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
volatile uint16_t BufferEntradas = REPOSO;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
static uint8_t ContadorEstados[ CANTeNTRADAS ];
uint32_t Outputs = 3;		//Arrancan heat y fan en OFF logica negativa
uint32_t MascaraOutputs = 0xffffffff;
uint32_t BufferLeds = 0;

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/
/**
	@fn  		void Debounce ( void )
	@brief 		elimina rebote de las entradas digitales
 	@author 	Ing. Marcelo Trujillo
 	@date 		25/04/17
 	@param void
	@return void
*/
void Debounce ( void )
{
	uint16_t lectura = 0, j ;
	uint16_t cambios;

	if( GetPIN( IN2 , BAJO ) )
		lectura =  0x01;

	cambios = ( BufferEntradas ^ lectura );

	if( cambios )
	{
		for( j = 0 ; j < CANTeNTRADAS ; j++ )
		{
			if( cambios & ( 0x01 << j ) )
			{
				ContadorEstados[ j ] ++;

				if( ContadorEstados[ j ] == ACEPTAReSTADO )
				{
					ContadorEstados[ j ] = 0;
					BufferEntradas = BufferEntradas ^ ( 0x01 << j );
				}
			}
			else
				ContadorEstados[ j ] = 0;
		}
	}
	else
	{
		for(j = 0 ; j < CANTeNTRADAS ; j++)
			ContadorEstados[ j ] = 0;
	}
}

uint16_t get_Entradas( void )
{
	return BufferEntradas;
}


/**
	@fn  		void InicializarIO ( void )
	@brief 		Inicializa las entradas salidas digitales
 	@author 	Ing. Marcelo Trujillo
 	@date 		19-06-16
 	@return 	void
*/
void RefrescoOut ( void )
{
	uint8_t i;
	// Salidas Digitales ---------------------------------------------------------
	for(i=0; i < CANTsALIDAS; i++)
		SetOuts(i, (Outputs>>i)&0x01);
	//Leds
	for(i=0; i < 9; i++)
		SetLeds(i, (BufferLeds>>i)&0x01);
}




void SetLeds( uint8_t nroLed, uint8_t actividad )
{
	switch(nroLed)
	{
	case 0:
		if( actividad )
			SetPIN(led1, ON);
		else
			SetPIN(led1, OFF);
		break;

	case 1:
		if( actividad )
			SetPIN(led2, ON);
		else
			SetPIN(led2, OFF);
		break;

	case 2:
		if( actividad )
			SetPIN(led3, ON);
		else
			SetPIN(led3, OFF);
		break;

	case 3:
		if( actividad )
			SetPIN(led4, ON);
		else
			SetPIN(led4, OFF);
		break;

	case 4:
		if( actividad )
			SetPIN(led5, ON);
		else
			SetPIN(led5, OFF);
		break;

	case 5:
		if( actividad )
			SetPIN(led6, ON);
		else
			SetPIN(led6, OFF);
		break;

	case 6:
		if( actividad )
			SetPIN(led7, ON);
		else
			SetPIN(led7, OFF);
		break;

	case 7:
		if( actividad )
			SetPIN(led8, ON);
		else
			SetPIN(led8, OFF);
		break;

	case 8:
		if( actividad )
			SetPIN(led9, ON);
		else
			SetPIN(led9, OFF);
		break;

default:
	break;
	}
}

void LedsOff( void )
{
	LED0oFF;
	LED1oFF;
	LED2oFF;
	LED3oFF;
	LED4oFF;
	LED5oFF;
	LED6oFF;
	LED7oFF;
	LED8oFF;


}

void LedsOn( void )
{
	LED0oN;
	LED1oN;
	LED2oN;
	LED3oN;
	LED4oN;
	LED5oN;
	LED6oN;
	LED7oN;
	LED8oN;

}
void SetOuts( uint8_t nroOut, uint8_t actividad )
{
	switch(nroOut)
	{
	case 0:
		if( actividad )
			SetPIN( heat, OFFcUKI );
		else
			SetPIN( heat, ONcUKI );
		break;

	case 1:
		if( actividad )
			SetPIN( fan, OFFcUKI );
		else
			SetPIN( fan, ONcUKI );
		break;

	case 2:
		if( actividad )
			SetPIN( buzzer, ON );
		else
			SetPIN( buzzer, OFF );
		break;
	default:
		break;

	}

}

void HeatOn( void )
{
	HEAToN;
}
void HeatOff( void )
{
	HEAToFF;
}
void FanOn( void )
{
	FANoN;
}
void FanOff( void )
{
	FANoFF;
}
void BuzzerOn( void )
{
	BUZZERoN;
}
void BuzzerOff( void )
{
	BUZZERoFF;
}
void LedCicloOn( void )
{
	LED3oN;
}
void LedCicloOff( void )
{
	LED3oFF;
}


