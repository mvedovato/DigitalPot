/*
 * x9c10xs.h
 *
 *  Created on: 10 ene. 2026
 *      Author: marianito
 */

#ifndef X9C10XS_H_
#define X9C10XS_H_

#include <stdint.h>
#include "gpio.h"

// Volume
#define 	POTE_X9C103S_CS		PORTC,1		//OK
#define 	POTE_X9C103S_UD		PORTC,0		//OK
#define 	POTE_X9C103S_INC	PORTF,7		//OK

// Drive
#define 	POTE_X9C104S_DRIVE_CS		PORTE,3		//OK
#define 	POTE_X9C104S_DRIVE_UD		PORTG,3		//OK
#define 	POTE_X9C104S_DRIVE_INC		PORTE,2		//OK

// Tone
#define 	POTE_X9C104S_TONE_CS		PORTG,2		//OK
#define 	POTE_X9C104S_TONE_UD		PORTG,0		//OK
#define 	POTE_X9C104S_TONE_INC		PORTG,1		//OK

#define    ON_CS			0
#define    OFF_CS			1
#define    ON_INC			0
#define    OFF_INC			1
#define    ON_UD			0
#define    OFF_UD			1

void x9c103s_inc( void );
void x9c103s_dec( void );
void x9c103s_CS_LOW( void );
void x9c103s_CS_HIGH( void );
void x9c103s_INC_LOW( void );
void x9c103s_INC_HIGH( void );
void x9c103s_UD_LOW( void );
void x9c103s_UD_HIGH( void );
void x9c103s_Store_wipe_position( void );
void x9c103s_Standby_current( void );
void x9c103s_SetVolume( uint8_t );
void x9c103s_SetMinimun( void );
void x9c103s_SetMaximus( void );
void x9c103s_Init( void );

//Drive
void x9c104s_Drive_inc( void );
void x9c104s_Drive_dec( void );
void x9c104s_Drive_CS_LOW( void );
void x9c104s_Drive_CS_HIGH( void );
void x9c104s_Drive_INC_LOW( void );
void x9c104s_Drive_INC_HIGH( void );
void x9c104s_Drive_UD_LOW( void );
void x9c104s_Drive_UD_HIGH( void );
void x9c104s_Drive_Store_wipe_position( void );
void x9c104s_Drive_Standby_current( void );
void x9c104s_Drive_SetDrive( uint8_t );
void x9c104s_Drive_SetMinimun( void );
void x9c104s_Drive_SetMaximus( void );
void x9c104s_Drive_Init( void );

//Tone
void x9c104s_Tone_inc( void );
void x9c104s_Tone_dec( void );
void x9c104s_Tone_CS_LOW( void );
void x9c104s_Tone_CS_HIGH( void );
void x9c104s_Tone_INC_LOW( void );
void x9c104s_Tone_INC_HIGH( void );
void x9c104s_Tone_UD_LOW( void );
void x9c104s_Tone_UD_HIGH( void );
void x9c104s_Tone_Store_wipe_position( void );
void x9c104s_Tone_Standby_current( void );
void x9c104s_Tone_SetTone( uint8_t );
void x9c104s_Tone_SetMinimun( void );
void x9c104s_Tone_SetMaximus( void );
void x9c104s_Tone_Init( void );
uint8_t getParameter( void );
void delay_1ms( void );

#endif /* X9C10XS_H_ */
