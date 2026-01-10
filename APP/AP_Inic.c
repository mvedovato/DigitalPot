/*
 * TK1706_FW_Inicializaciones.c
 *
 *  Created on: Oct 17, 2013
 *      Author: marcelo
 */


#include <AP_arranque.h>
#include <AP_Control.h>
#include <AP_Inic.h>
#include <AP_prueba.h>
#include <AP_TK.h>
#include <gpio.h>
#include <leds.h>
#include <PR_Carga.h>
#include <PR_display.h>
#include <systick.h>
#include <uart.h>
#include "flash.h"
#include "DR_nmi.h"
#include "DR_SystemInit.h"
#include "DR_LCD16x2.h"
#include "init.h"
#include "timer.h"


/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* Constants and macros
******************************************************************************/

/******************************************************************************
* Local types
******************************************************************************/

/******************************************************************************
* Local function prototypes
******************************************************************************/

/******************************************************************************
* Local variables
******************************************************************************/

/******************************************************************************
* Local functions
******************************************************************************/

/******************************************************************************
* Global functions
******************************************************************************/

void Inicializacion( void )
{
	//PROGRAMA echk = 0 , chk = 0 ;

	InicializarSistema( );
	InicializarNMI( );
	InicializarBoard( );
	//InicializarEEPROM( );
	InicializarSystick( 1000 );
	//InicializarLeds( );
	//InicializarUart0( UART0bAUDrATE );
	InicializarUart1( UART1bAUDrATE );
	//Inicializar_LCD( );
	//InicializarLCDGrafico( );
	//InicializarADC( );

	TimerStart(E_TIMEOUT_VOLUME, T_VOLUME, timeoutVolume, SEG);
	TimerStart(E_TIMEOUT_DRIVE, T_DRIVE, timeoutDrive, SEG);
	TimerStart(E_TIMEOUT_TONE, T_TONE, timeoutTone, SEG);




	/*
	echk = LoadProgramas( );

	chk = Checksum( );

	if ( echk != chk )
		SaveValoresFabrica( ) ; //!< Salva valores de proceso de fabrica + claves de fabrica

	Arranque( );
	UPrg[ 0 ] = 1;	//!< Tiempo de tortuga
	UPrg[ 1 ] = 1 ; //!< Tiempo de liebre

	if ( DipSwitch == 1 )
		PuestaEnMarcha( );

	*/

}
