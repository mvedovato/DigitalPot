/*******************************************************************************************************************************//**
 * @details		Proyecto: AirFryerCuki
 * @file		display.c
 * @brief		DESCRIPCION ---------------
 * @date		31-10-2024
 * @author		Marianito
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <display.h>
#include <timer.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define    DIGITO_0     0
#define    DIGITO_1     1
#define    DIGITO_2     2


/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
const static uint16_t Tabla_Digitos_BCD_7seg[] = {CERO,UNO,DOS,TRES,CUATRO,CINCO,SEIS,SIETE,OCHO,NUEVE};
/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
uint16_t MSG_DSP[ N_DIGITOS ] = { CERO ,UNO , DOS};			//!< 	Digitos del display

extern uint8_t emergencia;
extern uint8_t arranque;
/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
static uint8_t fParpadeoDisplay;

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
	@fn  		void EV_ParpadeoDisplay ( void )
	@brief 		alterna el flag de parpadeo Display
 	@author 	Marianito
 	@date 		31-10-2024
 	@param 		void
	@return void
*/
void EV_ParpadeoDisplay ( void )
{

}

/**
	@fn  		void RefrescoDeDisplay( void )
	@brief 		refresca el buffer de display
 	@author 	Marianito
 	@date 		31-10-2024
	@return void
*/
void RefrescoDeDisplay( void )
{
	uint8_t i , inx_min , inx_max, acc;

	for ( i = 0 ; i < N_DISPLAYS ; i++ )
	{
		if ( MSG_USE[ i ] == OFF )
			continue;

		acc = MSG_ACCION[ i ] % 10;

		inx_max = MSG_POS[ i ] + MSG_DIG[ i ];

		switch( acc )
		{
			case ON:
				for ( inx_min = MSG_POS[ i ] ; inx_min < inx_max ; inx_min++ )
					MSG_DSP[ inx_min ] = ( MSG_DSP[ inx_min ] & 0xff80 ) | MSG_AUX[ inx_min ];
				break;
			case OFF:
				for ( inx_min = MSG_POS[ i ] ; inx_min < inx_max ; inx_min++ )
					MSG_DSP[ inx_min ] |= 0x007f;
				break;
			case PARPADEO:
				if( fParpadeoDisplay )
				{
					for ( inx_min = MSG_POS[ i ] ; inx_min < inx_max ; inx_min++ )
						MSG_DSP[ inx_min ] = ( MSG_DSP[ inx_min ] & 0xff80 ) | MSG_AUX[ inx_min ];
				}
				if( !fParpadeoDisplay )
				{
					acc = PARPADEO;
					for ( inx_min = MSG_POS[ i ] ; inx_min < inx_max ; inx_min++ )
						MSG_DSP[ inx_min ] |= 0x007f;
				}
				break;
		}
	}
}



/**
	@fn  		void Display( int16_t Val, uint8_t ndsp )
	@brief 		Muestra un valor en el display de 7 segmentos
 	@author 	Marianito
 	@date 		31-10-2024
 	@param [in] Val: Valor a mostrar
 	@param [in] ndsp: Accion a realizar sobre el display
 	@param [in]
		<ul>
			<li> Parametros
			<ol>
			<li> DSPn: Muestra el Valor
			<li> DSPn_OFF: Apaga el display
			<li> DSPn_BLINK: Proboca el Blink del display
			</ol>
		</ul>
	@return void
*/

void Display( int16_t Val, uint8_t ndsp )
{
	int8_t a;

	if( emergencia || arranque ){
		if( Val == 257 ){
			MSG_DSP[ 0 ] = 0xff;
			MSG_DSP[ 1 ] = 0xff;
			MSG_DSP[ 2 ] = 0xff;
		}

		if( Val == 258 ){
			MSG_DSP[ 0 ] = 0x00;
			MSG_DSP[ 1 ] = 0x00;
			MSG_DSP[ 2 ] = 0x00;
		}

		return;
	}
	for( a = N_DIGITOS-1 ; a >= 0 ; a-- )
	{
		MSG_DSP[ a ] = Tabla_Digitos_BCD_7seg[ Val % 10] & 0x00ff;
		Val /= 10;
	}


}


/**
	@fn  		void ConfigurarDisplay ( uint8_t dsp , uint8_t pos, uint8_t cant )
	@brief 		Configura el la posicio de comiezo de un display t su cantidad de digitos
 	@author 	Marianito
 	@date 		31-10-2024
 	@param [in] dsp: numero de display
  	@param [in] dsp: posicion en el vector
  	@param [in] pos: cantidad de digitos
 	@param [in] use: es para cuando el mismo display tiene dos formas de uso (ej: 4 o dos de dos, caso tipico Reloj).
 						cuando se ua el grupo de dos se debe deahabilitar el grupo decuatro y viceversa

	@return void
*/
void ConfigurarDisplay ( uint8_t dsp , uint8_t pos, uint8_t cant , uint8_t use )
{
	MSG_POS[ dsp ] = pos;		//!< 	Numero de digito donde comienza cada display
	MSG_DIG[ dsp ] = cant;		//!<	Cantifad de digitos d cada display
	MSG_USE[ dsp ] = use;		//!<	Display habilitado o no
}


/**
	@fn  		void BarridoDisplay( void )
	@brief 		Barrido de display
 	@author 	Marianito
 	@date 		31-10-2024
	@return void
*/
void BarridoDisplay( void )
{
	static uint8_t turno = 0;
    uint16_t auxiliar;
    static uint8_t    Indice_Display = 0 ;

    if( turno == 5 ){
		turno = 0;
    	SetPIN ( digito0 , OFF );
		SetPIN ( digito1 , OFF );
		SetPIN ( digito2 , OFF );

		auxiliar = MSG_DSP[ Indice_Display ];

		SetPIN ( seg_a  , (~(   auxiliar         & (uint16_t) 1 )) & 0x01 );
		SetPIN ( seg_b  , (~( ( auxiliar >> 1 )  & (uint16_t) 1 )) & 0x01 );
		SetPIN ( seg_c  , (~( ( auxiliar >> 2 )  & (uint16_t) 1 )) & 0x01 );
		SetPIN ( seg_d  , (~( ( auxiliar >> 3 )  & (uint16_t) 1 )) & 0x01 );
		SetPIN ( seg_e  , (~( ( auxiliar >> 4 )  & (uint16_t) 1 )) & 0x01 );
		SetPIN ( seg_f  , (~( ( auxiliar >> 5 )  & (uint16_t) 1 )) & 0x01 );
		SetPIN ( seg_g  , (~( ( auxiliar >> 6 )  & (uint16_t) 1 )) & 0x01 );
		SetPIN ( seg_dp  , (~( ( auxiliar >> 7 )  & (uint16_t) 1 )) & 0x01 );

		switch( Indice_Display )
		{
			case DIGITO_0:
				SetPIN (digito0,ON);
				break;
			case DIGITO_1:
				SetPIN (digito1,ON);
				break;
			case DIGITO_2:
				SetPIN (digito2,ON);
				break;

		}

		// Incremento el indice del display
		Indice_Display ++;
		Indice_Display %= N_DIGITOS;
    }
    turno ++;
}
