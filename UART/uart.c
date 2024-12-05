/*
 * DR_uart.c
 *
 *  Created on: 26/7/2021
 *      Author: mariano
 */


#include "uart.h"

UART0_Struct UART0_datos;
UART0_Struct UART1_datos;

/*
 * UARTBaudRate = BUSclk / 16*BR
 * BR = BUSclk / 16*UARTBaudRate
 * BR = 16MHz / 16*9600 =
 */

uint8_t InicializarUart0( uint32_t baudRate )
{
	uint8_t retVal = 1;
	/* SIM_SCGC: UART0=1 */
	SIM_SCGC |= SIM_SCGC_UART0_MASK;

	/* SIM_PINSEL: UART0PS=1 RX0 y TX0 por PTA2 y PTA3*/
	SIM_PINSEL |= SIM_PINSEL_UART0PS_MASK;
	//UART0_BDH = UART_BDH_SBR(baudRate);	//No le gusta con esto
	//UART0_BDL = UART_BDL_SBR(baudRate);	//No le gusta con esto
	/* UART0_BDH: LBKDIE=0,RXEDGIE=0,SBNS=0,SBR=0 */
	UART0_BDH = UART_BDH_SBR(0x00);		//así sí
	/* UART0_BDL: SBR=0x68 */
	UART0_BDL = UART_BDL_SBR(0x68);
	UART0_C1  = 0;	//8N1
	//UART0_C2  = UART_C2_TIE_MASK | UART_C2_RIE_MASK | UART_C2_TE_MASK | UART_C2_RE_MASK;	//Funciona
	UART0_C2  = UART_C2_TCIE_MASK | UART_C2_RIE_MASK | UART_C2_TE_MASK | UART_C2_RE_MASK;	//Con tx vacio
	UART0_datos.RX.Indice_out = UART0_datos.RX.Indice_in = 0;
	UART0_datos.TX.Indice_out = UART0_datos.TX.Indice_in = 0;
	NVIC_EnableIRQ(UART0_IRQn);

	return retVal;
}

void UART0_IRQHandler(void)
{
	uint8_t temporal, dato;
	temporal = UART0_S1;

	if( (temporal & UART_S1_RDRF_MASK) >> UART_S1_RDRF_SHIFT )		//RX
	{
		dato = UART0_D;
		UART0_PushRx( dato );

	}


	if( (temporal & UART_S1_TC_MASK) >> UART_S1_TC_SHIFT )		//TX
	{
		dato = UART0_PopTx();
		if( dato != 0xFF )
			UART0_D = (uint8_t)dato;
		else
		{
			//UART0->INTENCLR = (1 << 2); //disable int TX
			//UART0_C2  &= ~( 1 << UART_C2_TIE_SHIFT );		//Funciona
			UART0_C2  &= ~( 1 << UART_C2_TCIE_SHIFT );		//Con tx vacio
			UART0_datos.TX.Datos_Validos = 0;
		}

	}



}

void UART0_Send(uint8_t *Datos, uint32_t Tamanio)
{
	uint32_t i;

	/*if(0 == Tamanio)
		Tamanio = CADENAS_Strlen(Datos);
	*/
	for(i = 0 ; i < Tamanio ; i++)
		UART0_PushTx(Datos[i]);

	return;
}


void UART0_PushTx(uint8_t dato)
{
	UART0_datos.TX.Buffer[UART0_datos.TX.Indice_in] = dato;

	UART0_datos.TX.Indice_in ++;
	UART0_datos.TX.Indice_in %= UART0_TAMANIO_COLA_TX;

	if ( UART0_datos.TX.Datos_Validos == 0 )
	{
		UART0_datos.TX.Datos_Validos = 1;

		UART0_D = (uint8_t)UART0_PopTx();

		//USART0->INTENSET = (1 << 2); // int tx
		//UART0_C2  |= ( 1 << UART_C2_TIE_SHIFT );
		UART0_C2  |= ( 1 << UART_C2_TCIE_SHIFT );
	}
}

int32_t UART0_PopTx( void )
{
	int32_t dato = -1;

	if ( UART0_datos.TX.Indice_in != UART0_datos.TX.Indice_out )
	{
		dato = (int32_t) UART0_datos.TX.Buffer[UART0_datos.TX.Indice_out];
		UART0_datos.TX.Indice_out ++;
		UART0_datos.TX.Indice_out %= UART0_TAMANIO_COLA_TX;
	}
	return dato;
}

void UART0_PushRx(uint8_t dato)
{
	UART0_datos.RX.Buffer[UART0_datos.RX.Indice_in] = dato;

	UART0_datos.RX.Indice_in ++;
	UART0_datos.RX.Indice_in %= UART0_TAMANIO_COLA_RX;
}

int32_t UART0_PopRx( void )
{
	int32_t dato = -1;

	if ( UART0_datos.RX.Indice_in != UART0_datos.RX.Indice_out )
	{
		dato = (int32_t) UART0_datos.RX.Buffer[UART0_datos.RX.Indice_out];
		UART0_datos.RX.Indice_out ++;
		UART0_datos.RX.Indice_out %= UART0_TAMANIO_COLA_RX;
	}
	return dato;
}



