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

uint8_t x9c103s_volume = 0;
uint8_t x9c104s_drive = 0;
uint8_t x9c104s_tone = 0;

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

void x9c103s_inc( void ){

	x9c103s_INC_LOW();
	delay_1ms();
	x9c103s_INC_HIGH();
	delay_1ms();

}

void x9c103s_dec( void ){

	x9c103s_INC_LOW();
	delay_1ms();
	x9c103s_INC_HIGH();
	delay_1ms();
}

void x9c103s_CS_LOW( void ){

	SetPIN( POTE_X9C103S_CS  , ON_CS );
}

void x9c103s_CS_HIGH( void ){

	SetPIN( POTE_X9C103S_CS  , OFF_CS );
}

void x9c103s_INC_LOW( void ){

	SetPIN( POTE_X9C103S_INC  , ON_INC );
}

void x9c103s_INC_HIGH( void ){

	SetPIN( POTE_X9C103S_INC  , OFF_INC );
}

void x9c103s_UD_LOW( void ){

	SetPIN( POTE_X9C103S_UD  , ON_UD );
}

void x9c103s_UD_HIGH( void ){

	SetPIN( POTE_X9C103S_UD  , OFF_UD );
}

void x9c103s_Store_wipe_position( void ){
	SetPIN( POTE_X9C103S_INC  , OFF_INC );
	x9c103s_CS_HIGH(  );
}

void x9c103s_Standby_current( void ){
	SetPIN( POTE_X9C103S_INC  , OFF_INC );
	SetPIN( POTE_X9C103S_CS  , OFF_CS );
}

void x9c103s_SetVolume( uint8_t value ){
	uint8_t distancia, i;
	if( value > 100 )
		return;

	if( value == 100 ){
		x9c103s_SetMaximus();
		return;
	}

	if( value == 0 ){
		x9c103s_SetMinimun();
		return;
	}

	if( value <= x9c103s_volume ){
		x9c103s_CS_LOW();
		x9c103s_UD_LOW();			//Decrementar
		distancia = x9c103s_volume - value;
		for( i=0; i < distancia; i++)
			x9c103s_dec();
	}
	else{
		x9c103s_CS_LOW();
		x9c103s_UD_HIGH();			//Incrementar

		distancia = value - x9c103s_volume;
		for( i=0; i < distancia; i++)
			x9c103s_inc();
	}
	x9c103s_CS_HIGH();
	x9c103s_volume = value;
}

void x9c103s_SetMinimun( void ){
	x9c103s_CS_LOW();
	x9c103s_UD_LOW();

	for( int i = 0; i < 100; i++ ){
		x9c103s_dec( );
	}

	x9c103s_CS_HIGH();

	x9c103s_volume = 0;
}

void x9c103s_SetMaximus( void ){
	x9c103s_CS_LOW();
	x9c103s_UD_HIGH();

	for( int i = 0; i < 100; i++ ){
		x9c103s_inc( );
	}

	x9c103s_CS_HIGH();

	x9c103s_volume = 100;
}

void x9c103s_Init( void ){
	//Pote X9C103S
	SetDIR( POTE_X9C103S_CS  , SALIDA );
	SetDIR( POTE_X9C103S_INC  , SALIDA );
	SetDIR( POTE_X9C103S_UD  , SALIDA );

	SetPIN( POTE_X9C103S_CS  , OFF_CS );
	SetPIN( POTE_X9C103S_INC  , OFF_INC );
	SetPIN( POTE_X9C103S_UD  , OFF_UD );

	//x9c103s_SetMinimun();
	x9c103s_SetMaximus();
}

// Drive


void x9c104s_Drive_inc( void ){

	x9c104s_Drive_INC_LOW();
	delay_1ms();
	x9c104s_Drive_INC_HIGH();
	delay_1ms();

}

void x9c104s_Drive_dec( void ){

	x9c104s_Drive_INC_LOW();
	delay_1ms();
	x9c104s_Drive_INC_HIGH();
	delay_1ms();
}

