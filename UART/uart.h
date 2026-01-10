/*
 * DR_uart.h
 *
 *  Created on: 26/7/2021
 *      Author: mariano
 */

#ifndef SOURCES_DRIVERS_MKE_H_DR_UART_H_
#define SOURCES_DRIVERS_MKE_H_DR_UART_H_

#include "MKE02Z2.h"
#include <stdio.h>
#include <string.h>

#define 	UART0bAUDrATE							9600
#define		UART0_TAMANIO_COLA_RX					10
#define		UART0_TAMANIO_COLA_TX					10

#define 	UART1bAUDrATE							9600
#define		UART1_TAMANIO_COLA_RX					100
#define		UART1_TAMANIO_COLA_TX					100


typedef struct
{
	uint8_t						Datos_Validos;
	uint16_t					Tamanio;
	uint8_t						Buffer[UART0_TAMANIO_COLA_RX];
	uint16_t					Indice_in, Indice_out;
}STRUCT_RX0;

typedef struct
{
	uint8_t						Datos_Validos;
	uint16_t					Tamanio;
	uint8_t						Buffer[UART0_TAMANIO_COLA_TX];
	uint16_t					Indice_in, Indice_out;
}STRUCT_TX0;

typedef struct
{
	STRUCT_RX0					RX;
	STRUCT_TX0					TX;
}UART0_Struct;


uint8_t InicializarUart0( uint32_t);
void UART0_Send(uint8_t *, uint32_t );
void UART0_PushTx(uint8_t );
int32_t UART0_PopTx( void );
void UART0_PushRx(uint8_t );
int32_t UART0_PopRx( void );

uint8_t InicializarUart1( uint32_t );
void UART1_Send(uint8_t *, uint32_t);
void UART1_PushTx(uint8_t );
int32_t UART1_PopTx( void );
void UART1_PushRx(uint8_t );
int32_t UART1_PopRx( void );
int32_t volumeRx( uint8_t );
int32_t driveRx( uint8_t );
int32_t toneRx( uint8_t );
int32_t statusRx( uint8_t );
int32_t analysisRx( uint8_t );

#endif /* SOURCES_DRIVERS_MKE_H_DR_UART_H_ */
