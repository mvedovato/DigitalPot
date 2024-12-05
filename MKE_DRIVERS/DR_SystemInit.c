/**
 	\file FW_SystemInit.c
 	\brief Drivers de inicializacion del del sistema para familias MKE02ZXXX4
 	\details Inicializacion de oscilador, watchdog, NMI, reset, debug
 	\author Pablo Irrera Condines
 	\date 2015.10.05
*/

#include "DR_SystemInit.h"

#undef	CLOCK_SETUP
/* Valor de CLOCK_SETUP:
0: Oscilador interno. CORE_CLOCK = 16.777216MHz BUS_CLOCK = 16.777216MHz
1: Oscilador interno. CORE_CLOCK = 33.554432MHz BUS_CLOCK = 16.777216MHz
2: Cristal de 4MHz. CORE_CLOCK = 16MHz BUS_CLOCK = 16MHz
3: Cristal de 4MHz. CORE_CLOCK = 32MHz BUS_CLOCK = 16MHz
*/
#define CLOCK_SETUP		0

//1#define CPU_XTAL_CLOCK			4000000u /* Value of the external crystal or oscillator clock frequency in Hz */
#define CPU_XTAL_CLOCK			4194304u
#define CPU_INTERNAL_CLOCK		32768u   /* Value of the internal oscillator clock frequency in Hz  */

/********************************************************************************
	\fn static void SystemClocksUpdate(void)
	\brief: Funcion privada para actualizar el clock del sistema
	\details: Actualiza la variable SystemCoreClock de CMSIS con el bus clock
	\author: Pablo Irrera Condines
	\return void
********************************************************************************/
static void SystemClocksUpdate(void)
{
  uint32_t ICSOUTClock;                                                        /* Variable to store output clock frequency of the ICS module */
  uint8_t Divider;

  if ((ICS->C1 & ICS_C1_CLKS_MASK) == 0x0u) {
    /* Output of FLL is selected */
    if ((ICS->C1 & ICS_C1_IREFS_MASK) == 0x0u) {
      /* External reference clock is selected */
      ICSOUTClock = CPU_XTAL_CLOCK;                                         /* System oscillator drives ICS clock */
      Divider = (uint8_t)(1u << ((ICS->C1 & ICS_C1_RDIV_MASK) >> ICS_C1_RDIV_SHIFT));
      ICSOUTClock = (ICSOUTClock / Divider);  /* Calculate the divided FLL reference clock */
      if ((OSC->CR & OSC_CR_RANGE_MASK) != 0x0u) {
        ICSOUTClock /= 32u;                                                  /* If high range is enabled, additional 32 divider is active */
      }
    } else {
      ICSOUTClock = CPU_INTERNAL_CLOCK;                                          /* The internal reference clock is selected */
    }
    ICSOUTClock *= 1024u;                                                    /* Apply 1024 FLL multiplier */
  } else if ((ICS->C1 & ICS_C1_CLKS_MASK) == 0x40u) {
    /* Internal reference clock is selected */
    ICSOUTClock = CPU_INT_CLK_HZ;
  } else if ((ICS->C1 & ICS_C1_CLKS_MASK) == 0x80u) {
    /* External reference clock is selected */
    ICSOUTClock = CPU_XTAL_CLK_HZ;
  } else {
    /* Reserved value */
    return;
  }
  ICSOUTClock = ICSOUTClock >> ((ICS->C2 & ICS_C2_BDIV_MASK) >> ICS_C2_BDIV_SHIFT);
  SystemCoreClock = (ICSOUTClock / (1u + ((SIM->BUSDIV & SIM_BUSDIV_BUSDIV_MASK) >> SIM_BUSDIV_BUSDIV_SHIFT)));

}


