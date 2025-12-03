/*******************************************************************************************************************************//**
 * @details		Proyecto: TK18101-Empanadas
 * @file		AP_Control.c
 * @brief		DESCRIPCION ---------------
 * @date		27/4/2017
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <AP_Control.h>
#include <AP_TK.h>
#include <io.h>
#include <leds.h>
#include <PR_Carga.h>
#include <PR_display.h>
#include <PR_Strings.h>
#include "timer.h"

#include "teclado.h"
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
uint8_t	EstadoAutomatico = TORTUGA;		//!< Variable de estado de la maquina de estados del ciclo auomatico
uint8_t fLIEBRE_MANUAL;
uint8_t fTORTUGA_MANUAL;
uint8_t fPARADA_MANUAL = OFF;
uint8_t fPARADA_AUTOMATICO = OFF;
uint8_t fReja = OFF;
uint8_t fTortuga,fLiebre;
uint32_t ComienzoCalibracion , FinCalibracion;
uint8_t fLLenar = 0;

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
void Control ( void )
{
	}
/**
	@fn  		void Control ( void )
	@brief 		Realiza el funcionamiento del armado de las empanadas
 	@author 	Ing. Marcelo Trujillo
 	@date 		27/04/17
 	@param 		void
	@return 	void
*/

void Automatico ( void )
{
	//uint32_t t_tortuga;
	uint32_t t_liebre ;

	switch ( EstadoAutomatico )
	{
		case TORTUGA:
			TORTUGA_ON ;
			LIEBRE_OFF ;
			L_TIMER_TORTUGA = PARPADEOLENTO ;
			L_TIMER_LIEBRE = APAGADO ;

			TORTUGA_ON ;
			LIEBRE_OFF ;

			//TimerStart( E_TORTUGA , T_TORTUGA , Ev_Tortuga , MIN );//MIN
			fTortuga = ON;
			EstadoAutomatico = DISABLE;
			break;
		case DEMORA:
			TORTUGA_OFF ;
			LIEBRE_OFF ;
			L_TIMER_TORTUGA = APAGADO ;
			L_TIMER_LIEBRE = APAGADO ;

			TimerStart( E_DEMORA , T_DEMORA + T_ADD_DEMORA , Ev_Demora , DEC );
			EstadoAutomatico = DISABLE;

			break;
		case LIEBRE:
			fTortuga = OFF;
			TORTUGA_OFF ;
			LIEBRE_ON ;

			L_TIMER_TORTUGA = APAGADO ;
			L_TIMER_LIEBRE = PARPADEOLENTO ;
			L_MARCHA_TOTUGA = APAGADO;
			L_MARCHA_LIEBRE = ENCENDIDO;

			TimerStart( E_LIEBRE , T_LIEBRE , Ev_Liebre , MIN ); // MIN
			fLiebre = ON;
			EstadoAutomatico = DISABLE;
			break;
		case FIN:
			BEEP_ON;
			LIEBRE_OFF ;
			TORTUGA_OFF ;

			L_TIMER_TORTUGA = APAGADO ;
			L_TIMER_LIEBRE = APAGADO ;
			L_PARADA = ENCENDIDO;
			L_MARCHA_LIEBRE = APAGADO;
			L_MARCHA_TOTUGA = APAGADO;

			fLiebre = OFF;

			TimerStart( E_BEEP , T_BEEP , Ev_Beep , DEC );
			TimerStart( E_FIN_BEEP , T_FIN_BEEP , Ev_FinBeep , SEG );

			EstadoAutomatico = TORTUGA;
			fPARADA_AUTOMATICO = OFF;

			Display( T_LIEBRE ,DSP2 );
			Display( T_TORTUGA ,DSP1 );

			break;
	}

	if (  Reja == OFF )
	{
		if ( fProgramando == OFF )
		{
			//t_tortuga = GetTimer( E_TORTUGA );
			t_liebre = GetTimer( E_LIEBRE );

			//if ( fTortuga )
			//	Display( t_tortuga + 1 ,DSP1);

			if ( fLiebre )
			{
				Display( 0 , DSP1 );
				Display( t_liebre + 1 , DSP2 );
			}
		}
	}
}

void ParadaAutomatico( void )
{
	}
