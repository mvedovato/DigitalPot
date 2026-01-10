/*
 * timer.h
 *
 *  Created on: 25 sep. 2021
 *      Author: mariano
 */

#ifndef TIMER_H_
#define TIMER_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <stdio.h>
#include "MKE02Z2.h"
#include "flash.h"
#include "teclado.h"
#include "../APP/AP_Control.h"
#include "../APP/AP_TK.h"
#include "../APP/PR_Carga.h"
#include "../APP/PR_display.h"
#include "../TECLADO/teclado.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
//Numero de eventos que se usaran como maximo en la aplicacion

//!< Eventos reservados 0 al 5. NO USARLOS

#define		RUN				0
#define		STOP			1

#define 	N_INTERRUPTS		10

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/
typedef void (*Timer_Handler)(void);

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
//!< Bases de tiempo
#define		DEC				0
#define		SEG				1
#define		MIN				2

//!< Bases de tiempo
#define		MINUTOS			60
#define		SEGUNDOS		10
#define		DECIMAS			100

//!< Eventos reservados 0 al 5
#define 	E_PARPADEORAPIDO 		0
#define 	E_PARPADEOLENTO			1
#define 	E_PARPADEODISPLAY 		2
#define 	E_PROGRAMACION			3
#define 	E_CONVERSOR				4
#define 	E_ARRANQUE				5
#define 	E_IMPRIMIR				6
#define 	E_LCDGRAFICO			7
#define 	E_TIMEOUT_VOLUME		8
#define 	E_TIMEOUT_DRIVE			9
#define 	E_TIMEOUT_TONE			10

#define 	T_PARPADEORAPIDO 		2
#define 	T_PARPADEOLENTO			5
#define 	T_PARPADEODISPLAY		5
#define 	T_PROGRAMACION 			3
#define 	T_CONVERSOR				5
#define 	T_ARRANQUE				30
#define 	T_IMPRIMIR				20
#define     TIEMPOdELAY     		250
#define 	T_LCDGRAFICO			10
#define     T_VOLUME	     		1
#define 	T_DRIVE					2
#define 	T_TONE					3

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
#define 	N_TIMERS				20				//!< Losprimeros 5 estan reservados, Usar por encima del evento 5

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
extern volatile uint32_t TmrRun[ ];
extern volatile uint8_t g_events[  ];
extern void (*g_handlers[ ]) (void);
extern volatile uint8_t StandBy[  ];
extern volatile uint32_t TicksDelSistema;


/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void TimerStart( uint8_t event , uint32_t time , void (*handler)(void) , uint8_t base );
void TimerStop( uint8_t event );
void TimerClose( void );
void SetTimer( uint8_t event , uint32_t );
uint32_t GetTimer( uint8_t );
uint32_t StandByTimer( uint8_t  , uint8_t );
uint32_t GetTicks( uint8_t event );
uint32_t GetTicksDelSistma( void );

extern uint8_t fCalibrando;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void Ev_Tortuga ( void );
void Ev_Liebre ( void );
void Ev_Demora ( void );
void Ev_Beep ( void );
void Ev_FinBeep ( void );
void EV_Programa ( void );
void EV_Grabar ( void );
void EV_adc ( void );
void Ev_tecla0a3 ( void );


void AnalizarTimers( void );
void TimerEvent( void );
void SysTick_InterruptCallback( void );
void SysTick_SetHandlers( void (* handler )(void) );

void DelayMs (volatile uint32_t);

#endif /* TIMER_H_ */
