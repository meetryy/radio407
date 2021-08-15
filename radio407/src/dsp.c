#include "global.h"
#include "dsp.h"
#include "agc.h"
#include "fir.h"
#include "audio_cfg.h"
#include "local_gen.h"
#include "tools.h"
#include "gfx.h"
#include "fft.h"

#include <stdbool.h>
volatile bool dspRingHalf = HALF_LOWER;
volatile bool dspProcDone = 0;

DMA_HandleTypeDef hdma_spi2_tx;
I2S_HandleTypeDef hi2s2;


void dspInit(void){
	 DMA_HandleTypeDef *hdma = &hdma_spi2_tx;
	 hdma->Instance->CR  |= DMA_IT_HT | DMA_IT_TC;

	dspRingHalf = HALF_LOWER;
	dspProcDone = 0;
	AudioAgc_SetupAgcWdsp(48000, 0);
	AudioAgc_AgcWdsp_Init();

	debugPrint("dspInit");

	genInit(GEN_F0);
	genSetFreq(GEN_F0, 3100.0);
	genInit(GEN_F1);
	genSetFreq(GEN_F1, 3100.0);

}



void dspStartAudio(void){
	HAL_I2SEx_TransmitReceive_DMA(&hi2s2, (uint16_t*)audioTxBuffer, (uint16_t*)audioRxBuffer, AUDIO_BUFFER_LEN);
}

void dspStopAudio(void){
	HAL_I2S_DMAStop(&hi2s2);
}

volatile int16_t audioRxBuffer[AUDIO_BUFFER_LEN] = {0};
volatile int16_t audioTxBuffer[AUDIO_BUFFER_LEN] = {0};
int32_t dspStartTime = 0;
int32_t dspTotalTime = 0;

UART_HandleTypeDef huart1;

#define	Lch	(0)
#define Rch	(1)

char txt[64];

CCM_RAM_STATIC volatile float INbuffer[2][DSP_BLOCK_SIZE];
CCM_RAM_STATIC volatile float OUTbuffer[2][DSP_BLOCK_SIZE];

int16_t *ptrToRxArray;
int16_t *ptrToTxArray;

void bufferDeserialize(void){

	ptrToRxArray = (audioRxBuffer + (AUDIO_BUFFER_LEN/2 * (dspRingHalf == HALF_LOWER)));
	ptrToTxArray = (audioTxBuffer + (AUDIO_BUFFER_LEN/2 * (dspRingHalf == HALF_LOWER)));

	// L R L R to [LL] [RR]
	for (int i = 0; i < AUDIO_BUFFER_LEN/2; i++){
		if (i%2==0) INbuffer[Lch][i/2] = (float)(*(ptrToRxArray+i)) / (float)(1 << DSP_BIT);
		else 		INbuffer[Rch][i/2] = (float)(*(ptrToRxArray+i)) / (float)(1 << DSP_BIT);
	}
}

bool bypassDSP = 0;

void bufferSerialize(void){
	// [LL] [RR] to L R L R
	for (int i = 0; i < AUDIO_BUFFER_HALF; i++){
		if (i%2!=0)  *(ptrToTxArray+i) =  (int16_t)(OUTbuffer[Lch][i/2] * (float)(1 << DSP_BIT));
		else 		 *(ptrToTxArray+i) =  (int16_t)(OUTbuffer[Rch][i/2] * (float)(1 << DSP_BIT));
	}

	if (bypassDSP){
		for (int i = 0; i < AUDIO_BUFFER_HALF; i++){
			OUTbuffer[Lch][i] = INbuffer[Lch][i];
			OUTbuffer[Rch][i] = INbuffer[Rch][i];
		}
	}
}


#define FREQ_SHIFT_UP 0
static void FreqShift_QuarterFs(float32_t* I_buffer, float32_t* Q_buffer, int16_t blockSize, int16_t dir)
{
    /*
     *
     * Shift Down (shift == 1) => i = Q, q = I      *
     * [moves receive frequency to the right in the spectrum display]
     *
     * Shift Up   (shift == 0) => q = I, q = Q
     * [moves receive frequency to the right in the spectrum display]
     *
     */

    float32_t* i_buffer = dir == FREQ_SHIFT_UP? I_buffer : Q_buffer;
    float32_t* q_buffer = dir == FREQ_SHIFT_UP? Q_buffer : I_buffer;

    for(int i = 0; i < blockSize; i += 4)
    {
        float32_t hh1 = q_buffer[i + 1];
        float32_t hh2 = - i_buffer[i + 1];
        i_buffer[i + 1] = hh1;
        q_buffer[i + 1] = hh2;
        hh1 = - i_buffer[i + 2];
        hh2 = - q_buffer[i + 2];
        i_buffer[i + 2] = hh1;
        q_buffer[i + 2] = hh2;
        hh1 = - q_buffer[i + 3];
        hh2 = i_buffer[i + 3];
        i_buffer[i + 3] = hh1;
        q_buffer[i + 3] = hh2;
    }
}


float inputGain = 1.0f;
uint32_t dspEntries = 0;

