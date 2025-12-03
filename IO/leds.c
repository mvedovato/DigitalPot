/*******************************************************************************************************************************//**
 * @details		Proyecto: Template
 * @file		PR_leds.c
 * @brief		Funciones manipuladoras de los leds
 * @date		16/6/2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <display.h>
#include <leds.h>
#include <timer.h>

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
// se completa con la posiscion relativa del digito donde estan asociados los leds con el indice
// respectivo. Esta duplicado porque cada led tiene dos mascaras asociadas
const uint8_t PosMSG_DSP[] = {4,4,4,4,4,4,4,4,4,4};

//0x0001 , 0xfffe , 	//!<a
//0x0002 , 0xfffd , 	//!<b
//0x0004 , 0xfffb , 	//!<c
//0x0008 , 0xfff7 , 	//!<d
//0x0010 , 0xffef , 	//!<e
//0x0020 , 0xffdf , 	//!<f
//0x0040 , 0xffbf , 	//!<g

const uint16_t MascaraMSG_DSP[] = {
	// mascaras de los leds de grupo 0 (led0)
	0x0001 , 0xfffe , 	//!<a
	0x0002 , 0xfffd , 	//!<b
	0x0004 , 0xfffb , 	//!<c
	0x0008 , 0xfff7 , 	//!<d
	0x0010 , 0xffef , 	//!<e
};


/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
static uint8_t fParpadeoRapido,fParpadeoLento;

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
void EV_ParpadeoRapido ( void );
void EV_ParpadeoLento ( void );

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
/**
	@fn  		void EV_ParpadeoRapido ( void )
	@brief 		alterna el flag de parpadeo rapido
 	@author 	Ing. Marcelo Trujillo
 	@date 		16-06-2016
 	@param 		void
	@return void
*/
void EV_ParpadeoRapido ( void )
{
	fParpadeoRapido ++;
	fParpadeoRapido %=2;
	TimerStart( E_PARPADEORAPIDO , T_PARPADEORAPIDO , EV_ParpadeoRapido , DEC );
}

/**
	@fn  		void EV_ParpadeoLento ( void )
	@brief 		alterna el flag de parpadeolento
 	@author 	Ing. Marcelo Trujillo
 	@date 		16-06-2016
 	@param 		void
	@return void
*/
void EV_ParpadeoLento ( void )
{
	fParpadeoLento ++;
	fParpadeoLento %=2;
	TimerStart( E_PARPADEOLENTO , T_PARPADEOLENTO , EV_ParpadeoLento , DEC );
}

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/
/**
	@fn  		void RefrescoDeLeds ( void )
	@brief 		Maneja las acciones de los leds de la placa
	@brief 		llamarla desde Get_Key ()
 	@author 	Ing. Marcelo Trujillo
 	@date 		16-06-2016
 	@param 		void
		<ul>
			<li> L_i
			<ol>
			<li> APAGADO
			<li> ENCENDIDO
			<li> PARPADEORAPIDO
			<li> PARPADEOLENTO
			</ol>
		</ul>
	@return void
*/
void RefrescoDeLeds ( void )
{
	}
/**
	@fn  		void Leds ( uint8_t nLed , uint8_t estado )
	@brief 		Enciende o Apaga un led
 	@author 	Ing. Marcelo Trujillo
 	@date 		16-06-16
 	@param [in] nLed: Numero de led
 	@param [in] estado: Estado del led
		<ul>
			<li> estado
			<ol>
			<li> OFF
			<li> ON
			</ol>
		</ul>
	@return void
*/

void Leds ( uint8_t nLed , uint8_t estado )
{
	uint8_t pos;

	pos = nLed * 2 + estado ;

	if ( estado )
		MSG_DSP[ PosMSG_DSP[pos] ] &= MascaraMSG_DSP[ pos ];
	else
		MSG_DSP[ PosMSG_DSP[pos] ] |= MascaraMSG_DSP[ pos ];
}


/**
	@fn  		void InicializarLeds( void )
	@brief 		Dispara los Timers de Blink
 	@author 	Ing. Marcelo Trujillo
 	@date 		16-06-2016
 	@param 		void
	@return 	void
*/
void InicializarLeds( void )
{
	TimerStart( E_PARPADEORAPIDO , T_PARPADEORAPIDO , EV_ParpadeoRapido , DEC );
	TimerStart( E_PARPADEOLENTO , T_PARPADEOLENTO , EV_ParpadeoLento , DEC );
}
