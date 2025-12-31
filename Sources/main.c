/*******************************************************************************************************************************//**
 * @details		Proyecto: DigitalPot  @ MCUXpresso
 * @file		main.c
 * @brief		Marianito INC
 * @date		06/11/2021
 * @author		Marianito
 *
 **********************************************************************************************************************************/

#include <DigitalPot.h>


uint8_t estado = 0;
int16_t volumen = 0;
int16_t tono = 0;
int16_t distorsion = 0;

int main( void )
{
	uint8_t c = NO_KEY, stepsVolume = 0, stepsDrive = 0;
	int32_t caracter;

	Inicializacion( );
	Display_LCD((unsigned char *)"Digital Pot", 0, 0);
	Control_DigPot_Volume(3);
    Control_DigPot_Drive(2);


	while ( 1 )
	{
    	c = GetKey ( );
    	/*
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
    		Control_DigPot_Volume(stepsVolume);
     		break;
    	case DRIVE:
    		Control_DigPot_Drive(stepsDrive);
     		break;

    	default:
    		estado = IDLE;
    		break;
    	}
     	*/

     	caracter = UART1_PopRx();
     	if( caracter > 0 ){
     		volumeRx((uint8_t)caracter);
     		if( volumen >= 0 ){
     			x9c103s_SetVolume(volumen);
     		}
     		/*
     		driveRx((uint8_t)caracter);
     		if( distorsion > 0 ){
     			distorsion = 0;
     		}

     		toneRx((uint8_t)caracter);
     		if( tono > 0 ){
     			tono = 0;
     		}
     		*/
     	}

	}
}





