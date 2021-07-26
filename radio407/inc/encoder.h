#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "global.h"

enum encNames {ENC_UPPER, ENC_LOWER, ENC_NR};
typedef struct {
	uint8_t 			phaseState;
	uint8_t 			phaseOldState;
	int					deltaRaw;
	//int					deltaOld;
	int					delta;
	bool 				isReversed;
	const uint16_t		pins[2];
	const GPIO_TypeDef*	port;
	uint8_t				divider;
} encoder_t;

extern encoder_t encoder[ENC_NR];

void encInputRoutine(void);
