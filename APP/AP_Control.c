/*******************************************************************************************************************************//**
 * @details		Proyecto: AirFryerCuki
 * @file		AP_Control.c
 * @brief		DESCRIPCION ---------------
 * @date		09/11/2024
 * @author		Marianito
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <AP_Control.h>
#include <AP_TK.h>
#include <io.h>
#include <leds.h>
#include <PR_Carga.h>
#include <PR_display.h>
#include <PR_Strings.h>
#include "timer.h"

#include "teclado.h"
#include "io.h"

uint8_t fIntervaloProgreso = 0;
uint8_t fParpadeo = 0;
uint8_t fTimeoutBuzzer = 0;
uint32_t temperatura;
uint32_t temperaturaAmbiente;
uint32_t minutosCoccion;
uint8_t setpoint;
uint8_t imprimirParametro;
uint8_t indiceModo = CANTIDADmODOS;
uint8_t emergencia = 0;
uint8_t arranque = 1;

const parametrosCuki ParametrosDefault[ CANTIDADmODOS ] = {{DEFAULTmINUTOScOCCION, DEFAULTsETpOINT}, {22, 200}, {21,180}, {11,180}, {18,200}};

extern uint8_t setpoint;
extern uint32_t BufferLeds;
extern uint8_t aTrabajar;
extern uint8_t enPausa;
extern uint8_t felegirmodo;

void Control ( void ){
	 temperatura = GetNTC100K();
	 temperaturaAmbiente = GetNTC10K();

	 if( temperatura == 999 ){
		 emergencia = 1;
		 return;
	 }

	if( temperaturaAmbiente == 999 ){
			 emergencia = 1;
			 return;
	}

	if( aTrabajar == ON ){
		if( temperatura > setpoint ){
			HeatOff();
			LedHeat(OFF);
		}

		if( temperatura < (setpoint-BANDA) ){
			HeatOn();
			LedHeat(ON);
		}
	}
	else
	{
		HeatOff();
		LedHeat(OFF);
	}

}


void cicloCoccion( void ){

	LedHeat(OFF);
	HeatOff();
	TimerStop(E_REZAGOfAN);
	TimerStart(E_REZAGOfAN, 1, ApagarFan, MIN);
	aTrabajar = OFF;


}

void ApagarFan( void ){
	FanOff();

}

uint8_t BarraProgreso( uint8_t actividad, uint32_t minutosCuki )
{
	static uint8_t estado = 0;
	uint8_t working = ON;

	if( actividad == OFF ){
		estado = 0;
		LedsBarraProgreso(OFF);
		TimerStop(E_BARRApPROGRESO);
	}else{

	}
	switch( estado ){
	case 0:
		if( actividad == ON ){
			estado = 1;
			LedsBarraProgreso(ON);
			//(minutosCuki*60)/6 = minutosCuki*10). Saco factor comun el disparo del timer
			TimerStart(E_BARRApPROGRESO, (minutosCuki*10), IntervaloProgreso, SEG);
		}
		break;

	case 1:
		if( fParpadeo )
			LED7oN;
		else
			LED7oFF;

		if( fIntervaloProgreso ){
			fIntervaloProgreso = 0;
			estado = 2;
			LED7oFF;
			TimerStart(E_BARRApPROGRESO, (minutosCuki*10), IntervaloProgreso, SEG);
		}
		break;

	case 2:
		if( fParpadeo )
			LED6oN;
		else
			LED6oFF;

		if( fIntervaloProgreso ){
			fIntervaloProgreso = 0;
			estado = 3;
			LED7oFF;
			LED6oFF;
			TimerStart(E_BARRApPROGRESO, (minutosCuki*10), IntervaloProgreso, SEG);
		}
		break;

	case 3:
		if( fParpadeo )
			LED5oN;
		else
			LED5oFF;

		if( fIntervaloProgreso ){
			fIntervaloProgreso = 0;
			estado = 4;
			LED7oFF;
			LED6oFF;
			LED5oFF;
			TimerStart(E_BARRApPROGRESO, (minutosCuki*10), IntervaloProgreso, SEG);
		}
		break;

	case 4:
		if( fParpadeo )
			LED4oN;
		else
			LED4oFF;

		if( fIntervaloProgreso ){
			fIntervaloProgreso = 0;
			estado = 5;
			LED7oFF;
			LED6oFF;
			LED5oFF;
			LED4oFF;
			TimerStart(E_BARRApPROGRESO, (minutosCuki*10), IntervaloProgreso, SEG);
		}
		break;

	case 5:
		if( fParpadeo )
			LED0oN;
		else
			LED0oFF;

		if( fIntervaloProgreso ){
			fIntervaloProgreso = 0;
			estado = 6;
			LED7oFF;
			LED6oFF;
			LED5oFF;
			LED4oFF;
			LED0oFF;
			TimerStart(E_BARRApPROGRESO, (minutosCuki*10), IntervaloProgreso, SEG);
		}
		break;

	case 6:
		if( fParpadeo )
			LED1oN;
		else
			LED1oFF;

		if( fIntervaloProgreso ){
			fIntervaloProgreso = 0;
			estado = 0;
			LED7oFF;
			LED6oFF;
			LED5oFF;
			LED4oFF;
			LED0oFF;
			LED1oFF;
			TimerStop(E_BARRApPROGRESO);
			working = OFF;

		}
		break;

	default:
		break;

	}


	return working;
}

void LedsBarraProgreso(uint8_t actividad ){
	if( actividad == OFF ){
		LED1oFF;
		LED0oFF;
		LED4oFF;
		LED5oFF;
		LED6oFF;
		LED7oFF;
	}

	if( actividad == ON ){
		LED1oN;
		LED0oN;
		LED4oN;
		LED5oN;
		LED6oN;
		LED7oN;
	}
}

void IntervaloProgreso( void ){
	fIntervaloProgreso = 1;
}

void parpadeo( void ){
	fParpadeo ++;
	fParpadeo %= 2;
	TimerStart(E_PARPADEO, 1, parpadeo, SEG);
}

void estadoCuki( uint8_t actividad ){
	if( actividad == OFF ){
		LED3oFF;
		LED2oN;
		//Por las dudas
		HeatOff();

	}else{
		LED2oFF;
		LED3oN;
	}


}

void LedHeat( uint8_t actividad ){
	if( actividad == ON )
		LED8oN;
	else
		LED8oFF;
}


uint8_t CicloBuzzer( uint8_t actividad, uint32_t segundosCuki, uint8_t oneShot )
{
	static uint8_t estado = 0;
	uint8_t working = ON;

	if( actividad == ON  && oneShot == ON ){
		TimerStart(E_ONEsHOT, TIEMPOoNEsHOT, OneShot, SEG);
		BuzzerOn();
	}
	if( actividad == OFF ){
		estado = 0;
		BuzzerOff();
		TimerStop(E_BUZZER);
	}

	switch(estado){
	case 0:
		if( actividad == ON  && oneShot == OFF ){
			estado = 1;
			TimerStart(E_BUZZER, segundosCuki, TimeoutBuzzer, SEG);
			BuzzerOn();

		}
		break;
	case 1:
		if( actividad == ON && oneShot == OFF ){
			if( fTimeoutBuzzer ){
				fTimeoutBuzzer = 0;
				estado = 2;
				TimerStart(E_BUZZER, segundosCuki, TimeoutBuzzer, SEG);
				BuzzerOff();
			}
		}

		break;

	case 2:
		if( actividad == ON && oneShot == OFF ){
			if( fTimeoutBuzzer ){
				fTimeoutBuzzer = 0;
				estado = 3;
				TimerStart(E_BUZZER, segundosCuki, TimeoutBuzzer, SEG);
				BuzzerOn();
			}
		}

		break;

	case 3:
		if( actividad == ON && oneShot == OFF ){
			if( fTimeoutBuzzer ){
				fTimeoutBuzzer = 0;
				estado = 4;
				TimerStart(E_BUZZER, segundosCuki, TimeoutBuzzer, SEG);
				BuzzerOff();
			}
		}

		break;

	case 4:
		if( actividad == ON && oneShot == OFF ){
			if( fTimeoutBuzzer ){
				fTimeoutBuzzer = 0;
				estado = 5;
				TimerStart(E_BUZZER, segundosCuki, TimeoutBuzzer, SEG);
				BuzzerOn();
			}
		}

		break;

	case 5:
		if( actividad == ON  && oneShot == OFF){
			if( fTimeoutBuzzer ){
				fTimeoutBuzzer = 0;
				estado = 0;
				TimerStop(E_BUZZER);
				BuzzerOff();
				working = OFF;
			}
		}

		break;
	default:
		estado = 0;
		working = OFF;
		BuzzerOff();
		break;
	}
	return working;

}

void TimeoutBuzzer( void ){
	fTimeoutBuzzer = 1;
}
void OneShot(void ){
	BuzzerOff();
}

uint8_t GetFparpadeo( void ){
	return fParpadeo;
}

void imprimirParametros( void ){
	imprimirParametro = TEMPERATURAfREIR;
}

void elegirModo( void ){
	felegirmodo = 1;
}

void imprimirCuki( uint8_t parametro ){

	switch( parametro ){
	case TEMPERATURAfREIR:
		Display( temperatura, 0);
		break;

	case SETPOINT:
		Display( setpoint, 0);
		break;

	case MINUTOScCOCCION:
		Display( minutosCoccion, 0);
		break;

	case ELEGIRmODO:
		Display( indiceModo + 1 , 0); //Número de programa que arranca en 1
		break;

	case MODOeMERGENCIA:
		if(  GetFparpadeo( ) ){
			Display(257, 0);
		}
		else{
			Display(258, 0);
		}
		break;

	default:
		Display( temperatura, 0);
			break;

	}
}
