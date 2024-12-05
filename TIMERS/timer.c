/*
 * timer.c
 *
 *  Created on: 25 sep. 2021
 *      Author: mariano
 */


/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "timer.h"


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
uint8_t fProgramando;							//!< entrada en programacion
uint8_t salir_programacion;

PROGRAMA UPrg[ N_PARAMETROS ] ;					//!< Parametros de Programa de Usuario
uint8_t fCalibrando = 0;
extern uint8_t estado;
extern uint8_t flag0a3;

volatile uint32_t TmrRun[ N_TIMERS ];
volatile uint8_t g_events[ N_TIMERS ];
void (*g_handlers[N_TIMERS]) (void);
volatile uint8_t StandBy[ N_TIMERS ];
void (*g_interrupts[ N_INTERRUPTS ]) (void);		//!< Vector de interrupciones
volatile uint32_t TicksDelSistema = 0;


/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

static uint8_t TmrBase[ N_TIMERS ];

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
	\fn void Timer_Check(void)
	\brief Decremento periodico de los contadores
 	\details Decrementa los contadores de los timers en ejecucion. Debe ser llamada periodicamente con la base de tiempos
	\return void
*/
void AnalizarTimers(void)
{
	uint32_t i;

	TicksDelSistema++;

	for(i=0; i< N_TIMERS ; i++)
	{
		if(TmrRun[i])
		{
			if ( !StandBy[ i ] )
			{
				TmrRun[i]--;
				if(!TmrRun[i])
					g_events[i] = 1;
			}
		}
	}
}

/**
	\fn void Timer_Event(void)
	\brief Chequeo de timers vencidos
 	\details Llama a los callbacks de los timers vencidos. Debe llamarse desde el lazo principal del programa
	\return void
*/
void TimerEvent(void)
{
	uint8_t i;

	for( i=0 ; i < N_TIMERS ; i++ )
	{
		if(g_events[i])
		{
			g_handlers[i]();
			g_events[i] = 0;
		}
	}
}

/**
	@fn  		void SysTick_InterruptCallback( void )
	@brief 		Intercepta el SysTick
 	@author 	Ing. Marcelo Trujillo
 	@date 		02-10-17
 	@param void
	@return void
*/
void SysTick_InterruptCallback( void )
{
	int i = 0;

	for( i = 0 ; i < N_INTERRUPTS ; i++ )
	{
		if( g_interrupts[i] )
			g_interrupts[i]();
	}
}

/**
	@fn  		void SysTick_InterruptCallback( void )
	@brief 		Intercepta el SysTick
 	@author 	Ing. Marcelo Trujillo
 	@date 		02-10-17
 	@param void
	@return void
*/
void SysTick_SetHandlers( void (* handler )(void) )
{
	int i = 0;

	for( i = 0 ; i < N_INTERRUPTS ; i++ )
	{
		if( !g_interrupts[i] )
		{
			g_interrupts[i] = handler;
			break;
		}
	}
}


/**
	\fn void TimerStart(uint8_t event, timer_t t, void (*handler)(void))
	\brief Inicia un timer
 	\details Inicia el timer \a e al transcurrir el tiempo especificado por \a t se llama a la funcion apuntada por \a handler
 	\param [in] event Numero de evento entre 0 y 31
 	\param [in] t Tiempo del evento. Dependiente de la base de tiempos
 	\param [in] handler Callback del evento
	\return void
*/
void TimerStart(uint8_t event, uint32_t time, Timer_Handler handler , uint8_t base )
{
	switch ( base )
	{
		case DEC:
			time *= DECIMAS;
			break;
		case SEG:
			time = time * ( SEGUNDOS * DECIMAS );// + DECIMAS;
			break;
		case MIN:
			time = time * ( MINUTOS * SEGUNDOS * DECIMAS );// + SEGUNDOS * DECIMAS * 2;
			break;
	}

	TmrBase[event] = base;
	if(time != 0)	//el tiempo no es 0, lo cargo
	{
		TmrRun[event] = time;
		g_events[event] = 0;
	}
	else	//el tiempo es cero, el timer vence automáticamente
	{
		TmrRun[event] = 0;
		g_events[event] = 1;
	}
	g_handlers[event] = handler;
}

