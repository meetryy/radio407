#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "arm_math.h"
#include "audio_cfg.h"

//extern double firCoeffs32[NUM_TAPS];
#define NUM_TAPS  96

void firFloat( double *coeffs, double *input, double *output, int length, int filterLength);
void firTest(float32_t  *inputF32, float32_t *outputF32, int blockSize, int i);
void firInit(void);

extern const float firCoeffs32[NUM_TAPS];

