#pragma once
#include <stdint.h>
#include <stdbool.h>

enum mods{MOD_LSB, MOD_USB, MOD_CW, MOD_CWN, MOD_AM, MOD_FM, MOD_NR};
enum vfos{VFO_A, VFO_B, VFO_NR};

typedef struct{
	uint32_t	vfoFreqHz[2];
	bool		vfoCurrent;
	int			vfoStepHz;
	int			vfoStepFastHz;

	int			modulation[2];
	int			filter[2];
	bool		txState;
	float		sMeterdBm;
	float		battVoltage;
} radioState_t;

extern radioState_t radio;
