#pragma once

#include "main.h"
#include "stm32f4xx_hal.h"
#include "pins.h"

#define 	DBG_LCD
#undef 		DBG_USB_UART
#undef 		DBG_UART

#define M_PI           3.14159265358979323846  /* pi */
#define M_2PI          (2.0*3.14159265358979323846)

#define USE_CCM_MEM

#ifndef USE_CCM_MEM
#define CCM_RAM_CODE
#define CCM_RAM_CONST
#define CCM_RAM_STATIC
#endif


#ifdef USE_CCM_MEM
#define CCM_RAM_CODE		__attribute__ ((section(".ccmram")))
#define CCM_RAM_CONST		__attribute__ ((section(".ccmram_constant")))
#define CCM_RAM_STATIC		__attribute__ ((section(".ccmram_static")))
#endif

/*
   .ccmram : {
    . = ALIGN(4);
	*(.ccmram)
    *(.ccmram_constant)
    *(.ccmram_static)
	} > CCMRAM
 */
