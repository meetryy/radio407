#pragma once

#include "audio_cfg.h"
#include "arm_math.h"
#include <stdint.h>


#define FFT_LEN			(AUDIO_BUFFER_LEN/8)
#define FFT_USEFUL_BINS	(FFT_LEN/2)
#define FFT_HZ_PER_BIN	(AUDIO_BUFFER_HALF/FFT_LEN)

//extern float fftBins [FFT_LEN];
//extern float mags[FFT_LEN];

extern volatile uint8_t fftMagnitudesdB[FFT_LEN];
extern volatile uint8_t fftMagnitudes[FFT_LEN];
extern volatile uint8_t fftMagnitudesOld[FFT_LEN];
extern volatile float FFTbuffer[FFT_LEN*2];

extern int maxIndex;
extern float maxValue;

void fftTest(float *inputF32);
void fftInit(void);
void fftWaterfallShift(void);

#define FFT_WF_LEN		30
#define WF_UPD_STAGES	4
