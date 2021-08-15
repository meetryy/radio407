#pragma once
#include <stdbool.h>
#include "global.h"

#define SOFT_TIMER_HZ	(10000)
#define _MS				/(SOFT_TIMER_HZ/1000)

#define SOFT_MS(x) (x/(SOFT_TIMER_HZ/1000))

extern uint32_t preciseTimerCounter;


uint32_t preciseTimerValue();
void preciseTimerIRQ();

