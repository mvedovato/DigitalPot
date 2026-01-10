/*******************************************************************************************************************************//**
 * @details		Proyecto: DigitalPot  @ MCUXpresso
 * @file		main.c
 * @brief		Marianito INC
 * @date		06/11/2021
 * @author		Marianito
 *
 **********************************************************************************************************************************/

#include <DigitalPot.h>


int8_t estado = 0;
int16_t volumen = 0;
int16_t tono = 0;
int16_t distorsion = 0;
extern uint8_t parameter;

int main( void )
{
	uint8_t c = NO_KEY, stepsVolume = 0, stepsDrive = 0;
	int32_t caracter, valor;
	uint8_t bufferTx[16];
	uint8_t i, chkTx;


	Inicializacion( );



	while ( 1 )
	{
/*    	c = GetKey ( );

    	if( c != NO_KEY )
    	{
    		if( c == 0 ){
    			estado = VOLUME;
    			stepsVolume++;
    			stepsVolume%=8;
    			TimerStart(E_TIMEOUT_VOLUME, T_VOLUME, timeoutVolume, SEG);

    		}

    		if( c == 1 ){
				estado = DRIVE;
				stepsDrive++;
				stepsDrive%=4;
				TimerStart(E_TIMEOUT_DRIVE, T_DRIVE, timeoutDrive, SEG);

			}
    	}

    	if( GetFvolume() ){
    		SetFvolume(0);
    		estado = IDLE;
    	}

    	if( GetFdrive() ){
			SetFdrive(0);
			estado = IDLE;
		}
     	switch(estado)
    	{
    	case IDLE:
    		break;
    	case VOLUME:

     		break;
    	case DRIVE:

     		break;

    	default:
    		estado = IDLE;
    		break;
    	}


     	caracter = UART1_PopRx();
     	if( caracter > 0 ){
     		volumen = volumeRx((uint8_t)caracter);
     		if( volumen >= 0 ){
     			x9c103s_SetVolume(volumen);
     		}


     		distorsion = driveRx((uint8_t)caracter);
     		if( distorsion >= 0 ){
     			x9c104s_Drive_SetDrive(distorsion);
     		}

     		tono = toneRx((uint8_t)caracter);
     		if( tono >= 0 ){
     			x9c104s_Tone_SetTone(tono);
     		}

     		statusRx((uint8_t)caracter);


     	}
*/
     	caracter = UART1_PopRx();
     	if( caracter > 0 ){
     		valor = analysisRx((uint8_t)caracter);
     		if( valor >= 0 ){
     			switch( parameter ){
     			case 'V':
     				x9c103s_SetVolume(valor);
     				break;

     			case 'D':
     				x9c104s_Drive_SetDrive(valor);
     				break;

     			case 'T':
     				x9c104s_Tone_SetTone(valor);
     				break;

     			case 'G':
     				//>ValueVolume,ValueDrive,ValueTone,chk<

     				sprintf((char *)bufferTx,">,%d,%d,%d,",volumen, tono, distorsion );
     				for(i=0;bufferTx[i];i++){
     					chkTx ^= bufferTx[i];
     				}
     				bufferTx[i] = chkTx;
     				bufferTx[i+1] = '<';
     				bufferTx[i+2] = '\0';
     				UART1_Send(bufferTx, strlen((char *)bufferTx));
     				break;

     			default:

     				break;

     			}

     		}
     	}
	}
}





