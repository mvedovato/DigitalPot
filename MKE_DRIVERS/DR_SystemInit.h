/**
 	\file FW_SystemInit.h
 	\brief Header Drivers de inicializacion del sistema para familias MKE02ZXXX4
 	\details Inicializacion de oscilador, watchdog, NMI, reset, debug
 	\author Pablo Irrera Condines
 	\date 2015.10.05
*/

#ifndef FW_SYSTEMINIT_H_
#define FW_SYSTEMINIT_H_

#include "MKE02Z2.h"

void InicializarSistema( void );

#endif /* FW_SYSTEMINIT_H_ */
