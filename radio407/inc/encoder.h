#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "global.h"

enum encNames {ENC_UPPER, ENC_LOWER, ENC_NR};
typedef struct {
	volatile uint8_t 			phaseState;
	volatile uint8_t 			phaseOldState;
	volatile int					deltaRaw;
	//int					deltaOld;
	volatile int					delta;
	volatile bool 					isReversed;
	volatile const uint16_t			pins[2];
	volatile const GPIO_TypeDef*	port;
	volatile uint8_t				divider;
} encoder_t;

extern encoder_t encoder[ENC_NR];

void encInputRoutine(void);
void encInputCallback(uint16_t GPIO_Pin);

