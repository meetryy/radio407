#include "radio_state.h"
#include "tools.h"
#include "global.h"
#include "main.h"



radioState_t radio = {
		.vfoFreqHz[VFO_A] = 7040888,
		.vfoFreqHz[VFO_B] = 14100888,
		.modulation[VFO_A] = MOD_LSB,
		.modulation[VFO_B] = MOD_USB,
		.vfoCurrent = VFO_A,
		.battVoltage = 13.8f,
		.txState = 0,
		.vfoStepHz = 1,
		.vfoStepFastHz = 1000,
};