/**
	\fn void SetTimer( uint8_t event , timer_t t )
	\brief Inicia un timer
 	\details Reinicia el timer con el valor t (no lo resetea)
 	\param [in] event Numero de evento entre 0 y 31
 	\param [in] t Tiempo del evento. Dependiente de la base de tiempos
 	\return void
*/
void SetTimer( uint8_t event, uint32_t time )
{
	switch ( TmrBase[event] )
	{
		case DEC:
			time *= DECIMAS;
			break;
		case SEG:
			time = time * ( SEGUNDOS * DECIMAS );// + DECIMAS;
			break;
		case MIN:
			time = time * ( MINUTOS * SEGUNDOS * DECIMAS );// + SEGUNDOS * DECIMAS * 2;
			break;
	}
	TmrRun[event] = time;
}

/**
	\fn  GetTimer( uint8_t event )
	\brief Toma el valor al vuelo del timer en cuestion
 	\details Lee el timer
 	\param [in] event Numero de evento entre 0 y 31
 	\return valor del timer
*/
uint32_t GetTimer( uint8_t event )
{
	uint32_t time = TmrRun[event];

	switch ( TmrBase[event] )
	{
		case DEC:
			time /= DECIMAS;
			break;
		case SEG:
			time /= ( SEGUNDOS * DECIMAS );
			break;
		case MIN:
			time /= ( MINUTOS * SEGUNDOS * DECIMAS );
			break;
	}
	return time;
}
/**
	\fn  uint32_t GetTicks( uint8_t event )
	\brief Toma el valor al vuelo de los tics del timmer en cuestion
 	\details Lee el timer
 	\param [in] event Numero de evento entre 0 y 31
 	\return valor del timer
*/
uint32_t GetTicks( uint8_t event )
{
	uint32_t time = TmrRun[event];
	return time;
}

/**
	\fn  StandByTimer( uint8_t event , uint8_t accion)
	\brief Detiene/Arranca el timer, NO lo resetea
 	\details lo pone o lo saca de stand by
 	\param [in] event Numero de evento entre 0 y 31
 	\param [in] accion RUN lo arranca, STOP lo pone en stand by
 	\return valor del timer
*/
uint32_t StandByTimer( uint8_t event , uint8_t accion)
{
	StandBy[event] = accion;
	return 1;
}

/**
	\fn void Timer_Stop(Eventos e)
	\brief Detiene un timer
 	\details Detiene el timer \a e
 	\param [in] e Numero de evento entre 0 y 31
	\return void
*/
void TimerStop(uint8_t event)
{
	TmrRun[event] = 0;
	g_events[event] = 0;
	g_handlers[event] = NULL;
	TmrBase[event] = 0;
	StandBy[event] = RUN;
}

/**
	\fn void Timer_Close(void)
	\brief Detiene los timers
 	\details Detiene todos los timers
	\return void
*/
void TimerClose(void)
{
	uint32_t i;
	for(i=0;i<N_TIMERS;i++)
		TimerStop( i );
}

/**
	\fn  uint32_t GetTicksDelSistma( void )
	\brief Toma el valor al vuelo de los ticks del sistema
 	\details Lee una variable global que se incrementa cada un ms
 	\param void
 	\return valor de los ticks del sistema
*/
uint32_t GetTicksDelSistma( void )
{
	return TicksDelSistema;
}

// App


void Ev_Tortuga ( void )
{

}
void Ev_Liebre ( void )
{

}
void Ev_Demora ( void )
{

}

void Ev_tecla0a3 ( void )
{

}

void Ev_Beep ( void )
{
	static uint8_t fbeep;
	if( fbeep )
	{
		fbeep = 0;
		BuzzerOff();
	}
	else
	{
		fbeep = 1;
		BuzzerOn();
	}
	TimerStart( E_BEEP , T_BEEP , Ev_Beep , DEC );

	return;
}

void Ev_FinBeep ( void )
{
	BuzzerOff();
	TimerStop( E_BEEP );
}

void EV_Programa ( void )
{

}

void EV_Grabar ( void )
{
	SaveProgramas(  );

	return;
}
void EV_adc ( void )
{
	conversor();
	TimerStart( E_CONVERSOR , T_CONVERSOR , EV_adc , DEC );
}


