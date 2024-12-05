/*
 * TK14907_AP_Carga.h
 *
 *  Created on: 19/10/2015
 *      Author: Marcelo
 */

#ifndef TK14907_AP_CARGA_H_
#define TK14907_AP_CARGA_H_
/*==================[inclusions]============================================================================*/
#include "AP_TK.h"
/*==================[macros]================================================================================*/

/*==================[typedef]===============================================================================*/

/*==================[external data declaration]=============================================================*/
extern PROGRAMA UPrg[ ];					//!< Parametros de Programa de Usuario
extern PROGRAMA UConfig[ ];
extern uint8_t fProgramando;				//!< entrada en programacion
extern uint8_t  fReprogramacion;			//!< Indica comienzo / fin de reprogranacion
extern uint8_t salir_programacion;

/*==================[external functions declaration]=======================================================*/
uint8_t CargaParametro( PARAMETROS *Valor  );
void SaveProgramas( void );					// Guarda todos los parametros de programa en flash
void SaveVencimientos( void );				// Guarda todos los vencimientos en flash
PROGRAMA LoadProgramas( void );						// Lee los parametros desde la EEprom
void LoadVencimientos( void );
void SaveValoresFabrica( void );			// Primer Guardado de valores
PROGRAMA Checksum( void );					// Calculo de Checksum
void ParametrosFabrica ( void );
uint8_t Load( uint8_t inx );
void Sum_Rest(int inx,int tope,char operacion);
void LoadVal (void);

#endif /* TK14907_AP_CARGA_H_ */