/********************************************************************************
	\fn void InicializarSistema( void )
	\brief: Inicializacion del sistema
	\details: Inicializa oscilador segun configuracion establecida. Deshabilita
			  watchdog y NMI. Habilita reset y debug. Actualiza variables de clock
	\author: Pablo Irrera Condines
	\return void
********************************************************************************/
void InicializarSistema( void )
{
#if (DISABLE_WDOG)
	/* WDOG->TOVAL: TOVAL=0xE803 */
	WDOG->TOVAL = WDOG_TOVAL_TOVAL(0xE803); /* Timeout value */
	/* WDOG->CS2: WIN=0,FLG=0,??=0,PRES=0,??=0,??=0,CLK=1 */
	WDOG->CS2 = WDOG_CS2_CLK(0x01);       /* 1-kHz clock source */
	/* WDOG->CS1: EN=0,INT=0,UPDATE=1,TST=0,DBG=0,WAIT=1,STOP=1 */
	WDOG->CS1 = WDOG_CS1_UPDATE_MASK |
			 WDOG_CS1_TST(0x00) |
			 WDOG_CS1_WAIT_MASK |
			 WDOG_CS1_STOP_MASK;

#endif /* (DISABLE_WDOG) */
#if (CLOCK_SETUP == 0)
	/* ICS->C2: BDIV|=1 */
	ICS->C2 |= ICS_C2_BDIV(0x01);         /* Update system prescalers */
	/* SIM->BUSDIV: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,BUSDIV=0 */
	SIM->BUSDIV = 0x00U;                  /* Update system prescalers */
	/* Switch to FEI Mode */
	/* ICS->C1: CLKS=0,RDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
	ICS->C1 = ICS_C1_CLKS(0x00) |
		   ICS_C1_RDIV(0x00) |
		   ICS_C1_IREFS_MASK |
		   ICS_C1_IRCLKEN_MASK;
	/* ICS->C2: BDIV=1,LP=0 */
	ICS->C2 = (uint8_t)((ICS->C2 & (uint8_t)~(uint8_t)(
			ICS_C2_BDIV(0x06) |
			ICS_C2_LP_MASK
		   )) | (uint8_t)(
			ICS_C2_BDIV(0x01)
		   ));
	/* OSC->CR: OSCEN=0,??=0,OSCSTEN=0,OSCOS=0,??=0,RANGE=0,HGO=0,OSCINIT=0 */
	OSC->CR = 0x00U;
	while((ICS->S & ICS_S_IREFST_MASK) == 0x00U) { /* Check that the source of the FLL reference clock is the internal reference clock. */
	}
	while((ICS->S & 0x0CU) != 0x00U) {    /* Wait until output of the FLL is selected */
	}
#elif (CLOCK_SETUP == 1)
	/* SIM->BUSDIV: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,BUSDIV=1 */
	SIM->BUSDIV = 0x01U;                  /* BUS_CLOCK  = ICSOUTCLK/2 */
	/* Switch to FEI Mode */
	/* ICS->C1: CLKS=0,RDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
	ICS->C1 = ICS_C1_CLKS(0x00) |
		   ICS_C1_RDIV(0x00) |
		   ICS_C1_IREFS_MASK |
		   ICS_C1_IRCLKEN_MASK;
	/* ICS->C2: BDIV=0,LP=0 */
	ICS->C2 &= ~(ICS_C2_BDIV(0x07) | ICS_C2_LP_MASK);
	/* OSC->CR: OSCEN=0,??=0,OSCSTEN=0,OSCOS=0,??=0,RANGE=0,HGO=0,OSCINIT=0 */
	OSC->CR = 0x00U;
	while((ICS->S & ICS_S_IREFST_MASK) == 0x00U) { /* Check that the source of the FLL reference clock is the internal reference clock. */
	}
	while((ICS->S & 0x0CU) != 0x00U) {    /* Wait until output of the FLL is selected */
	}
#elif (CLOCK_SETUP == 2)
	/* ICS->C2: BDIV|=1 */
	ICS->C2 |= ICS_C2_BDIV(0x01);         /* Update system prescalers */
	/* SIM->BUSDIV: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,BUSDIV=0 */
	SIM->BUSDIV = 0x00U;                  /* Update system prescalers */
	/* Switch to FEE Mode */
	/* ICS->C2: BDIV=1,LP=0 */
	ICS->C2 = (uint8_t)((ICS->C2 & (uint8_t)~(uint8_t)(
			ICS_C2_BDIV(0x06) |
			ICS_C2_LP_MASK
		   )) | (uint8_t)(
			ICS_C2_BDIV(0x01)
		   ));
	/* OSC->CR: OSCEN=1,??=0,OSCSTEN=0,OSCOS=1,??=0,RANGE=1,HGO=0,OSCINIT=0 */
	OSC->CR = (OSC_CR_OSCEN_MASK | OSC_CR_OSCOS_MASK | OSC_CR_RANGE_MASK);
	/* ICS->C1: CLKS=0,RDIV=2,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
	ICS->C1 = (ICS_C1_CLKS(0x00) | ICS_C1_RDIV(0x02) | ICS_C1_IRCLKEN_MASK);
	while((ICS->S & ICS_S_IREFST_MASK) != 0x00U) { /* Check that the source of the FLL reference clock is the external reference clock. */
	}
	while((ICS->S & 0x0CU) != 0x00U) {    /* Wait until output of the FLL is selected */
	}
#elif (CLOCK_SETUP == 3)
	/* SIM->BUSDIV: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,BUSDIV=1 */
	SIM->BUSDIV = 0x01U;                  /* BUS_CLOCK  = ICSOUTCLK/2 */
	/* Switch to FEI Mode */
	/* ICS->C2: BDIV=0,LP=0 */
	ICS->C2 &= ~(ICS_C2_BDIV(0x07) | ICS_C2_LP_MASK);
	/* OSC->CR: OSCEN=1,??=0,OSCSTEN=0,OSCOS=1,??=0,RANGE=1,HGO=0,OSCINIT=0 */
	OSC->CR = (OSC_CR_OSCEN_MASK | OSC_CR_OSCOS_MASK | OSC_CR_RANGE_MASK);
	/* ICS->C1: CLKS=0,RDIV=2,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
	ICS->C1 = (ICS_C1_CLKS(0x00) | ICS_C1_RDIV(0x02) | ICS_C1_IRCLKEN_MASK);
	while((ICS->S & ICS_S_IREFST_MASK) == 0x00U) { /* Check that the source of the FLL reference clock is the internal reference clock. */
	}
	while((ICS->S & 0x0CU) != 0x00U) {    /* Wait until output of the FLL is selected */
	}
#endif

	SystemClocksUpdate();

	SIM_SOPT = SIM_SOPT_RSTPE_MASK | SIM_SOPT_SWDE_MASK; //NMI deshabilitado, RESET habilitado, SWD habilitado
}

