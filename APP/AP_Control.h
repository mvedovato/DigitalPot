/*******************************************************************************************************************************//**
 *
 * @file		AP_Control.h
 * @brief		DESCRIPCION ------------------------
 * @date		27/4/2017
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef SOURCES_APLICACION_AP_CONTROL_H_
#define SOURCES_APLICACION_AP_CONTROL_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <stdint.h>

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
#define AUTOMATICO	1
#define MANUAL		0

#define IZQUIERDA	1
#define DERECHA		0

#define TORTUGA		0
#define DEMORA		1
#define LIEBRE		2
#define FIN			3

#define DISABLE								255
#define	DEFAULTsETpOINT						200
#define	MINIMOsETPOINT						60
#define	MAXIMOsETPOINT						245
#define	DEFAULTmINUTOScOCCION				20
#define	MINIMOmINUTOScOCCION				1
#define	MAXIMOmINUTOScOCCION				60
#define	DEFAULTsEGUNDOScICLObUZZER			2
#define	BANDA								4
#define	CANTIDADmODOS						5

#define	TEMPERATURAfREIR					0
#define	SETPOINT							1
#define	MINUTOScCOCCION						2
#define	ELEGIRmODO							3
#define MODOeMERGENCIA						4

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/
typedef struct {
	uint32_t minutos;
	uint8_t temperatura;
} parametrosCuki;
/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void Control ( void );
void Automatico ( void );
void ParadaManual ( void );
void ParadaAutomatico ( void );
void cicloCoccion( void );
uint8_t BarraProgreso(uint8_t, uint32_t );
void LedsBarraProgreso(uint8_t );
void IntervaloProgreso( void );
void parpadeo( void );
void estadoCuki( uint8_t );
void ApagarFan( void );
void LedHeat( uint8_t );
uint8_t CicloBuzzer( uint8_t, uint32_t, uint8_t );
void TimeoutBuzzer( void );
void OneShot(void );
uint8_t GetFparpadeo( void );
void imprimirParametros( void );
void elegirModo( void );
void imprimirCuki( uint8_t );

#endif /* SOURCES_APLICACION_AP_CONTROL_H_ */
