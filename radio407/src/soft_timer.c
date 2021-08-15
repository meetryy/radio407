#include "soft_timer.h"
#include "cw.h"

uint32_t preciseTimerCounter = 0;

uint32_t preciseTimerValue(){
	return preciseTimerCounter;
}

void preciseTimerIRQ(){
	if (preciseTimerCounter == ((2 << 32) - 1))
		preciseTimerCounter = 0;
	else
		preciseTimerCounter++;

	cwTimerRoutine();
}
