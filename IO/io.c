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


void TogglearSalidas( uint8_t salida )
{
	switch( salida )
	{
	case 0:
		if( (Outputs >> 0) & 0x01 )
			OUT0oFF;
		else
			OUT0oN;
		break;
	case 1:
		if( (Outputs >> 1) & 0x01 )
			OUT1oFF;
		else
			OUT1oN;
		break;
	case 2:
		if( (Outputs >> 2) & 0x01 )
			OUT2oFF;
		else
			OUT2oN;
		break;
	case 3:
		if( (Outputs >> 3) & 0x01 )
			OUT3oFF;
		else
			OUT3oN;
		break;
	case 4:
		if( (Outputs >> 4) & 0x01 )
			OUT4oFF;
		else
			OUT4oN;
		break;
	case 5:
		if( (Outputs >> 5) & 0x01 )
			OUT5oFF;
		else
			OUT5oN;
		break;
	case 6:
		if( (Outputs >> 6) & 0x01 )
			OUT6oFF;
		else
			OUT6oN;
		break;
	case 7:
		if( (Outputs >> 7) & 0x01 )
			OUT7oFF;
		else
			OUT7oN;
		break;
	case 8:
		if( (Outputs >> 8) & 0x01 )
			OUT8oFF;
		else
			OUT8oN;
		break;
	case 9:
		if( (Outputs >> 9) & 0x01 )
			OUT9oFF;
		else
			OUT9oN;
		break;
	case 10:
		if( (Outputs >> 10) & 0x01 )
			OUT10oFF;
		else
			OUT10oN;
		break;
	case 11:
		if( (Outputs >> 11) & 0x01 )
			OUT11oFF;
		else
			OUT11oN;
		break;
	case 12:
		if( (Outputs >> 12) & 0x01 )
			OUT12oFF;
		else
			OUT12oN;
		break;
	case 13:
		if( (Outputs >> 13) & 0x01 )
			OUT13oFF;
		else
			OUT13oN;
		break;
	case 14:
		if( (Outputs >> 14) & 0x01 )
			OUT14oFF;
		else
			OUT14oN;
		break;
	case 15:
		if( (Outputs >> 15) & 0x01 )
			OUT15oFF;
		else
			OUT15oN;
		break;
	case 16:
		if( (Outputs >> 16) & 0x01 )
			OUT16oFF;
		else
			OUT16oN;
		break;
	case 17:
		if( (Outputs >> 17) & 0x01 )
			OUT17oFF;
		else
			OUT17oN;
		break;
	case 18:
		if( (Outputs >> 18) & 0x01 )
			OUT18oFF;
		else
			OUT18oN;
		break;
	case 19:
		if( (Outputs >> 19) & 0x01 )
			OUT19oFF;
		else
			OUT19oN;
		break;
	case 20:
		if( (Outputs >> 20) & 0x01 )
			OUT20oFF;
		else
			OUT20oN;
		break;
	case 21:
		if( (Outputs >> 21) & 0x01 )
			OUT21oFF;
		else
			OUT21oN;
		break;
	case 22:
		if( (Outputs >> 22) & 0x01 )
			OUT22oFF;
		else
			OUT22oN;
		break;
	case 23:
		if( (Outputs >> 23) & 0x01 )
			OUT23oFF;
		else
			OUT23oN;
		break;
	case 24:
		if( (Outputs >> 24) & 0x01 )
			OUT24oFF;
		else
			OUT24oN;
		break;
	case 25:
		if( (Outputs >> 25) & 0x01 )
			OUT25oFF;
		else
			OUT25oN;
		break;
	case 26:
		if( (Outputs >> 26) & 0x01 )
			OUT26oFF;
		else
			OUT26oN;
		break;
	case 27:
		if( (Outputs >> 27) & 0x01 )
			OUT27oFF;
		else
			OUT27oN;
		break;
	case 28:
		if( (Outputs >> 28) & 0x01 )
			OUT28oFF;
		else
			OUT28oN;
		break;
	case 29:
		if( (Outputs >> 29) & 0x01 )
			OUT29oFF;
		else
			OUT29oN;
		break;
	case 30:
		if( (Outputs >> 30) & 0x01 )
			OUT30oFF;
		else
			OUT30oN;
		break;
	case 31:
		if( (Outputs >> 31) & 0x01 )
			OUT31oFF;
		else
			OUT31oN;
		break;

	case ALLoUTSON:
		Outputs = 0xFFFFFFFF;
		break;
	default:
		break;
	}
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
	fTimeoutVolume = 1;
}

void timeoutDrive(void){
	fTimeoutDrive = 1;
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
