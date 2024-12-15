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

//Termistor NTC 100K a VCC
const uint16_t gradosNTC100K[] = {5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,205,210,215,220,225,230,235,240,245,250};
const uint16_t cuentasNTC100K[] = {155,195,244,303,430,438,447,480,505,554,596,654,728,786,860,935,1026,1125,1200,1307,1423,1514,1621,1729,1845,1994,2110,2300,2366,2498,2622,2738,2854,2953,3077,3177,3259,3342,3417,3483,3557,3615,3673,3723,3764,3805,3976,3986,3995,4003};
//Termistor NTC 10K a masa
const uint16_t gradosNTC10K[] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100};
const uint16_t cuentasNTC10K[] = {2997, 2818, 2630, 2437, 2241, 2048, 1859, 1678, 1524, 1349, 1203, 1070, 950, 842, 746, 661, 585, 519, 460, 408, 363};

uint16_t medida[MUESTRAS][ CANALES ];
volatile uint32_t Vlr_Mdd[ CANALES ] = { 999, 999 };

// Drivers
void ADC_Init( void )
{
	SIM_SCGC |= SIM_SCGC_ADC_MASK;
	ADC_SC3 = ADC_SC3_MODE(2) | ADC_SC3_ADLPC_MASK | ADC_SC3_ADLSMP_MASK | ADC_SC3_ADIV(0x03) | ADC_SC3_ADICLK(1); //12bits, low power, long sample time, inputclock: (BUSCLK/2)/8
	ADC_SC2 = 0;
	ADC_SC4 = 0;//ADC_SC4_ASCANE_MASK | ADC_SC4_AFDEP(8-1);	//8 canales de FIFO con scan mode
	ADC_SC1 = ADC_SC1_ADCO_MASK | ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(0x1F);	//interrupt enabled, continuous conversion, canales deshabilitados

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
	static int sampl = 0, i = 0 ;
	medida[sampl][i]= ADC_GetChannelResult( );		//12 bits. medida[0] channel 12 Watts, medida[1] channel 13 dBm
	i++;
	i%=2;
	if( i )
	{
		ADC_DisableChannels();
		ADC_EnableChannel(ADC_CHANNEL_1);
		sampl++;
		if( sampl == MUESTRAS )
		{
			sampl = 0;
		}
	}
	else
	{
		ADC_DisableChannels();
		ADC_EnableChannel(ADC_CHANNEL_0);
	}


}

void InicializarADC( void )
{
	ADC_SetCallback(ADC_InterruptCallback);
	ADC_Init();
	ADC_EnableChannel(ADC_CHANNEL_0);
	TimerStart( E_CONVERSOR , T_CONVERSOR , EV_adc , DEC );

}


//********************************************************************************************
//	Proposito: Lectura del valor de ADC y promedio
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

uint16_t GetNTC100K( void )
{
	float grados, aux;
	int i;

	if( Vlr_Mdd[1] < (cuentasNTC100K[0] -5 ) ){
		grados = 999;
		return (uint16_t)grados;
	}

	for( i = 1; i < 50; i ++)
		if( Vlr_Mdd[1] < cuentasNTC100K[i] )
			break;

	//Pendiente positiva
	grados = Vlr_Mdd[1]*(float)( gradosNTC100K[i-1] - gradosNTC100K[i])/(cuentasNTC100K[i-1] - cuentasNTC100K[i]);
	aux = (float)( cuentasNTC100K[i-1]*gradosNTC100K[i]) - (float)(cuentasNTC100K[i]*gradosNTC100K[i-1]);
	aux = aux / ( cuentasNTC100K[i-1] - cuentasNTC100K[i]);
	grados = grados	+ aux;
	return (uint16_t)grados;
}

uint16_t GetNTC10K( void )
{
	float grados, aux;
	int i;

	if( Vlr_Mdd[0] > (cuentasNTC10K[0] - 5 ) ){
		grados = 999;
		return (uint16_t)grados;
	}

	if( Vlr_Mdd[0] < (cuentasNTC10K[13] ) ){		//Mayor a 65º
		grados = 999;
		return (uint16_t)grados;
	}
	for( i = 1; i < 21; i ++)
		if( Vlr_Mdd[0] < cuentasNTC10K[i] )
			break;

	//Pendiente negativa
	grados = Vlr_Mdd[0]*(float)( gradosNTC10K[i-1]-gradosNTC10K[i])/( cuentasNTC10K[i-1]-cuentasNTC10K[i]);
	aux = (float)( cuentasNTC10K[i-1]*gradosNTC10K[i]) - (float)(cuentasNTC10K[i]*gradosNTC10K[i-1]);
	aux = aux / ( cuentasNTC10K[i-1] - cuentasNTC10K[i]);
	grados = grados	+ aux;
	return (uint16_t)grados;
}

