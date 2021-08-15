#include "fft.h"
#include "global.h"
#include "audio_cfg.h"
#include "gfx.h"
#include <stdint.h>

arm_cfft_instance_f32 fftS;
arm_rfft_fast_instance_f32 fftR;

// out = fft_len
// input = fft_len*2

void fftInit(void) {
	arm_cfft_radix4_init_f32(&fftS, FFT_LEN, 0, 1);
	arm_rfft_fast_init_f32(&fftR, FFT_LEN);
}


CCM_RAM_STATIC volatile float mags[FFT_LEN] = {0};
CCM_RAM_STATIC volatile uint8_t fftMagnitudes[FFT_LEN] = {0};
CCM_RAM_STATIC volatile uint8_t fftMagnitudesOld[FFT_LEN];
CCM_RAM_STATIC volatile uint8_t fftMagnitudesdB[FFT_LEN] = {0};
CCM_RAM_STATIC volatile float FFTbuffer[FFT_LEN*2];

float maxValue;
int maxIndex;

float complexABS(float real, float compl) {
	return sqrtf(real*real+compl*compl);
}

uint32_t	maxFFTidx;
float		maxFFTval;

void fftTest(float *inputF32) {
	arm_cfft_radix4_f32(&fftS, inputF32);
	arm_cmplx_mag_f32(inputF32, mags, FFT_LEN);
	//arm_max_f32(inputF32, FFT_LEN, &maxFFTval, &maxFFTidx);

	volatile float scaled[FFT_LEN] = {0};
	arm_scale_f32(mags, (5.0f), scaled, FFT_LEN);


	//volatile float realFFTout[FFT_LEN] = {0};
	//arm_rfft_fast_f32(&fftR, inputF32, realFFTout, 0);

	//for (int i=0; i<FFT_LEN; i=i+2) {
	//	fftMagnitudes[i/2] = (int)(20*log10f(complexABS(realFFTout[i], realFFTout[i+1])));
	//}


	float magF[FFT_LEN];
	for (int i=0; i<FFT_LEN; i++){
		fftMagnitudes[i] = (int)(scaled[i]);
		fftMagnitudesdB[i] = 20*log10f(fftMagnitudes[i]);

		magF[i] = (float)fftMagnitudesdB[i];
	}

	arm_max_f32(fftMagnitudesdB, FFT_LEN, &maxValue, &maxIndex);
}

/*
uint8_t	fftWFdata[FFT_WF_LEN][FFT_USEFUL_BINS] = {0};
void fftWaterfallShift(void){
	for (int row = (FFT_WF_LEN-1); row > 0; row--){
		for (int col = 0; col < FFT_USEFUL_BINS; col++){
			fftWFdata[row][col] = fftWFdata[row-1][col];
		}
	}


	for (int i=0; i<FFT_USEFUL_BINS; i++)
			fftWFdata[0][i] = fftMagnitudesdB[i];

	//gfxItems[G_FFT_WF].pendUpd = 1;

	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);



}
*/





