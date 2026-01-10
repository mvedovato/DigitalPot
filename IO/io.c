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
#include "x9c10xs.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
#define 	CANTeNTRADAS	4
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
uint32_t Outputs = 0;
uint32_t MascaraOutputs = 0xffffffff;
uint8_t fTimeoutVolume = 0;
uint8_t fTimeoutDrive = 0;



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

	if( GetPIN( IN3 , BAJO ) )
		lectura |= 0x02;

	if( GetPIN( IN4 , BAJO ) )
		lectura |= 0x04;

	if( GetPIN( IN5 , BAJO ) )
		lectura |= 0x08;

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


	// Salidas Digitales ---------------------------------------------------------

}




uint8_t GetFvolume( void ){
	return fTimeoutVolume;
}
void SetFvolume( uint8_t value ){
	fTimeoutVolume = value;
}
uint8_t GetFdrive( void ){
	return fTimeoutDrive;
}
void SetFdrive( uint8_t value ){
	fTimeoutDrive = value;
}

void timeoutVolume(void){
	x9c103s_Init( );
	fTimeoutVolume = 1;

}

void timeoutDrive(void){
	x9c104s_Drive_Init( );
	fTimeoutDrive = 1;
}

void timeoutTone(void){
	x9c104s_Tone_Init( );
}