void x9c104s_Drive_CS_LOW( void ){

	SetPIN( POTE_X9C104S_DRIVE_CS  , ON_CS );
}

void x9c104s_Drive_CS_HIGH( void ){

	SetPIN( POTE_X9C104S_DRIVE_CS  , OFF_CS );
}

void x9c104s_Drive_INC_LOW( void ){

	SetPIN( POTE_X9C104S_DRIVE_INC  , ON_INC );
}

void x9c104s_Drive_INC_HIGH( void ){

	SetPIN( POTE_X9C104S_DRIVE_INC  , OFF_INC );
}

void x9c104s_Drive_UD_LOW( void ){

	SetPIN( POTE_X9C104S_DRIVE_UD  , ON_UD );
}

void x9c104s_Drive_UD_HIGH( void ){

	SetPIN( POTE_X9C104S_DRIVE_UD  , OFF_UD );
}

void x9c104s_Drive_Store_wipe_position( void ){
	SetPIN( POTE_X9C104S_DRIVE_INC  , OFF_INC );
	x9c104s_Drive_CS_HIGH(  );
}

void x9c104s_Drive_Standby_current( void ){
	SetPIN( POTE_X9C104S_DRIVE_INC  , OFF_INC );
	SetPIN( POTE_X9C104S_DRIVE_CS  , OFF_CS );
}

void x9c104s_Drive_SetDrive( uint8_t value ){
	uint8_t distancia, i;
	if( value > 100 )
		return;

	if( value == 100 ){
		x9c104s_Drive_SetMaximus();
		return;
	}

	if( value == 0 ){
		x9c104s_Drive_SetMinimun();
		return;
	}

	if( value <= x9c104s_drive ){
		x9c104s_Drive_CS_LOW();
		x9c104s_Drive_UD_LOW();			//Decrementar
		distancia = x9c104s_drive - value;
		for( i=0; i < distancia; i++)
			x9c104s_Drive_dec();
	}
	else{
		x9c104s_Drive_CS_LOW();
		x9c104s_Drive_UD_HIGH();			//Incrementar

		distancia = value - x9c104s_drive;
		for( i=0; i < distancia; i++)
			x9c104s_Drive_inc();
	}
	x9c104s_Drive_CS_HIGH();
	x9c104s_drive = value;
}

void x9c104s_Drive_SetMinimun( void ){
	x9c104s_Drive_CS_LOW();
	x9c104s_Drive_UD_LOW();

	for( int i = 0; i < 100; i++ ){
		x9c104s_Drive_dec( );
	}

	x9c104s_Drive_CS_HIGH();

	x9c104s_drive = 0;
}

void x9c104s_Drive_SetMaximus( void ){
	x9c104s_Drive_CS_LOW();
	x9c104s_Drive_UD_HIGH();

	for( int i = 0; i < 100; i++ ){
		x9c104s_Drive_inc( );
	}

	x9c104s_Drive_CS_HIGH();

	x9c104s_drive = 100;
}

void x9c104s_Drive_Init( void ){
	//Pote X9C104S Drive
	SetDIR( POTE_X9C104S_DRIVE_CS  , SALIDA );
	SetDIR( POTE_X9C104S_DRIVE_INC  , SALIDA );
	SetDIR( POTE_X9C104S_DRIVE_UD  , SALIDA );

	SetPIN( POTE_X9C104S_DRIVE_CS  , OFF_CS );
	SetPIN( POTE_X9C104S_DRIVE_INC  , OFF_INC );
	SetPIN( POTE_X9C104S_DRIVE_UD  , OFF_UD );

	//x9c104s_Drive_SetMinimun();
	//x9c104s_Drive_SetMaximus();
	x9c104s_Drive_SetDrive(30);
}

// Tone

void x9c104s_Tone_inc( void ){

	x9c104s_Tone_INC_LOW();
	delay_1ms();
	x9c104s_Tone_INC_HIGH();
	delay_1ms();

}