uint8_t InicializarUart1( uint32_t baudRate )
{
	uint8_t retVal = 1;
	/* SIM_SCGC: UART0=1 */
	SIM_SCGC |= SIM_SCGC_UART1_MASK;

	/* SIM_PINSEL: UART0PS=1 RX0 y TX0 por PTA2 y PTA3*/
	//SIM_PINSEL |= SIM_PINSEL_UART0PS_MASK;
	//UART0_BDH = UART_BDH_SBR(baudRate);	//No le gusta con esto
	//UART0_BDL = UART_BDL_SBR(baudRate);	//No le gusta con esto
	/* UART0_BDH: LBKDIE=0,RXEDGIE=0,SBNS=0,SBR=0 */
	UART1_BDH = UART_BDH_SBR(0x00);		//así sí
	/* UART0_BDL: SBR=0x68 */
	UART1_BDL = UART_BDL_SBR(0x68);
	UART1_C1  = 0;	//8N1
	//UART0_C2  = UART_C2_TIE_MASK | UART_C2_RIE_MASK | UART_C2_TE_MASK | UART_C2_RE_MASK;	//Funciona
	UART1_C2  = UART_C2_TCIE_MASK | UART_C2_RIE_MASK | UART_C2_TE_MASK | UART_C2_RE_MASK;	//Con tx vacio
	UART1_datos.RX.Indice_out = UART1_datos.RX.Indice_in = 0;
	UART1_datos.TX.Indice_out = UART1_datos.TX.Indice_in = 0;
	NVIC_EnableIRQ(UART1_IRQn);

	return retVal;
}


void UART1_IRQHandler(void)
{
	uint8_t temporal, dato;
	temporal = UART1_S1;

	if( (temporal & UART_S1_RDRF_MASK) >> UART_S1_RDRF_SHIFT )		//RX
	{
		dato = UART1_D;
		UART1_PushRx( dato );

	}


	if( (temporal & UART_S1_TC_MASK) >> UART_S1_TC_SHIFT )		//TX
	{
		dato = UART1_PopTx();
		if( dato != 0xFF )
			UART1_D = (uint8_t)dato;
		else
		{
			//UART0->INTENCLR = (1 << 2); //disable int TX
			//UART0_C2  &= ~( 1 << UART_C2_TIE_SHIFT );		//Funciona
			UART1_C2  &= ~( 1 << UART_C2_TCIE_SHIFT );		//Con tx vacio
			UART1_datos.TX.Datos_Validos = 0;
		}

	}



}

void UART1_Send(uint8_t *Datos, uint32_t Tamanio)
{
	uint32_t i;

	/*if(0 == Tamanio)
		Tamanio = CADENAS_Strlen(Datos);
	*/
	for(i = 0 ; i < Tamanio ; i++)
		UART1_PushTx(Datos[i]);

	return;
}


void UART1_PushTx(uint8_t dato)
{
	UART1_datos.TX.Buffer[UART1_datos.TX.Indice_in] = dato;

	UART1_datos.TX.Indice_in ++;
	UART1_datos.TX.Indice_in %= UART1_TAMANIO_COLA_TX;

	if ( UART1_datos.TX.Datos_Validos == 0 )
	{
		UART1_datos.TX.Datos_Validos = 1;

		UART1_D = (uint8_t)UART1_PopTx();

		//USART0->INTENSET = (1 << 2); // int tx
		//UART0_C2  |= ( 1 << UART_C2_TIE_SHIFT );
		UART1_C2  |= ( 1 << UART_C2_TCIE_SHIFT );
	}
}

int32_t UART1_PopTx( void )
{
	int32_t dato = -1;

	if ( UART1_datos.TX.Indice_in != UART1_datos.TX.Indice_out )
	{
		dato = (int32_t) UART1_datos.TX.Buffer[UART1_datos.TX.Indice_out];
		UART1_datos.TX.Indice_out ++;
		UART1_datos.TX.Indice_out %= UART1_TAMANIO_COLA_TX;
	}
	return dato;
}

void UART1_PushRx(uint8_t dato)
{
	UART1_datos.RX.Buffer[UART1_datos.RX.Indice_in] = dato;

	UART1_datos.RX.Indice_in ++;
	UART1_datos.RX.Indice_in %= UART1_TAMANIO_COLA_RX;
}

int32_t UART1_PopRx( void )
{
	int32_t dato = -1;

	if ( UART1_datos.RX.Indice_in != UART1_datos.RX.Indice_out )
	{
		dato = (int32_t) UART1_datos.RX.Buffer[UART1_datos.RX.Indice_out];
		UART1_datos.RX.Indice_out ++;
		UART1_datos.RX.Indice_out %= UART1_TAMANIO_COLA_RX;
	}
	return dato;
}
