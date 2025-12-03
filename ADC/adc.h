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
#define  	CANALES			3

#define 	CANTbYTES					31
#define 	LIMiNFERIORmUESTRAS			MUESTRAS/4
#define 	LIMsUPERIORmUESTRAS 		(3*MUESTRAS)/4
#define 	CANTpROMmUESTRAS 			(LIMsUPERIORmUESTRAS - LIMiNFERIORmUESTRAS)



//Estados
#define		IDLE						0
#define		VOLUME						1
#define		DRIVE						2


#define 	Corriente			Vlr_Mdd[ 0 ]	//Sensor de Corriente
#define		VBat				Vlr_Mdd[ 1 ]	//R1=46,9K R2=9,86K
#define		VPanel				Vlr_Mdd[ 2 ]   	//R1=33,1K R2=9,88K


#define		FACTORbATERIA			((46.9+9.86)/9.86)
#define		FACTORpANEL				((33.1+9.88)/9.88)
#define 	PENDcORRIENTE			(10)
#define 	ORDoRIGENcORRIENTE		(-25)



//Drivers
void ADC_Init(void);
void ADC_EnableChannel(uint8_t channel);
void ADC_DisableChannels( void );
uint16_t ADC_GetChannelResult( void );
void ADC_SetCallback(ADC_Handler callback);

//Primitivas
void InicializarADC(void);
void conversor( void );
void ImprimirADC( void );
uint32_t ConvertirTensionBateria( uint32_t );
uint32_t ConvertirTensionPanel( uint32_t );
int32_t ConvertirCorrienteCarga( uint32_t );


#endif /* FW_ADC_H_ */
