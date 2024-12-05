/*******************************************************************************************************************************//**
 * @details		Proyecto: Template
 * @file		PR_carga1.c
 * @brief		DESCRIPCION ---------------
 * @date		20/6/2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

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
extern uint8_t fProgramando;							//!< entrada en programacion
extern uint8_t salir_programacion;

extern PROGRAMA UPrg[ N_PARAMETROS ] ;					//!< Parametros de Programa de Usuario

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

//***************************************************************************************
//	Proposito: Incrementa / Decrementa las variables de proseso.
//	Parametros:
//		inx : Posicion del vector de programa.
//		tope : limite del valor a modificar.
//		operacion:
//						1 : Incrementar.
//						-1 : Decrementar.
//	Retorna: void.
//****************************************************************************************
void Sum_Rest( int inx , int tope , char operacion )
{
    if( UPrg[ inx ] == tope )
        return ;

    UPrg[ inx ] = UPrg[ inx ] + operacion * 1;
    return ;
}

//********************************************************************************************
//	Proposito: Guarda un valor de proceso en la ee
//	Parametros:
//			int indice del valor a salvar
//	Retorna: void
//********************************************************************************************
PROGRAMA Checksum( void )
{
	PROGRAMA chk = 0 , i ;
	for ( i = 0 ; i < N_PARAMETROS - 1 ; i++ )
		chk += UPrg[i];

    return chk;
}

void SaveProgramas( void )
{
	uint16_t n ;

	n = N_PARAMETROS * sizeof ( PROGRAMA ) ;

	UPrg[ CHECKSUM ] = Checksum();
	SysTick->CTRL = 0;
	SysTick->CTRL = 0x07;
	EEPROM_Write( (uint8_t *) UPrg , 0 , n );

}


PROGRAMA LoadProgramas( void )
{
	uint16_t n ;

	n = sizeof ( PROGRAMA ) * N_PARAMETROS ;

	EEPROM_Read( (uint8_t *) UPrg , 0 , n );

	return UPrg[ CHECKSUM ];
}


void SaveValoresFabrica( void )
{

	UPrg[ 0 ] = 1;	//!< Tiempo de tortuga
	UPrg[ 1 ] = 1 ; //!< Tiempo de liebre
	UPrg[ 2 ] = 10 ; //!< litros
	UPrg[ 3 ] = 1 ; //!< Tiempo de llenado
	SaveProgramas(  );
}


/**
	@fn  		void Load( PARAMETROS *p )
	@brief 		Carga de un valor de proceso en forma individual
 	@author 	Ing. Marcelo Trujillo
 	@date 		20-06-16
 	@param [in] PARAMETROS *p: puntero a la estructura de configuracion
 		<ul>
			<li> Parametros
			<ol>
			<li> *Valor: Direccion del valor a modificar
			<li> Tope_Max: Limite maximo
			<li> Tope_Min: Limite minimo
			<li> dsp: posicion en el display
			<li> teclas: vector de teclas de incremento y decremento
			</ol>
		</ul>

	@return void
*/
uint8_t CargaParametro( PARAMETROS *p )
{
	uint8_t c = p->teclas[4];

	salir_programacion = ON;

    while( 1 )
	{
		TimerStart( E_PROGRAMACION , T_PROGRAMACION , EV_Programa , SEG );

		if ( c == p->teclas[ 0 ] || c == p->teclas[ 1 ] )
		{
			(*(p->Valor))++;
			if( *(p->Valor) > p->Tope_Max )
				*(p->Valor) = p->Tope_Max ;
		}
		else if ( c == p->teclas[ 2 ] || c == p->teclas[ 3 ] )
		{
			if( *(p->Valor)> p->Tope_Min )
				(*(p->Valor)) -- ;
		}
		else
		{

 			if ( ( c & 0xc0 ) != 0xc0 ) // codigo de soltar tecla
 			{
				salir_programacion = OFF;
				return c;
 			}
		}

		Display( *(p->Valor) , p->dsp );

		while ( ( c = GetKey( ) ) == NO_KEY )
        {
			if( !salir_programacion )
			{
				return NO_KEY;
			}
   		}
	}
}
