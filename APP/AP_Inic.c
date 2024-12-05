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
	InicializarADC( );
	InicializarBoard( );
	//InicializarEEPROM( );
	InicializarSystick( 1000 );
	//InicializarUart0( UART0bAUDrATE );
	InicializarUart1( UART1bAUDrATE );

	TimerStart(E_PARPADEO, 1, parpadeo, SEG);

}
