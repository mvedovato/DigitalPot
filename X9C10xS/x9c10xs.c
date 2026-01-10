/*
 * x9c10xs.c
 *
 *  Created on: 10 ene. 2026
 *      Author: marianito
 */
#include "x9c10xs.h"

uint8_t x9c103s_volume = 0;
uint8_t x9c104s_drive = 0;
uint8_t x9c104s_tone = 0;

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


