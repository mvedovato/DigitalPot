/*******************************************************************************************************************************//**
 *
 * @file		DR_Entradas.h
 * @brief		DESCRIPCION ------------------------
 * @date		08/11/2024
 * @author		Marianito
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
// Heat enciende con 0
#define HEAToFF			Outputs |= 0x00000001
#define HEAToN			Outputs &= 0xFFFFFFFE

// Fan enciende con 0
#define FANoFF			Outputs |= 0x00000002
#define FANoN			Outputs &= 0xFFFFFFFD

#define BUZZERoN		Outputs |= 0x00000004
#define BUZZERoFF		Outputs &= 0xFFFFFFFB


//Leds
#define LED0oN		BufferLeds |= 0x00000001
#define LED0oFF		BufferLeds &= 0xFFFFFFFE

#define LED1oN		BufferLeds |= 0x00000002
#define LED1oFF		BufferLeds &= 0xFFFFFFFD

#define LED2oN		BufferLeds |= 0x00000004
#define LED2oFF		BufferLeds &= 0xFFFFFFFB

#define LED3oN		BufferLeds |= 0x00000008
#define LED3oFF		BufferLeds &= 0xFFFFFFF7

#define LED4oN		BufferLeds |= 0x00000010
#define LED4oFF		BufferLeds &= 0xFFFFFFEF

#define LED5oN		BufferLeds |= 0x00000020
#define LED5oFF		BufferLeds &= 0xFFFFFFDF

#define LED6oN		BufferLeds |= 0x00000040
#define LED6oFF		BufferLeds &= 0xFFFFFFBF

#define LED7oN		BufferLeds |= 0x00000080
#define LED7oFF		BufferLeds &= 0xFFFFFF7F

#define LED8oN		BufferLeds |= 0x00000100
#define LED8oFF		BufferLeds &= 0xFFFFFEFF

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
void SetLeds( uint8_t , uint8_t );
void SetOuts( uint8_t , uint8_t );
void HeatOn( void );
void HeatOff( void );
void FanOn( void );
void FanOff( void );
void BuzzerOn( void );
void BuzzerOff( void );
void LedCicloOn( void );
void LedCicloOff( void );
void LedsOn( void );
void LedsOff( void );



#endif /* SOURCES_DRIVER_TK_DR_ENTRADAS_H_ */