void x9c104s_Tone_dec( void ){

	x9c104s_Tone_INC_LOW();
	delay_1ms();
	x9c104s_Tone_INC_HIGH();
	delay_1ms();
}

void x9c104s_Tone_CS_LOW( void ){

	SetPIN( POTE_X9C104S_TONE_CS  , ON_CS );
}

void x9c104s_Tone_CS_HIGH( void ){

	SetPIN( POTE_X9C104S_TONE_CS  , OFF_CS );
}

void x9c104s_Tone_INC_LOW( void ){

	SetPIN( POTE_X9C104S_TONE_INC  , ON_INC );
}

void x9c104s_Tone_INC_HIGH( void ){

	SetPIN( POTE_X9C104S_TONE_INC  , OFF_INC );
}

void x9c104s_Tone_UD_LOW( void ){

	SetPIN( POTE_X9C104S_TONE_UD  , ON_UD );
}

void x9c104s_Tone_UD_HIGH( void ){

	SetPIN( POTE_X9C104S_TONE_UD  , OFF_UD );
}

void x9c104s_Tone_Store_wipe_position( void ){
	SetPIN( POTE_X9C104S_TONE_INC  , OFF_INC );
	x9c104s_Tone_CS_HIGH(  );
}

void x9c104s_Tone_Standby_current( void ){
	SetPIN( POTE_X9C104S_TONE_INC  , OFF_INC );
	SetPIN( POTE_X9C104S_TONE_CS  , OFF_CS );
}

void x9c104s_Tone_SetTone( uint8_t value ){
	uint8_t distancia, i;
	if( value > 100 )
		return;

	if( value == 100 ){
		x9c104s_Tone_SetMaximus();
		return;
	}

	if( value == 0 ){
		x9c104s_Tone_SetMinimun();
		return;
	}

	if( value <= x9c104s_tone ){
		x9c104s_Tone_CS_LOW();
		x9c104s_Tone_UD_LOW();			//Decrementar
		distancia = x9c104s_tone - value;
		for( i=0; i < distancia; i++)
			x9c104s_Tone_dec();
	}
	else{
		x9c104s_Tone_CS_LOW();
		x9c104s_Tone_UD_HIGH();			//Incrementar

		distancia = value - x9c104s_tone;
		for( i=0; i < distancia; i++)
			x9c104s_Tone_inc();
	}
	x9c104s_Tone_CS_HIGH();
	x9c104s_tone = value;
}

void x9c104s_Tone_SetMinimun( void ){
	x9c104s_Tone_CS_LOW();
	x9c104s_Tone_UD_LOW();

	for( int i = 0; i < 100; i++ ){
		x9c104s_Tone_dec( );
	}

	x9c104s_Tone_CS_HIGH();

	x9c104s_tone = 0;
}

void x9c104s_Tone_SetMaximus( void ){
	x9c104s_Tone_CS_LOW();
	x9c104s_Tone_UD_HIGH();

	for( int i = 0; i < 100; i++ ){
		x9c104s_Tone_inc( );
	}

	x9c104s_Tone_CS_HIGH();

	x9c104s_tone = 100;
}

void x9c104s_Tone_Init( void ){
	//Pote X9C104S Tone
	SetDIR( POTE_X9C104S_TONE_CS  , SALIDA );
	SetDIR( POTE_X9C104S_TONE_INC  , SALIDA );
	SetDIR( POTE_X9C104S_TONE_UD  , SALIDA );

	SetPIN( POTE_X9C104S_TONE_CS  , OFF_CS );
	SetPIN( POTE_X9C104S_TONE_INC  , OFF_INC );
	SetPIN( POTE_X9C104S_TONE_UD  , OFF_UD );

	//x9c104s_Tone_SetMinimun();
	//x9c104s_Tone_SetMaximus();
	x9c104s_Tone_SetTone(30);
}

uint8_t getParameter( void ){
	return 0;
}

void delay_1ms( void ){

}
