#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "arm_math.h"
#include "audio_cfg.h"

//extern double firCoeffs32[NUM_TAPS];
#define NUM_TAPS  96

#define FFT_LEN			(AUDIO_BUFFER_LEN/16)
#define FFT_HZ_PER_BIN	(AUDIO_BUFFER_HALF/FFT_LEN)

void firFloat( double *coeffs, double *input, double *output, int length, int filterLength);
void firTest(float32_t  *inputF32, float32_t *outputF32, int blockSize, int i);
void firInit(void);

extern const float firCoeffs32[NUM_TAPS];

extern float fftBins [FFT_LEN];
extern float mags[FFT_LEN];

extern int maxIndex;
extern float maxValue;

void fftTest(float32_t *inputF32);
void fftInit(void);
