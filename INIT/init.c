/*******************************************************************************************************************************//**
 * @details		Proyecto: Template
 * @file		FW_TK.c
 * @brief		DESCRIPCION ---------------
 * @date		18/7/2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <display.h>
#include <gpio.h>
#include <init.h>
#include <io.h>
#include <leds.h>
#include <teclado.h>
#include <timer.h>
#include "io.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
uint8_t DipSwitch;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

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
	@fn  		void InicializarTK ( void )
	@brief 		Inicializa los puertos gpio de la placa
	@author 	Ing. Marcelo Trujillo
 	@date 		17-06-16
	@return 	void
*/
void InicializarBoard ( void )
{

	// Teclado Fijo


	SetDIR( tecla0  , ENTRADA );
	SetDIR( tecla1  , ENTRADA );

	SetPINMODE( tecla0 , PULL_UP);
	SetPINMODE( tecla1 , PULL_UP);

	// LLave selectora de modo
	SetDIR( IN2  , ENTRADA );
	SetDIR( IN3  , ENTRADA );
	SetDIR( IN4  , ENTRADA );
	SetDIR( IN5  , ENTRADA );

	SetPINMODE( IN2 , PULL_UP);
	SetPINMODE( IN3 , PULL_UP);
	SetPINMODE( IN4 , PULL_UP);
	SetPINMODE( IN5 , PULL_UP);

	// SALIDAS --------------------------------------------
	SetDIR( VOLUME_CONTROL_1A  , SALIDA );
	SetDIR( VOLUME_CONTROL_1B  , SALIDA );
	SetDIR( VOLUME_CONTROL_1C  , SALIDA );
	SetDIR( VOLUME_CONTROL_1D  , SALIDA );
	SetDIR( VOLUME_CONTROL_2A  , SALIDA );
	SetDIR( VOLUME_CONTROL_2B  , SALIDA );
	SetDIR( VOLUME_CONTROL_2C  , SALIDA );
	SetDIR( VOLUME_CONTROL_2D  , SALIDA );

	SetPIN( VOLUME_CONTROL_1A  , ON );
	SetPIN( VOLUME_CONTROL_1B  , OFF );
	SetPIN( VOLUME_CONTROL_1C  , OFF );
	SetPIN( VOLUME_CONTROL_1D  , OFF );
	SetPIN( VOLUME_CONTROL_2A  , OFF );
	SetPIN( VOLUME_CONTROL_2B  , OFF );
	SetPIN( VOLUME_CONTROL_2C  , OFF );
	SetPIN( VOLUME_CONTROL_2D  , OFF );


	SetDIR( DRIVE_CONTROL_A  , SALIDA );
	SetDIR( DRIVE_CONTROL_B  , SALIDA );
	SetDIR( DRIVE_CONTROL_C  , SALIDA );
	SetDIR( DRIVE_CONTROL_D  , SALIDA );

	SetPIN( DRIVE_CONTROL_A  , ON );
	SetPIN( DRIVE_CONTROL_B  , OFF );
	SetPIN( DRIVE_CONTROL_C  , OFF );
	SetPIN( DRIVE_CONTROL_D  , OFF );

	x9c103s_Init( );

	// Handlers colgados del Systick. Se llaman cada 1 ms
	SysTick_SetHandlers( KeysDebounce );
	SysTick_SetHandlers( Debounce );
	//SysTick_SetHandlers( RefrescoOut );
	SysTick_SetHandlers( AnalizarTimers );



}

