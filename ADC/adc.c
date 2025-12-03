/*
 * adc.c
 *
 *  Created on: 25/9/2021
 *      Author: Marianito
 */

#include <adc.h>
#include <AP_TK.h>
#include <io.h>
#include "timer.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <PR_Carga.h>
#include <uart.h>
#include "DR_LCD16x2.h"
#include "init.h"



static ADC_Handler g_callback;



uint16_t medida[MUESTRAS][ CANALES ];
volatile uint32_t Vlr_Mdd[ CANALES ] = { 999, 999, 999 };


// Drivers
void ADC_Init( void )
{
	SIM_SCGC |= SIM_SCGC_ADC_MASK;
	ADC_SC3 = ADC_SC3_MODE(2) | ADC_SC3_ADLPC_MASK | ADC_SC3_ADLSMP_MASK | ADC_SC3_ADIV(0x03) | ADC_SC3_ADICLK(1); //12bits, low power, long sample time, inputclock: (BUSCLK/2)/8
	ADC_SC2 = 0;
	ADC_SC4 = 0;//ADC_SC4_ASCANE_MASK | ADC_SC4_AFDEP(8-1);	//8 canales de FIFO con scan mode
	ADC_SC1 = ADC_SC1_ADCO_MASK | ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(0x1F);	//interrupt enabled, continuous conversion, canales deshabilitados
	//ADC_EnableChannel(ChVBAT);
	ADC_EnableChannel(ChCORRIENTE);
	NVIC_EnableIRQ(ADC0_IRQn);
}


void ADC_EnableChannel(uint8_t channel)
{
    uint32_t aux;

    aux = ADC_SC1;
    aux &= ~ADC_SC1_ADCH_MASK;
    ADC_SC1 = aux | ADC_SC1_ADCH(channel);
}

void ADC_DisableChannels( void )
{
    ADC_SC1 &= ~ADC_SC1_ADCH_MASK;
}


uint16_t ADC_GetChannelResult(void)
{
	return ADC_R;
}

void ADC_SetCallback(ADC_Handler callback)
{
	g_callback = callback;
}


void ADC0_IRQHandler(void)
{
	if(g_callback)
		g_callback();
}

// Primitivas


static void ADC_InterruptCallback(void)
{
	static int sampl = 0, i = 0;

	medida[sampl][i]= ADC_GetChannelResult( );			//12 bits. medida[0] channel 12 Watts, medida[1] channel 13 dBm


	switch( i )
	{

	case 0:	//Corriente
		ADC_DisableChannels();
		ADC_EnableChannel(ChVBAT);
		break;

	case 1:	//VBat
		ADC_DisableChannels();
		ADC_EnableChannel(ChVPANEL);
		break;

	case 2:	//VPanel
		ADC_DisableChannels();
		ADC_EnableChannel(ChCORRIENTE);
		break;

	default:
		ADC_DisableChannels();
		ADC_EnableChannel(ChVBAT);
		break;

	}


	i++;
	if( i == CANALES )
	{
		i = 0;
		sampl++;
		sampl %= MUESTRAS;
	}


}

void InicializarADC( void )
{
	ADC_SetCallback(ADC_InterruptCallback);
	ADC_Init();
	ADC_EnableChannel(ADC_CHANNEL_12);
	//ADC_EnableChannel(ADC_CHANNEL_13);
	TimerStart( E_CONVERSOR , T_CONVERSOR , EV_adc , DEC );
	TimerStart( E_IMPRIMIR , T_IMPRIMIR , ImprimirADC , DEC );
}


//********************************************************************************************
//	Proposito: Lectura del valor de tempratura
//	Parametros: void.
//	Retorna: void
//********************************************************************************************
void conversor(void)
{
	uint32_t New_Mdd = 0, aux;
	uint8_t j, i, k;


    for ( k=0 ; k < CANALES ; k++ )
	{
		for( i = 0; i < MUESTRAS - 1 ; i ++)
			for( j = i + 1; j < MUESTRAS; j ++ )
				if( medida[ j ][ k ] < medida[ i ][ k ] )
				{
					aux = medida[ j ][ k ];
					medida[ j ][ k ] = medida[ i ][ k ];
					medida[ i ][ k ] = aux;

				}
		for( i = LIMiNFERIORmUESTRAS; i < LIMsUPERIORmUESTRAS;  i++)
			New_Mdd += medida[ i ][ k ];

		New_Mdd /= CANTpROMmUESTRAS;

		Vlr_Mdd[k] = New_Mdd;

		New_Mdd = 0;

	}



 }

uint32_t ConvertirTensionBateria( uint32_t valor )
{
	valor = (valor * 5 * 1000)/4095;
	valor = valor * FACTORbATERIA;
	return valor;

}

uint32_t ConvertirTensionPanel( uint32_t valor )
{
	valor = (valor * 5 * 1000)/4095;
	valor = valor * FACTORpANEL;
	return valor;

}

int32_t ConvertirCorrienteCarga( uint32_t valor )
{
	int32_t retorno;
	retorno = (valor * 5 * 1000)/4095;
	retorno = (retorno * PENDcORRIENTE) + ORDoRIGENcORRIENTE;
	return retorno;

}
void ImprimirADC( void )
{

}
