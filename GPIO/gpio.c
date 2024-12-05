/*******************************************************************************************************************************//**
 * @details		Proyecto: Template
 * @file		DR_gpio.c
 * @brief		Funciones de GPIO
 * @date		17/6/2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <gpio.h>

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
*	\fn  void SetDIR(uint8_t port, uint8_t pin, uint8_t direction)
*	\brief Configuracion de GPIO como entrada o salida
*	\details Configura el registro el registro de direccion correspondiente
* 	\param 	[in] port Puerto a configurar
* 	\param 	[in] pin Pin a configurar
* 	\param 	[in] direction Direccion del pin GPIO. Puede ser:
* 		\arg \c GPIO_INPUT para entrada
*		\arg \c GPIO_OUTPUT para salida
*	\return void
*/
void SetDIR( uint8_t port , uint8_t pin , uint8_t direction )
{
	if( port < PORTE)
	{
		if(direction)
		{
			GPIOA_PDDR |= ( 1 << (pin + (port<<3)) );
			GPIOA_PIDR |= ( 1 << (pin + (port<<3)) );
		}
		else
		{
			GPIOA_PDDR &= ~( 1 << (pin + (port<<3)) );
			GPIOA_PIDR &= ~( 1 << (pin + (port<<3)) );
		}
	}
	else
	{
		port -= PORTE;
		if( direction )
		{
			GPIOB_PDDR |= ( 1 << (pin + (port<<3)) );
			GPIOB_PIDR |= ( 1 << (pin + (port<<3)) );
		}
		else
		{
			GPIOB_PDDR &= ~( 1 << (pin + (port<<3)) );
			GPIOB_PIDR &= ~( 1 << (pin + (port<<3)) );
		}
	}
}

/**
	\fn  void SetPIN(uint8_t port, uint8_t pin, uint8_t value)
	\brief Setear valor de pin GPIO
	\details Escribe un valor en un pin de GPIO configurado como salida
	\author Pablo Irrera Condines
 	\param 	[in] port Puerto a configurar
 	\param 	[in] pin Pin a configurar
 	\param 	[in] value Valor del pin GPIO. Valores posibles: 0 o 1
	\return void
*/
void SetPIN(uint8_t port, uint8_t pin, uint8_t value)
{
	if(port < PORTE)
	{
		if(value)
			GPIOA_PSOR |= ( 1 << (pin + (port<<3)) );
		else
			GPIOA_PCOR |= ( 1 << (pin + (port<<3)) );
	}
	else
	{
		port -= PORTE;
		if(value)
			GPIOB_PSOR |= ( 1 << (pin + (port<<3)) );
		else
			GPIOB_PCOR |= ( 1 << (pin + (port<<3)) );
	}
}

/**
	\fn  void TogglePIN(uint8_t port, uint8_t pin)
	\brief Invertir estado de pin GPIO
	\details Cambia el estado de un un pin de GPIO configurado como salida
 	\param 	[in] port Puerto a configurar
 	\param 	[in] pin Pin a configurar
	\return void
*/
void TogglePIN(uint8_t port, uint8_t pin)
{
	if(port < PORTE)
	{
		GPIOA_PTOR |= ( 1 << (pin + (port<<3)) );
	}
	else
	{
		port -= PORTE;
		GPIOB_PTOR |= ( 1 << (pin + (port<<3)) );
	}
}

/**
	\fn  uint8_t GetPIN( uint8_t port , uint8_t pin , uint8_t activo)
	\brief Leer valor de pin GPIO
	\details Lee el valor de un pin de GPIO
 	\param 	[in] port Puerto a leer
 	\param 	[in] pin Pin a leer
  	\param 	[in] activo alto/ bajo

	\return Valor del pin. Puede ser 0 o 1
*/
uint8_t GetPIN( uint8_t port , uint8_t pin , uint8_t activo)
{
	uint8_t in;

	if(port < PORTE)
	{
		in = ( GPIOA_PDIR >> ( pin + (port<<3) ) ) & 0x01;
	}
	else
	{
		port -= PORTE;
		in = ( GPIOB_PDIR >> (pin+(port<<3)) ) & 0x01;
	}

	if ( activo ==  ALTO )
		return in;


	return (in == 0 ) ? 1 : 0;
}


void SetPINMODE( uint8_t port , uint8_t pin ,uint8_t modo )
{
/*	PORT_MemMapPtr base;
	base = ( PORT_MemMapPtr ) ( 0x40049000u + port * 0x1000u);
	PORT_PCR_REG( base , pin ) |=  PORT_PCR_PE_MASK | modo;	// 0 Pull down y 1 Pull up
	// PORT_PCR_PE_MASK: Habilita la pull up / down*/

	if(port <= PORTD)
	{
		if(modo)
			PORT_PUEL |= ( 1 << (pin + (port<<3)) ); //0 sin pull up, 1 con pull up
		else
			PORT_PUEL &= ~( 1 << (pin + (port<<3)) ); //0 sin pull up, 1 con pull up
	}
	else
	{
		port -= PORTE;
		if(modo)
			PORT_PUEH |= ( 1 << (pin + (port<<3)) ); //0 sin pull up, 1 con pull up
		else
			PORT_PUEH &= ~( 1 << (pin + (port<<3)) ); //0 sin pull up, 1 con pull up

	}
}