void dspProc(void){
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
	static double wt;
	static double wt2;

	float F = 2700/2; // Hz
	float F2 = 8000; // Hz
	double WTincrement = 2.0 * M_PI * F * 1.0/(double)AUDIO_FREQ;
	double WTincrement2 = 2.0 * M_PI * F2 * 1.0/(double)AUDIO_FREQ;

	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, dspRingHalf == HALF_LOWER);
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, dspRingHalf == HALF_UPPER);

	if (!dspProcDone){
		dspEntries++;

		dspStartTime = preciseTimerValue();

		bufferDeserialize();

		// ======= SCALING ========
		float LnputGain = 5.0f;
		float RnputGain = 5.0f;
		static float LbufferScaled[DSP_BLOCK_SIZE];
		static float RbufferScaled[DSP_BLOCK_SIZE];

		arm_scale_f32(INbuffer[Lch], LnputGain, LbufferScaled, DSP_BLOCK_SIZE);
		arm_scale_f32(INbuffer[Rch], RnputGain, RbufferScaled, DSP_BLOCK_SIZE);


		// ======= FREQ SHIFT ========
		static float Lshifted[DSP_BLOCK_SIZE];
		static float Rshifted[DSP_BLOCK_SIZE];

		//stageInL = LbufferScaled;
		//stageInR = RbufferScaled;
		//stageOutL = Lshifted;
		//stageOutR = Rshifted;

		FreqShift_QuarterFs(LbufferScaled, RbufferScaled, DSP_BLOCK_SIZE, 0);
		arm_copy_f32(LbufferScaled, Lshifted, DSP_BLOCK_SIZE);
		arm_copy_f32(RbufferScaled, Rshifted, DSP_BLOCK_SIZE);

		// ======= FIR FILTER ========
		static volatile float Lfiltered[DSP_BLOCK_SIZE];
		static volatile float Rfiltered[DSP_BLOCK_SIZE];
		firTest(Lshifted, Lfiltered, DSP_BLOCK_SIZE, 0);
		firTest(Rshifted, Rfiltered, DSP_BLOCK_SIZE, 1);

		// ======= LOCAL OSC ========
		float sinArr[DSP_BLOCK_SIZE];
		float cosArr[DSP_BLOCK_SIZE];
		genGetValue(sinArr, DSP_BLOCK_SIZE, GEN_F0, GEN_SIN);
		genGetValue(cosArr, DSP_BLOCK_SIZE, GEN_F1, GEN_COS);

		// ======= MIXER ========
		float mix2OutSin[DSP_BLOCK_SIZE];
		float mix2OutCos[DSP_BLOCK_SIZE];

		arm_mult_f32(sinArr, Lfiltered, mix2OutSin, DSP_BLOCK_SIZE);
		arm_mult_f32(cosArr, Rfiltered, mix2OutCos, DSP_BLOCK_SIZE);

		float demodResultBuffer[DSP_BLOCK_SIZE];
		arm_add_f32(mix2OutSin, mix2OutCos, demodResultBuffer, DSP_BLOCK_SIZE);

		for (int i = 0; i < DSP_BLOCK_SIZE; i++){
				OUTbuffer[Lch][i] = demodResultBuffer[i];//*3.0;
				OUTbuffer[Rch][i] = demodResultBuffer[i];//*3.0;
		}



		//genGetValue(LbufferOUT, DSP_BLOCK_SIZE, GEN_F0, GEN_SIN);
		//genGetValue(RbufferOUT, DSP_BLOCK_SIZE, GEN_F1, GEN_COS);

		//debugPrint("%f", LbufferOUT[0]);


		//for (int i = 0; i < DSP_BLOCK_SIZE; i++){
		//	LbufferOUT[i] = 1;
		//	LbufferOUT[i] = 0;
		//}


		// FFT
		for (int i = 0; i <FFT_LEN*2; i=i+2){
			FFTbuffer[i] = INbuffer[Lch][i/2];
			FFTbuffer[i+1] = 0;
		}
		fftTest(FFTbuffer);
		//gfxItems[G_FFT_BINS].pendUpd = 1;




		bufferSerialize();

		dspTotalTime = preciseTimerValue() - dspStartTime;
		dspProcDone = 1;
	}

}

float getAudioLoad(void){
	static float audioLoad = 0;
	float thisBufMs = ((float)dspTotalTime/10.0f); // tim7 = 10kHz -> /10 = ms
	float allBufMs = (AUDIO_BUFFER_HALF_MS);
	audioLoad = (thisBufMs/allBufMs*100.0f);
	//debugPrint("%.0f %.0f", thisBufMs, AUDIO_BUFFER_HALF_MS);
	return audioLoad;
}

float getAudioLoadPossible(void){
	return (getAudioLoad()*2);
}


void HAL_I2SEx_TxRxCpltCallback(I2S_HandleTypeDef *hi2s){
	  dspRingHalf = HALF_LOWER;
	  dspProcDone = 0;
}

void HAL_I2SEx_TxRxHalfCpltCallback(I2S_HandleTypeDef *hi2s){
	  dspRingHalf = HALF_UPPER;
	  dspProcDone = 0;
}
