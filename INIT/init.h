/*******************************************************************************************************************************//**
 *
 * @file		init.h
 * @brief		DESCRIPCION ------------------------
 * @date		30/10/2024
 * @author		Marianito
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

//Salidas potencia
#define    	fan	        	PORTA,6
#define    	heat	        PORTA,7

//Salidas generales
#define    	buzzer	        PORTE,4

//Leds 7 Segmentos
#define 	seg_a			PORTF,5
#define    	seg_b	        PORTD,3
#define    	seg_c	        PORTE,3
#define 	seg_d			PORTB,5
#define 	seg_e			PORTE,5
#define 	seg_f			PORTD,7
#define 	seg_g			PORTG,1
#define 	seg_dp			PORTE,6

//Cátodos 7 Segmentos
#define 	digito0			PORTF,4
#define 	digito1			PORTD,4
#define    	digito2	        PORTD,2

//Leds
#define    	led1	        PORTB,1
#define		led2			PORTB,2
#define		led3			PORTE,0
#define		led4			PORTC,5
#define    	led5	        PORTB,0
#define    	led6	        PORTF,2
#define 	led7			PORTF,1
#define 	led8			PORTF,0
#define    	led9	        PORTF,3

//Entradas teclado
#define 	tec_tiempo		PORTE,7
#define 	tec_modo		PORTH,6
#define 	tec_onOff		PORTH,2
#define 	tec_bajar		PORTH,1
#define 	tec_subir		PORTH,0




#define		ret3			PORTB,3
#define 	IN2				PORTH,7		//OK
#define 	OUT0			PORTD,1		//OK
#define 	OUT1			PORTD,0		//OK
#define 	OUT11			PORTB,4		//OK
#define 	OUT12			PORTC,3		//OK
#define 	OUT13			PORTC,2		//OK
#define 	OUT15			PORTD,6		//OK
#define 	OUT16			PORTD,5		//OK
#define 	OUT17			PORTC,1		//OK
#define 	OUT18			PORTC,0		//OK
#define 	OUT19			PORTF,7		//OK
#define 	OUT20			PORTF,6		//OK	//ADC0.14
#define 	OUT26			PORTD,3		//OK
#define 	OUT27			PORTD,2		//OK
#define 	OUT28			PORTA,1		//OK
#define 	OUT29			PORTA,0		//OK
#define 	OUT30			PORTC,7		//OK
#define 	OUT31			PORTC,6		//OK



/***********************************************************************************
 *** ENTRADAS ANALOGICAS
 ***********************************************************************************/
//#define	temperatura		//PORTA,1
//#define	NTC_10K			//PORTA,0

#define 	MUESTRAS		16

#define 	ADC_CHANNEL_0	0
#define 	ADC_CHANNEL_1	1
#define 	ADC_CHANNEL_11	11
#define 	ADC_CHANNEL_12	12
#define 	ADC_CHANNEL_13	13
#define 	ADC_CHANNEL_14	14

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

/***********************************************************************************
 *** DEFINES GLOBALES DE PROPOSITO GENERAL
 ***********************************************************************************/
#define		OFF				0
#define		ON				1
#define		OFFcUKI			1
#define		ONcUKI			0
#define		PARPADEO		2
#define		abs(x)			( x > 0 ) ? (x) : (-(x))

#define		ARRANQUE		0
#define		IDLE			1
#define		COCCION			2
#define		PAUSA			3
#define		COCINADO		4
#define		ELECCIONmODO	5
#define		EMERGENCIA		6

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void InicializarBoard ( void );

#endif /* SOURCES_DRIVER_TK_FW_TK_H_ */
