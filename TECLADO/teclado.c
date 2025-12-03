/*******************************************************************************************************************************//**
 * @details		Proyecto: Template
 * @file		DR_teclado.c
 * @brief		DESCRIPCION ---------------
 * @date		17/6/2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <teclado.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define	    TICKSdErEPETICION		100
#define	    CANTIDADdErEBOTES		25
#define	    ACEPTArEPETICION		450

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
uint8_t key = NO_KEY;	//!< Buffer de teclado
uint8_t fControl = OFF;			//!< Indica si el ciclo fue disparado
uint8_t fEncendido = OFF;		//!< Indica si el equipo esta Apagado o encendido


/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
static uint8_t KeysScan(void);

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
/**
	@fn  		static uint8_t KeysScan(void)
	@brief 		retorna el codigo de tecla oprimida
 	@author 	Ing. Marcelo Trujillo
 	@date 		17-06-16
 	@param 		void
	@return 	void
*/
static uint8_t KeysScan(void)
{
	uint8_t Key = NO_KEY;

	if ( GetPIN( tecla0 , BAJO ) )
		Key = 0 ;
	if ( GetPIN( tecla1 , BAJO ) )
		Key = 1 ;
	return Key;
}
 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/

/**
	@fn  		void KeysDebounce( void )
	@brief 		Elimina el rebote de los pulsadores de un teclado
 	@author 	Ing. Marcelo Trujillo
 	@date 		17-06-16
 	@param 		void
	@return 	void
*/
void KeysDebounce( void )
{
	// Se definen estaticas para encapsular el codigo
	static uint8_t CodigoAnterior = NO_KEY;
	static uint16_t TicksDeRepeticion;
	static uint8_t EstadosEstables = 0;
	static uint8_t Repeticion = OFF;
	uint8_t CodigoActual = NO_KEY;

	CodigoActual = KeysScan( );

	if( CodigoActual == NO_KEY )	// No hay tecla presionada o hubo un rebote
	{
		//key = CodigoAnterior | 0xc0;
		key = NO_KEY;
		CodigoAnterior = NO_KEY;
		Repeticion = OFF;
		EstadosEstables = 0;
		return;
	}

	if(EstadosEstables == 0)			// Se detecto una tecla por primera vez
	{
		CodigoAnterior = CodigoActual;
		EstadosEstables = 1;
		return;
	}

	if( EstadosEstables == CANTIDADdErEBOTES )
	{
		key = CodigoActual;	// Acepto la nueva tecla
		EstadosEstables = CANTIDADdErEBOTES + 1; // Para que no entre mas
																				// hasta concluir la repeticion
		Repeticion = ON;														// Entro al modo REPETICION
		TicksDeRepeticion = ACEPTArEPETICION;
		return;
	}

	if( Repeticion == OFF )
	{
		if( CodigoActual != CodigoAnterior )
		{
			// Esta Condicion es poco probable
			CodigoAnterior = NO_KEY;
			EstadosEstables = 0;
		}
		else
			EstadosEstables ++;

		return;
	}
	else
	{
		TicksDeRepeticion--;

		if( !TicksDeRepeticion )
		{
			key = CodigoActual | 0x80;				// Acepto codigo de repeticion
			TicksDeRepeticion = TICKSdErEPETICION; 	// Reanudamos la espera
		}
	}
}

/**
	@fn  		uint8_t GetKey( void )
	@brief 		retorna el contenodo del buffer de teclado
 	@author 	Ing. Marcelo Trujillo
 	@date 		17-06-16
  	@param 		void
	@return 	el contenido delbufer de teclado
*/
uint8_t GetKey( void )
{
	uint8_t Key = NO_KEY;

	TimerEvent( );
	RefrescoDeDisplay( );
	RefrescoDeLeds( );
	Control ( );

	Key = key;
	key = NO_KEY;
	return Key;
}

uint8_t TecMebrana( uint8_t tecla )
{
	switch( tecla )
		{
		case 0:
			return TECLAuNO;
			break;
		case 1:
			return TECLAdOS;
			break;
		case 2:
			return TECLAtRES;
			break;
		case 4:
			return TECLAcUATRO;
			break;
		case 5:
			return TECLAcINCO;
			break;
		case 6:
			return TECLAsEIS;
			break;
		case 8:
			return TECLAsIETE;
			break;
		case 9:
			return TECLAoCHO;
			break;
		case 10:
			return TECLAnUEVE;
			break;
		case 12:
			return TECLAaST;
			break;
		case 13:
			return TECLAcERO;
			break;
		case 14:
			return TECLAnUM;
			break;

		default:
			return NO_KEY;
			break;

		}
}

