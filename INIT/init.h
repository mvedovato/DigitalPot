/*******************************************************************************************************************************//**
 *
 * @file		TK.h
 * @brief		DESCRIPCION ------------------------
 * @date		19/6/2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef SOURCES_DRIVER_TK_FW_TK_H_
#define SOURCES_DRIVER_TK_FW_TK_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "MKE02Z2.h"
#include "gpio.h"

/***********************************************************************************
 *** ENTRADAS SALIDAS
 ***********************************************************************************/
#define		MAX_SALIDAS		32

//Teclado fijo 2 teclas

#define		tecla0			PORTB,2
#define		tecla1			PORTB,3

/*
 Volume n = 6

	 |
	---
	| |		4K7
	---
	 |
	 .
	 |
	---
	| |		10K
	---
	 |
	 .
	 |
	---
	| |		10K
	---
	 |
	 .
	 |
	---
	| |		10K
	---
	 |
	 .
	 |
	---
	| |		18K
	---
	 |
	 .
	 |
	---
	| |		4K7
	---
	 |
	 .
	 |
	---
	| |		560
	---
	 |
	 .
	 |
	---
	| |		1K
	---
	 |
 */

//Salidas control DigPot Volume
#define 	VOLUME_CONTROL_1A		PORTA,1		//OK
#define 	VOLUME_CONTROL_1B		PORTA,0		//OK

// Usados como potes digitales x9C10xS

#define 	VOLUME_CONTROL_1C		PORTE,3		//OK
#define 	VOLUME_CONTROL_1D		PORTE,2		//OK
#define 	VOLUME_CONTROL_2A		PORTG,3		//OK
#define 	VOLUME_CONTROL_2B		PORTG,2		//OK
#define 	VOLUME_CONTROL_2C		PORTG,1		//OK
#define 	VOLUME_CONTROL_2D		PORTG,0		//OK



//Salidas control DigPot Drive
#define 	DRIVE_CONTROL_A		PORTD,4		//OK
#define 	DRIVE_CONTROL_B		PORTF,0		//OK
#define 	DRIVE_CONTROL_C		PORTF,1		//OK
#define 	DRIVE_CONTROL_D		PORTE,4		//OK


//Salidas Poteciómentro digital 10K
/*
#define 	POTE_X9C103S_CS		PORTA,2		//OK
#define 	POTE_X9C103S_UD		PORTA,3		//OK
#define 	POTE_X9C103S_INC	PORTD,2		//OK
*/



#define    	IN1	        	PORTD,3



#define 	IN2				PORTH,7		//OK
#define 	IN3				PORTH,6		//OK
#define 	IN4				PORTE,7		//OK
#define 	IN5				PORTH,2		//OK


#define 	OUT0			PORTD,1		//OK
#define 	OUT1			PORTD,0		//OK
#define 	OUT6			PORTH,1		//OK
#define 	OUT7			PORTH,0		//OK

#define 	OUT8			PORTE,6		//OK
#define 	OUT9			PORTE,5		//OK
#define 	OUT10			PORTB,5		//OK
#define 	OUT11			PORTB,4		//OK
#define 	OUT12			PORTC,3		//OK
#define 	OUT13			PORTC,2		//OK

#define 	OUT14			PORTD,7		//OK
#define 	OUT15			PORTD,6		//OK
#define 	OUT16			PORTD,5		//OK
#define 	OUT17			PORTC,1		//OK
#define 	OUT18			PORTC,0		//OK
#define 	OUT19			PORTF,7		//OK
#define 	OUT20			PORTF,6		//OK	//ADC0.14
#define 	OUT21			PORTF,5		//OK	//ADC0.13

#define 	OUT22			PORTE,4		//OK
#define 	OUT23			PORTF,1		//OK
#define 	OUT24			PORTF,0		//OK
#define 	OUT25			PORTD,4		//OK
#define 	OUT26			PORTD,3		//OK
#define 	OUT27			PORTD,2		//OK
#define 	OUT28			PORTA,1		//OK
#define 	OUT29			PORTA,0		//OK
#define 	OUT30			PORTC,7		//OK
#define 	OUT31			PORTC,6		//OK



/***********************************************************************************
 *** ENTRADAS ANALOGICAS
 ***********************************************************************************/
#define 	MUESTRAS		16

#define 	ADC_CHANNEL_0	0
#define 	ADC_CHANNEL_1	1
#define 	ADC_CHANNEL_11	11
#define 	ADC_CHANNEL_12	12	//PTF4 PIN 4 BR2
#define 	ADC_CHANNEL_13	13	//PTF5 PIN 3 BR2
#define 	ADC_CHANNEL_14	14	//PTF6 PIN 2 BR2 (seguido de AGND PIN1 )

#define		ChCORRIENTE		ADC_CHANNEL_12
#define		ChVPANEL		ADC_CHANNEL_13
#define		ChVBAT			ADC_CHANNEL_14

/***********************************************************************************
 *** DISPLAY
 ***********************************************************************************/

/***********************************************************************************
 *** TECLADO - codigo teclas
 ***********************************************************************************/
#define F0		0
#define F1		1
#define F2		2
#define F3		3
#define F4		4
#define F5		5
#define F6		6
#define F7		7
#define F8		8
#define F9		9
#define F10		10
#define F11		11
#define F12		12
#define F13		13
#define F14		14
#define F15		15

//Teclado membrana
#define TECLAcERO		0
#define TECLAuNO		1
#define TECLAdOS		2
#define TECLAtRES		3
#define TECLAcUATRO		4
#define TECLAcINCO		5
#define TECLAsEIS		6
#define TECLAsIETE		7
#define TECLAoCHO		8
#define TECLAnUEVE		9
#define TECLAaST		10
#define TECLAnUM		11
#define	ALLoUTSON		157

/***********************************************************************************
 *** CONFIGURACION DE APLICACION
 ***********************************************************************************/
#define    	dip0	   		PORTE,6
#define    	dip1	   		PORTH,0

/***********************************************************************************
 *** DEFINES GLOBALES DE PROPOSITO GENERAL
 ***********************************************************************************/
#define		OFF				0
#define		ON				1
#define		PARPADEO		2
#define		abs(x)			( x > 0 ) ? (x) : (-(x))






/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
extern uint8_t DipSwitch;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void InicializarBoard ( void );

#endif /* SOURCES_DRIVER_TK_FW_TK_H_ */
