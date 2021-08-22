#include "global.h"
#include "audio_cfg.h"
#include "local_gen.h"
#include "tools.h"
#include "main.h"
#include "arm_math.h"

struct {
	double freq;
	double phase;
	double phaseInc;
} genData[GEN_NR];

void genInit(int genNumber){
	genData[genNumber].freq = 0;
	genData[genNumber].phase = 0;
	genData[genNumber].phaseInc = 0;
}

void genSetFreq(int genNumber, double freqHz){
	genData[genNumber].freq = freqHz;
	genData[genNumber].phaseInc = M_2PI * freqHz * 1.0/(double)AUDIO_FREQ;
}

void genGetValue(float *outBuffer, int16_t blockSize, int genNumber, int signalType){
	//double thisPhase = 0;
	for(int i = 0; i < blockSize; i++){
		genData[genNumber].phase += genData[genNumber].phaseInc;
		while (genData[genNumber].phase > M_2PI)
			genData[genNumber].phase -= M_2PI;


		float thisPhase = (float)genData[genNumber].phase;
		if 		(signalType == GEN_SIN) outBuffer[i] = arm_sin_f32((float)genData[genNumber].phase);
		else if (signalType == GEN_COS) outBuffer[i] = arm_cos_f32((float)genData[genNumber].phase);
	}
}

void genGetValueSinCos(float *outSin, float *outCos, int16_t blockSize, int genNumber){
	//double thisPhase = 0;
	for(int i = 0; i < blockSize; i++){
		genData[genNumber].phase += genData[genNumber].phaseInc;
		while (genData[genNumber].phase > M_2PI)
			genData[genNumber].phase -= M_2PI;

		arm_sin_cos_f32((float)genData[genNumber].phase, &outSin[i], &outCos[i]);
	}
}

