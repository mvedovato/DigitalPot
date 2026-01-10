/*******************************************************************************************************************************//**
 *
 * @file		DR_Entradas.h
 * @brief		DESCRIPCION ------------------------
 * @date		24/4/2017
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef SOURCES_DRIVER_TK_DR_ENTRADAS_H_
#define SOURCES_DRIVER_TK_DR_ENTRADAS_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "MKE02Z2.h"

#include "init.h"
#include "gpio.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define IN2aCTIVADA			0x0001
#define IN3aCTIVADA			0x0002
#define IN4aCTIVADA			0x0004
#define IN5aCTIVADA			0x0008
#define REPOSO				0

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
#define OUT0oN		Outputs |= 0x00000001
#define OUT0oFF		Outputs &= 0xFFFFFFFE

#define OUT1oN		Outputs |= 0x00000002
#define OUT1oFF		Outputs &= 0xFFFFFFFD

#define OUT2oN		Outputs |= 0x00000004
#define OUT2oFF		Outputs &= 0xFFFFFFFB

#define OUT3oN		Outputs |= 0x00000008
#define OUT3oFF		Outputs &= 0xFFFFFFF7

#define OUT4oN		Outputs |= 0x00000010
#define OUT4oFF		Outputs &= 0xFFFFFFEF

#define OUT5oN		Outputs |= 0x00000020
#define OUT5oFF		Outputs &= 0xFFFFFFDF

#define OUT6oN		Outputs |= 0x00000040
#define OUT6oFF		Outputs &= 0xFFFFFFBF

#define OUT7oN		Outputs |= 0x00000080
#define OUT7oFF		Outputs &= 0xFFFFFF7F

#define OUT8oN		Outputs |= 0x00000100
#define OUT8oFF		Outputs &= 0xFFFFFEFF

#define OUT9oN		Outputs |= 0x00000200
#define OUT9oFF		Outputs &= 0xFFFFFDFF

#define OUT10oN		Outputs |= 0x00000400
#define OUT10oFF	Outputs &= 0xFFFFFBFF

#define OUT11oN		Outputs |= 0x00000800
#define OUT11oFF	Outputs &= 0xFFFFF7FF

#define OUT12oN		Outputs |= 0x00001000
#define OUT12oFF	Outputs &= 0xFFFFEFFF

#define OUT13oN		Outputs |= 0x00002000
#define OUT13oFF	Outputs &= 0xFFFFDFFF

#define OUT14oN		Outputs |= 0x00004000
#define OUT14oFF	Outputs &= 0xFFFFBFFF

#define OUT15oN		Outputs |= 0x00008000
#define OUT15oFF	Outputs &= 0xFFFF7FFF

#define OUT16oN		Outputs |= 0x00010000
#define OUT16oFF	Outputs &= 0xFFFEFFFF

#define OUT17oN		Outputs |= 0x00020000
#define OUT17oFF	Outputs &= 0xFFFDFFFF

#define OUT18oN		Outputs |= 0x00040000
#define OUT18oFF	Outputs &= 0xFFFBFFFF

#define OUT19oN		Outputs |= 0x00080000
#define OUT19oFF	Outputs &= 0xFFF7FFFF

#define OUT20oN		Outputs |= 0x00100000
#define OUT20oFF	Outputs &= 0xFFEFFFFF

#define OUT21oN		Outputs |= 0x00200000
#define OUT21oFF	Outputs &= 0xFFDFFFFF

#define OUT22oN		Outputs |= 0x00400000
#define OUT22oFF	Outputs &= 0xFFBFFFFF

#define OUT23oN		Outputs |= 0x00800000
#define OUT23oFF	Outputs &= 0xFF7FFFFF

#define OUT24oN		Outputs |= 0x01000000
#define OUT24oFF	Outputs &= 0xFEFFFFFF

#define OUT25oN		Outputs |= 0x02000000
#define OUT25oFF	Outputs &= 0xFDFFFFFF

#define OUT26oN		Outputs |= 0x04000000
#define OUT26oFF	Outputs &= 0xFBFFFFFF

#define OUT27oN		Outputs |= 0x08000000
#define OUT27oFF	Outputs &= 0xF7FFFFFF

#define OUT28oN		Outputs |= 0x10000000
#define OUT28oFF	Outputs &= 0xEFFFFFFF

#define OUT29oN		Outputs |= 0x20000000
#define OUT29oFF	Outputs &= 0xDFFFFFFF

#define OUT30oN		Outputs |= 0x40000000
#define OUT30oFF	Outputs &= 0xBFFFFFFF

#define OUT31oN		Outputs |= 0x80000000
#define OUT31oFF	Outputs &= 0x7FFFFFFF

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
extern volatile uint16_t BufferEntradas;
extern uint32_t Outputs;
extern uint32_t MascaraOutputs;


/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void Debounce ( void );
uint16_t get_Entradas( void );
void RefrescoOut ( void );
uint8_t GetFvolume( void );
void SetFvolume( uint8_t );
uint8_t GetFdrive( void );
void SetFdrive( uint8_t );
void timeoutVolume(void);
void timeoutDrive(void);
void timeoutTone(void);
void Control_DigPot_Volume(uint8_t);
void Control_DigPot_Drive(uint8_t);

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

#endif /* SOURCES_DRIVER_TK_DR_ENTRADAS_H_ */
