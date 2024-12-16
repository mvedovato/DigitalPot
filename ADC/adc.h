/*
 * FW_ADC.h
 *
 *  Created on: 22/7/2015
 *      Author: pablo
 */

#ifndef FW_ADC_H_
#define FW_ADC_H_
#include "MKE02Z2.h"

typedef void (*ADC_Handler)(void);

#include "adc.h"



#define  	CANALES			2

#define		WATTdIRECTcHN	0
#define		WATTrEFcHN		1

#define 	Znom			50
#define		ESCALA1			0				//Directo
#define		ESCALA2			1				//Escala 2 	100mV--> 0,2 mW
											//			5V   --> 500 mW
#define		ESCALA3			2				//Escala 3 	100mV--> 2 W
											//			5V   --> 5000 W
#define		CANTbYTES		30
#define		SEGMENTOS		44				//44 segmentos tomados de a 20º en Tabla_J de -20 a 840

#ifdef DBM1MW
	#define		SEGMENTOSdBm	52			//52 segmentos tomados de a 10 mW
#endif

#ifdef DBM10MW
	#define		SEGMENTOSdBm	509			//509 segmentos tomados de a 1 mW
#endif

#ifdef DBMVARMW
	#define		SEGMENTOSdBm	159			//159 segmentos de mW variables
#endif

#define 	LIMiNFERIORmUESTRAS			MUESTRAS/4
#define 	LIMsUPERIORmUESTRAS 		(3*MUESTRAS)/4
#define 	CANTpROMmUESTRAS 			(LIMsUPERIORmUESTRAS - LIMiNFERIORmUESTRAS)


#define		NEGATIVO		0
#define		POSITIVO		1

//Estados
#define		IDLE						0
#define		FUNCwATTSeSCALA0a3			1
#define		FUNCwATTSeSCALA0a30			2
#define		FUNCwATTSeSCALA0a300		3
#define		FUNCwATTSeSCALA0a3000		4

//#define		FACTOReSCALA0a3WATTS		2.47423206341735
#define		FACTOReSCALA0a3WATTS		2.44948974278318
#define		FACTOReSCALA0a30WATTS		7.824208780217
#define		FACTOReSCALA0a300WATTS		24.7423206341735
#define		FACTOReSCALA0a3000WATTS		78.24208780217

#define		UMBRAL3WATTS				4055
#define		UMBRAL30WATTS				4055
#define		UMBRAL300WATTS				4055
#define		UMBRAL3000WATTS				4055

#define		UMBRALmILIwATTS				2341
#define		UMBRALmICROwATTS			73

#define 	CANTcUENTASfIX				27

//Drivers
void ADC_Init(void);
void ADC_EnableChannel(uint8_t channel);
void ADC_DisableChannels( void );
uint16_t ADC_GetChannelResult( void );
void ADC_SetCallback(ADC_Handler callback);

//Primitivas
void InicializarADC(void);
void conversor( void );
uint16_t GetNTC100K( void );
uint16_t GetNTC10K( void );
void ADC_DisableIRQ( void );
void ADC_EnableIRQ( void );



#endif /* FW_ADC_H_ */
