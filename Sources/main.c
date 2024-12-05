/*******************************************************************************************************************************//**
 * @details		Proyecto: AirFryerCuki  @ MCUXpresso con Kinetis MKE02Z64VQH4
 * @file		main.c
 * @brief		Marianito
 * @date		30/10/2024
 * @author		Marianito
 *
 **********************************************************************************************************************************/

#include <AirFryerCuki.h>


uint8_t estado = 0;


uint8_t aTrabajar = 0;
uint8_t enPausa = 0;
uint8_t felegirmodo = 0;
extern const parametrosCuki ParametrosDefault[];
uint32_t segundosCicloBuzzer = DEFAULTsEGUNDOScICLObUZZER;
extern uint32_t minutosCoccion;
extern uint8_t setpoint;
extern uint8_t imprimirParametro;
extern uint8_t indiceModo;
extern uint8_t emergencia;

int main( void )
{
	uint8_t c = NO_KEY;
	uint8_t fTeclaOnOff = 0;
	uint8_t fTeclaTiempoTemperatura = 0;


	Inicializacion( );

	imprimirParametro = TEMPERATURAfREIR;
	minutosCoccion = ParametrosDefault[0].minutos;
	setpoint = ParametrosDefault[0].temperatura;

	while ( 1 )
	{


		c = GetKey ( );
    	imprimirCuki( imprimirParametro );

    	if( emergencia )
    		estado = EMERGENCIA;


    	if( c != NO_KEY )
    	{

    	switch( c ){
    		case BAJAR:
    			if( estado == PAUSA  || estado == IDLE ){

    				if( fTeclaTiempoTemperatura == 0 ){ //Setpoint
						if( setpoint )
							setpoint--;
						if( setpoint <= MINIMOsETPOINT)
							setpoint = MINIMOsETPOINT;	//Tope Mínimo
						imprimirParametro = SETPOINT;

					}

    				if( fTeclaTiempoTemperatura == 1 ){ //Tiempo
						if( minutosCoccion )
							minutosCoccion--;
						if(!minutosCoccion)
							minutosCoccion = MINIMOmINUTOScOCCION;	//Tope Mínimo

						imprimirParametro = MINUTOScCOCCION;

    				}
    				TimerStart(E_IMPRIMIRpARAMETROS, T_IMPRIMIRpARAMETROS, imprimirParametros, SEG);
    			}
    			break;

    		case SUBIR:
    			if( estado == PAUSA || estado == IDLE ){

    				if( fTeclaTiempoTemperatura == 0 ){ //Setpoint
						setpoint++;
						if( setpoint >= MAXIMOsETPOINT )
							setpoint = MAXIMOsETPOINT;	//Tope Máximo
						imprimirParametro = SETPOINT;

					}

    				if( fTeclaTiempoTemperatura == 1 ){ //Tiempo
    					minutosCoccion++;
						if( minutosCoccion >= MAXIMOmINUTOScOCCION)
							minutosCoccion = MAXIMOmINUTOScOCCION;	//Tope Máximo
						imprimirParametro = MINUTOScCOCCION;
    				}
    				TimerStart(E_IMPRIMIRpARAMETROS, T_IMPRIMIRpARAMETROS, imprimirParametros, SEG);
    			}
    			break;

    		case MODO:
    			indiceModo ++;
    			indiceModo %= CANTIDADmODOS;
    			imprimirParametro = ELEGIRmODO;
    			TimerStart(E_IMPRIMIRpARAMETROS, T_IMPRIMIRpARAMETROS, imprimirParametros, SEG);
    			estado = ELECCIONmODO;
    			felegirmodo = 0;
    			TimerStart(E_MODO, T_ELEGIRmODO, elegirModo, SEG);
    			break;

    		case ONoFF:

    			fTeclaOnOff ++;
    			fTeclaOnOff %= 2;

    			break;

    		case TIEMPOtEMPERATURA://0 Temperatura 1 Tiempo
    			fTeclaTiempoTemperatura ++;
    			fTeclaTiempoTemperatura %= 2;
    			if( fTeclaTiempoTemperatura )
    				imprimirParametro = MINUTOScCOCCION;
    			else
    				imprimirParametro = SETPOINT;

    			TimerStart(E_IMPRIMIRpARAMETROS, T_IMPRIMIRpARAMETROS, imprimirParametros, SEG);
    			break;

    		case CANCELAR:
    			estado = 0;
    			estadoCuki(OFF);
				TimerStop(E_CONTROL);
				TimerStop(E_IMPRIMIRpARAMETROS);
				LedHeat(OFF);
				aTrabajar = OFF;
				TimerStart(E_REZAGOfAN, 60, ApagarFan, SEG);
    			break;

    		default:
    			break;
    		}
    	}

    	switch(estado){
    	case IDLE:
    		BarraProgreso( OFF, minutosCoccion );
    		estadoCuki(OFF);
    		aTrabajar = OFF;

    		if( fTeclaOnOff ){
    			estado = COCCION;
    			aTrabajar = ON;
    			TimerStart(E_CONTROL, minutosCoccion, cicloCoccion, MIN);
    			CicloBuzzer( ON, 1, ON );
    			FanOn();
    		}
    		break;

    	case COCCION: //Estado de cocción
    		if( BarraProgreso( ON, minutosCoccion ) == OFF ){
    			estado = COCINADO;
    		}

    		estadoCuki(ON);
    		if( !fTeclaOnOff ){	//Pausa
    			estado = PAUSA;
    			StandByTimer( E_CONTROL, STOP);
    			StandByTimer( E_REZAGOfAN, STOP);
    			aTrabajar = OFF;
    			enPausa = ON;
    			HeatOff();

    		}

    		break;

    	case PAUSA:	//Estado de pausa
    		if(  GetFparpadeo( ) )
    			LedCicloOn();
    		else
    			LedCicloOff();

    		if( fTeclaOnOff ){	//Reanudar
    			estado = COCCION;
    			StandByTimer( E_CONTROL, RUN);
    			StandByTimer( E_REZAGOfAN, RUN);
    			aTrabajar = ON;
    			enPausa = OFF;

    			if( fTeclaTiempoTemperatura == 1 ){	//Redisparo con nuevo tiempo

    				SetTimer(E_CONTROL, minutosCoccion);
        			CicloBuzzer( ON, 1, ON );
        			FanOn();
    			}
    		}
    		break;

    	case COCINADO:
    		if( CicloBuzzer( ON, segundosCicloBuzzer, OFF ) == OFF ){
    			estado = 0;
    			fTeclaOnOff = 0;
    			fTeclaTiempoTemperatura = 0;
    			aTrabajar = 0;
    			enPausa = 0;
    		}
    		break;

    	case ELECCIONmODO:
    			if( felegirmodo ){
    				felegirmodo = 0;
    				estado = IDLE;
    			}
    			minutosCoccion = ParametrosDefault[indiceModo].minutos;
    			setpoint = ParametrosDefault[indiceModo].temperatura;

    		break;

    	case EMERGENCIA:
    		if(  GetFparpadeo( ) )
    			LedsOn();
    		else
    			LedsOff();
    		imprimirParametro = MODOeMERGENCIA;
    		HeatOff();
    		aTrabajar = OFF;
    		break;


    	default:
    		estado = IDLE;
    		HeatOff();
    		break;

    	}
	}
}