void Control_DigPot_Volume(uint8_t value){
	switch( value ){
	case 0:
		SetPIN( VOLUME_CONTROL_1B  , OFF );
		SetPIN( VOLUME_CONTROL_1C  , OFF );
		SetPIN( VOLUME_CONTROL_1D  , OFF );
		SetPIN( VOLUME_CONTROL_2A  , OFF );
		SetPIN( VOLUME_CONTROL_2B  , OFF );
		SetPIN( VOLUME_CONTROL_2C  , OFF );
		SetPIN( VOLUME_CONTROL_2D  , OFF );
		SetPIN( VOLUME_CONTROL_1A  , ON );
		break;
	case 1:
		SetPIN( VOLUME_CONTROL_1A  , OFF );
		SetPIN( VOLUME_CONTROL_1C  , OFF );
		SetPIN( VOLUME_CONTROL_1D  , OFF );
		SetPIN( VOLUME_CONTROL_2A  , OFF );
		SetPIN( VOLUME_CONTROL_2B  , OFF );
		SetPIN( VOLUME_CONTROL_2C  , OFF );
		SetPIN( VOLUME_CONTROL_2D  , OFF );
		SetPIN( VOLUME_CONTROL_1B  , ON );
		break;
	case 2:
		SetPIN( VOLUME_CONTROL_1A  , OFF );
		SetPIN( VOLUME_CONTROL_1B  , OFF );
		SetPIN( VOLUME_CONTROL_1D  , OFF );
		SetPIN( VOLUME_CONTROL_2A  , OFF );
		SetPIN( VOLUME_CONTROL_2B  , OFF );
		SetPIN( VOLUME_CONTROL_2C  , OFF );
		SetPIN( VOLUME_CONTROL_2D  , OFF );
		SetPIN( VOLUME_CONTROL_1C  , ON );
		break;
	case 3:
		SetPIN( VOLUME_CONTROL_1A  , OFF );
		SetPIN( VOLUME_CONTROL_1B  , OFF );
		SetPIN( VOLUME_CONTROL_1C  , OFF );
		SetPIN( VOLUME_CONTROL_2A  , OFF );
		SetPIN( VOLUME_CONTROL_2B  , OFF );
		SetPIN( VOLUME_CONTROL_2C  , OFF );
		SetPIN( VOLUME_CONTROL_2D  , OFF );
		SetPIN( VOLUME_CONTROL_1D  , ON );
		break;
	case 4:
		SetPIN( VOLUME_CONTROL_1A  , OFF );
		SetPIN( VOLUME_CONTROL_1B  , OFF );
		SetPIN( VOLUME_CONTROL_1C  , OFF );
		SetPIN( VOLUME_CONTROL_1D  , OFF );
		SetPIN( VOLUME_CONTROL_2B  , OFF );
		SetPIN( VOLUME_CONTROL_2C  , OFF );
		SetPIN( VOLUME_CONTROL_2D  , OFF );
		SetPIN( VOLUME_CONTROL_2A  , ON );
		break;
	case 5:
		SetPIN( VOLUME_CONTROL_1A  , OFF );
		SetPIN( VOLUME_CONTROL_1B  , OFF );
		SetPIN( VOLUME_CONTROL_1C  , OFF );
		SetPIN( VOLUME_CONTROL_1D  , OFF );
		SetPIN( VOLUME_CONTROL_2A  , OFF );
		SetPIN( VOLUME_CONTROL_2C  , OFF );
		SetPIN( VOLUME_CONTROL_2D  , OFF );
		SetPIN( VOLUME_CONTROL_2B  , ON );
		break;
	case 6:
		SetPIN( VOLUME_CONTROL_1A  , OFF );
		SetPIN( VOLUME_CONTROL_1B  , OFF );
		SetPIN( VOLUME_CONTROL_1C  , OFF );
		SetPIN( VOLUME_CONTROL_1D  , OFF );
		SetPIN( VOLUME_CONTROL_2A  , OFF );
		SetPIN( VOLUME_CONTROL_2B  , OFF );
		SetPIN( VOLUME_CONTROL_2D  , OFF );
		SetPIN( VOLUME_CONTROL_2C  , ON );
		break;
	case 7:
		SetPIN( VOLUME_CONTROL_1A  , OFF );
		SetPIN( VOLUME_CONTROL_1B  , OFF );
		SetPIN( VOLUME_CONTROL_1C  , OFF );
		SetPIN( VOLUME_CONTROL_1D  , OFF );
		SetPIN( VOLUME_CONTROL_2A  , OFF );
		SetPIN( VOLUME_CONTROL_2B  , OFF );
		SetPIN( VOLUME_CONTROL_2C  , OFF );
		SetPIN( VOLUME_CONTROL_2D  , ON );
		break;
	default:
		SetPIN( VOLUME_CONTROL_1A  , OFF );
		SetPIN( VOLUME_CONTROL_1B  , OFF );
		SetPIN( VOLUME_CONTROL_1C  , OFF );
		SetPIN( VOLUME_CONTROL_1D  , OFF );
		SetPIN( VOLUME_CONTROL_2A  , OFF );
		SetPIN( VOLUME_CONTROL_2B  , OFF );
		SetPIN( VOLUME_CONTROL_2C  , OFF );
		SetPIN( VOLUME_CONTROL_2D  , OFF );
		break;
	}
}
void Control_DigPot_Drive(uint8_t value){
	switch( value ){
	case 0:
		SetPIN( DRIVE_CONTROL_D  , OFF );
		SetPIN( DRIVE_CONTROL_B  , OFF );
		SetPIN( DRIVE_CONTROL_C  , OFF );
		SetPIN( DRIVE_CONTROL_A  , ON );
		break;
	case 1:
		SetPIN( DRIVE_CONTROL_A  , OFF );
		SetPIN( DRIVE_CONTROL_D  , OFF );
		SetPIN( DRIVE_CONTROL_C  , OFF );
		SetPIN( DRIVE_CONTROL_B  , ON );
		break;
	case 2:
		SetPIN( DRIVE_CONTROL_A  , OFF );
		SetPIN( DRIVE_CONTROL_B  , OFF );
		SetPIN( DRIVE_CONTROL_D  , OFF );
		SetPIN( DRIVE_CONTROL_C  , ON );
		break;
	case 3:
		SetPIN( DRIVE_CONTROL_A  , OFF );
		SetPIN( DRIVE_CONTROL_B  , OFF );
		SetPIN( DRIVE_CONTROL_C  , OFF );
		SetPIN( DRIVE_CONTROL_D  , ON );
		break;
	default:
		SetPIN( DRIVE_CONTROL_D  , OFF );
		SetPIN( DRIVE_CONTROL_B  , OFF );
		SetPIN( DRIVE_CONTROL_C  , OFF );
		SetPIN( DRIVE_CONTROL_A  , OFF );
		break;
	}
}
