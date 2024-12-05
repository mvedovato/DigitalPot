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
#include "display.h"
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
	@fn  		void InicializarBoard ( void )
	@brief 		Inicializa los puertos gpio de la placa
	@author 	Marianito
 	@date 		31-10-2024
	@return 	void
*/
void InicializarBoard ( void )
{

	// Salidas generales
	SetDIR( fan, SALIDA );
	SetDIR( heat, SALIDA );
	SetDIR( buzzer, SALIDA );

	SetPIN( fan, OFFcUKI );
	SetPIN( heat, OFFcUKI );
	SetPIN( buzzer, OFF );


	//Leds
	SetDIR( led1, SALIDA );
	SetDIR( led2, SALIDA );
	SetDIR( led3, SALIDA );
	SetDIR( led4, SALIDA );
	SetDIR( led5, SALIDA );
	SetDIR( led6, SALIDA );
	SetDIR( led7, SALIDA );
	SetDIR( led8, SALIDA );
	SetDIR( led9, SALIDA );

	SetPIN( led1, OFF );
	SetPIN( led2, OFF );
	SetPIN( led3, OFF );
	SetPIN( led4, OFF );
	SetPIN( led5, OFF );
	SetPIN( led6, OFF );
	SetPIN( led7, OFF );
	SetPIN( led8, OFF );
	SetPIN( led9, OFF );

//	Display 7 Segmentos seg_leds
	SetDIR( seg_a, SALIDA );
	SetDIR( seg_b, SALIDA );
	SetDIR( seg_c, SALIDA );
	SetDIR( seg_d, SALIDA );
	SetDIR( seg_e, SALIDA );
	SetDIR( seg_f, SALIDA );
	SetDIR( seg_g, SALIDA );
	SetDIR( seg_dp, SALIDA );

	SetPIN( seg_a, ON );
	SetPIN( seg_b, ON );
	SetPIN( seg_c, ON );
	SetPIN( seg_d, ON );
	SetPIN( seg_e, ON );
	SetPIN( seg_f, ON );
	SetPIN( seg_g, ON );
	SetPIN( seg_dp, ON );

	//Display 7 Seg cátodos
	SetDIR( digito0, SALIDA );
	SetDIR( digito1, SALIDA );
	SetDIR( digito2, SALIDA );

	SetPIN( digito0, OFF );
	SetPIN( digito1, OFF );
	SetPIN( digito2, OFF );


	// Entradas teclas
	SetDIR( tec_bajar, ENTRADA );
	SetDIR( tec_subir, ENTRADA );
	SetDIR( tec_modo, ENTRADA );
	SetDIR( tec_tiempo, ENTRADA );
	SetDIR( tec_onOff, ENTRADA );

	SetPINMODE( tec_bajar, PULL_UP);
	SetPINMODE( tec_subir, PULL_UP);
	SetPINMODE( tec_modo, PULL_UP);
	SetPINMODE( tec_tiempo, PULL_UP);
	SetPINMODE( tec_onOff, PULL_UP);

	// SALIDAS --------------------------------------------

	// Handlers colgados del Systick. Se llaman cada 1 ms
	SysTick_SetHandlers( KeysDebounce );
	SysTick_SetHandlers( RefrescoOut );
	SysTick_SetHandlers( AnalizarTimers );
	SysTick_SetHandlers( BarridoDisplay );


}

