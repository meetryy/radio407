#pragma once 
#include <stdbool.h>
#include "audio_cfg.h"

#define	DSP_BIT			(16)
#define DSP_BLOCK_SIZE	(AUDIO_BUFFER_HALF/2)

enum {HALF_LOWER, HALF_UPPER};



extern volatile bool dspRingHalf;
extern volatile bool dspProcDone;
extern volatile int16_t audioRxBuffer[AUDIO_BUFFER_LEN];
extern volatile int16_t audioTxBuffer[AUDIO_BUFFER_LEN];
extern int32_t time2;
extern int32_t dspTotalTime;

extern float Ttest;
extern float wttest;
extern uint32_t dspEntries;
extern int dspOverrunCounter;

void dspInit(void);
void dspStartAudio(void);
void dspStopAudio(void);
float getAudioLoad(void);
float getAudioLoadPossible(void);
