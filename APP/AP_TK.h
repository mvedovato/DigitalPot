/*******************************************************************************************************************************//**
 *
 * @file		TK114402.h
 * @brief		DESCRIPCION ------------------------
 * @date		18/9/2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef SOURCES_TK16814_Aplicacion_h_
#define SOURCES_TK16814_Aplicacion_h_

#include "MKE02Z2.h"
#include "gpio.h"
#include "init.h"
#include "io.h"
#include "adc.h"

extern volatile uint32_t  Vlr_Mdd[ CANALES ];

// Aqui se deben hacer las redefiniciones para el proyecto en cuestion.
// Esto permite una capa de abstraccion sin tocar la funcion

#define		L_TIMER_LIEBRE		EstadoLeds[1]
#define		L_TIMER_TORTUGA		EstadoLeds[0]
#define		L_PARADA			EstadoLeds[4]
#define		L_MARCHA_LIEBRE		EstadoLeds[2]
#define		L_MARCHA_TOTUGA		EstadoLeds[3]



#define     LF0					0xc5
#define     LF1					0xc4
#define     LF2					0xc2
#define     LF3					0xc1
#define     LF4					0xc6
#define     LF5					0xc3
#define     LF6					0xc0

/***********************************************************************************
 *** ENTRADAS SALIDAS
 ***********************************************************************************/
#define    	TORTUGA_OFF			Outputs &= 0xfe
#define    	LIEBRE_OFF			Outputs &= 0xfd
#define    	GIRO_IZQUIERDA_OFF	Outputs &= 0xfb
#define    	GIRO_DERECHA_OFF	Outputs &= 0xf7
#define    	CAUDAL_OFF			Outputs &= 0xef
#define    	BEEP_OFF			Outputs &= 0xdf

#define    	TORTUGA_ON			Outputs |= 0x01
#define    	LIEBRE_ON			Outputs |= 0x02
#define    	GIRO_IZQUIERDA_ON	Outputs |= 0x04
#define    	GIRO_DERECHA_ON		Outputs |= 0x08
#define    	CAUDAL_ON			Outputs |= 0x10
#define    	BEEP_ON				Outputs |= 0x20

#define 	Reja				( ( BufferEntradas >> 0 ) & 0x01 ) //!<

/***********************************************************************************
 *** ENTRADAS ANALOGICAS
 ***********************************************************************************/

/***********************************************************************************
 *** TEMPORIZADORES
 ***********************************************************************************/
//!< Eventos reservados 0 al 6 - Utilizar a partir del 6
//!< Losprimeros 5 estan reservados, Usar por encima del evento 5

#define T_TORTUGA						UPrg[ 0 ]
#define T_LIEBRE						UPrg[ 1 ]

#define T_DEMORA		20
#define T_BEEP			5
#define T_FIN_BEEP		30
#define T_ADD_DEMORA	Vlr_Mdd[0]
#define T_INVERSION 	( T_DEMORA + T_ADD_DEMORA )
#define T_GRABAR		4
#define T_CALIBRAR		3 // 10
#define T_TECLA0a3		1


#define E_TECLA0a3		7
#define E_LIEBRE		8
#define E_DEMORA		9
#define E_BEEP			10
#define E_FIN_BEEP		11
#define E_INVERSION		12
#define E_GRABAR		13
#define E_CALIBRAR		14
#define E_LLENAR		15

/***********************************************************************************
 *** PARAMETROS DE PROGRAMA
 ***********************************************************************************/
typedef int32_t		PROGRAMA;

typedef struct Parametros
{
	PROGRAMA *Valor;
	PROGRAMA Tope_Max;
	uint8_t Tope_Min;
	uint8_t dsp;
	uint8_t teclas[5];
}PARAMETROS;

#define		N_UPARAMETROS			4	// !< Poner aqui la cantidad de Parametros del vector de parametros
#define		CHECKSUM				( N_UPARAMETROS )
#define		N_PARAMETROS			( CHECKSUM + 1 )

// Configuracion ------------------------------------------------------------------------------------------------------------------
#define 	CONTROL					0
#define 	CALIBRAR_PRUEBA			1

#endif /* SOURCES_TK16814_Aplicacion_h_ */

