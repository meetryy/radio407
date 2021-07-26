#include "fir.h"
#include <stdio.h>
#include <stdint.h>

#include "global.h"
#include "audio_cfg.h"
//#include "math_helper.h"

static float32_t firState1[AUDIO_BUFFER_LEN/2 + NUM_TAPS - 1];
static float32_t firState2[AUDIO_BUFFER_LEN/2 + NUM_TAPS - 1];
arm_fir_instance_f32 S1;
arm_fir_instance_f32 S2;

arm_cfft_instance_f32 fftS;


void fftInit(void) {
	arm_cfft_radix4_init_f32(&fftS, FFT_LEN, 0, 0);
}

float mags[FFT_LEN] = {0};

int maxIndex = 0;
float maxValue = 0;

void fftTest(float *inputF32) {
	arm_cfft_radix4_f32(&fftS, inputF32);
	arm_cmplx_mag_f32(inputF32, mags, FFT_LEN);
	//arm_max_f32(mags, FFT_LEN, &maxValue, &maxIndex);
}

void firInit(void) {
  arm_fir_init_f32(&S1, NUM_TAPS, firCoeffs32, firState1, AUDIO_BUFFER_LEN/2);
  arm_fir_init_f32(&S2, NUM_TAPS, firCoeffs32, firState2, AUDIO_BUFFER_LEN/2);
  return 0;
}

UART_HandleTypeDef huart1;

void firTest(float32_t  *inputF32, float32_t *outputF32, int blockSize, int i) {
  if (i==0)
	  arm_fir_f32(&S1, inputF32, outputF32, blockSize);
	  //convolve(&firCoeffs32, NUM_TAPS, &inputF32, &outputF32);

  if (i==1)
	  //convolve(&firCoeffs32, NUM_TAPS, &inputF32, &outputF32);
	 arm_fir_f32(&S2, inputF32, outputF32, blockSize);

  return 0;
}

void convolve (float *p_coeffs, float p_coeffs_n,
		float *p_in, float *p_out, float n)
{
  int i, j, k;
  double tmp;

  for (k = 0; k < n; k++)  //  position in output
  {
    tmp = 0;

    for (i = 0; i < p_coeffs_n; i++)  //  position in coefficients array
    {
      j = k - i;  //  position in input

      if (j >= 0)  //  bounds check for input buffer
      {
        tmp += p_coeffs [k] * p_in [j];
      }
    }

    p_out [i] = tmp;
  }
}



/*
double coeffs[FILTER_LEN] =
{
  -0.0448093,  0.0322875,   0.0181163,   0.0087615,   0.0056797,
   0.0086685,  0.0148049,   0.0187190,   0.0151019,   0.0027594,
  -0.0132676, -0.0232561,  -0.0187804,   0.0006382,   0.0250536,
   0.0387214,  0.0299817,   0.0002609,  -0.0345546,  -0.0525282,
  -0.0395620,  0.0000246,   0.0440998,   0.0651867,   0.0479110,
   0.0000135, -0.0508558,  -0.0736313,  -0.0529380,  -0.0000709,
   0.0540186,  0.0766746,   0.0540186,  -0.0000709,  -0.0529380,
  -0.0736313, -0.0508558,   0.0000135,   0.0479110,   0.0651867,
   0.0440998,  0.0000246,  -0.0395620,  -0.0525282,  -0.0345546,
   0.0002609,  0.0299817,   0.0387214,   0.0250536,   0.0006382,
  -0.0187804, -0.0232561,  -0.0132676,   0.0027594,   0.0151019,
   0.0187190,  0.0148049,   0.0086685,   0.0056797,   0.0087615,
   0.0181163,  0.0322875,  -0.0448093
};

// array to hold input samples
double insamp[ BUFFER_LEN ];

// FIR init
void firFloatInit( void )
{
    memset( insamp, 0, sizeof( insamp ) );
}

// the FIR filter function
void firFloat( double *coeffs, double *input, double *output,
       int length, int filterLength )
{
    double acc;     // accumulator for MACs
    double *coeffp; // pointer to coefficients
    double *inputp; // pointer to input samples
    int n;
    int k;

    // put the new samples at the high end of the buffer
    memcpy( &insamp[filterLength - 1], input,
            length * sizeof(double) );

    // apply the filter to each input sample
    for ( n = 0; n < length; n++ ) {
        // calculate output n
        coeffp = coeffs;
        inputp = &insamp[filterLength - 1 + n];
        acc = 0;
        for ( k = 0; k < filterLength; k++ ) {
            acc += (*coeffp++) * (*inputp--);
        }
        output[n] = acc;
    }
    // shift input samples back in time for next time
    memmove( &insamp[0], &insamp[length],
            (filterLength - 1) * sizeof(double) );
}

*/


const float firCoeffs32[NUM_TAPS] = {
		   -0.00653603984882394470,
		        -0.01027017922497046100,
		        -0.01384196957956241500,
		        -0.01667045308244168700,
		        -0.01826855346520743500,
		        -0.01832686076204851100,
		        -0.01677261999694612900,
		        -0.01379329265598692100,
		        -0.00981923474449864120,
		        -0.00546630182700430510,
		        -0.00144560770683092190,
		        0.00154677364071832170,
		        0.00294357342068702610,
		        0.00240560599987884280,
		        -0.00011000572595645973,
		        -0.00432517339398102740,
		        -0.00966607142484973700,
		        -0.01533708202871443400,
		        -0.02043461467791843000,
		        -0.02408526756225965300,
		        -0.02558816300974391500,
		        -0.02453951075242026900,
		        -0.02091893475969400900,
		        -0.01512176740238115600,
		        -0.00792881216005365470,
		        -0.00041402873129452254,
		        0.00620005901361850820,
		        0.01072106207667219300,
		        0.01217525010011326900,
		        0.00997876126811177500,
		        0.00406531813519589710,
		        -0.00505093482641940510,
		        -0.01629075648193838800,
		        -0.02810620896123239300,
		        -0.03864979186764946200,
		        -0.04599740406352739700,
		        -0.04839786347369780900,
		        -0.04451680675972549000,
		        -0.03364213513841733000,
		        -0.01582199217549542700,
		        0.00808584505442745680,
		        0.03646328577686212100,
		        0.06707741697802852000,
		        0.09730698322835894300,
		        0.12442376411277335000,
		        0.14589509309911927000,
		        0.15967042043811849000,
		        0.16441630942864346000,
		        0.15967042043811849000,
		        0.14589509309911927000,
		        0.12442376411277335000,
		        0.09730698322835894300,
		        0.06707741697802852000,
		        0.03646328577686212100,
		        0.00808584505442745680,
		        -0.01582199217549542700,
		        -0.03364213513841733000,
		        -0.04451680675972549000,
		        -0.04839786347369780900,
		        -0.04599740406352739700,
		        -0.03864979186764946200,
		        -0.02810620896123239300,
		        -0.01629075648193838800,
		        -0.00505093482641940510,
		        0.00406531813519589710,
		        0.00997876126811177500,
		        0.01217525010011326900,
		        0.01072106207667219300,
		        0.00620005901361850820,
		        -0.00041402873129452254,
		        -0.00792881216005365470,
		        -0.01512176740238115600,
		        -0.02091893475969400900,
		        -0.02453951075242026900,
		        -0.02558816300974391500,
		        -0.02408526756225965300,
		        -0.02043461467791843000,
		        -0.01533708202871443400,
		        -0.00966607142484973700,
		        -0.00432517339398102740,
		        -0.00011000572595645973,
		        0.00240560599987884280,
		        0.00294357342068702610,
		        0.00154677364071832170,
		        -0.00144560770683092190,
		        -0.00546630182700430510,
		        -0.00981923474449864120,
		        -0.01379329265598692100,
		        -0.01677261999694612900,
		        -0.01832686076204851100,
		        -0.01826855346520743500,
		        -0.01667045308244168700,
		        -0.01384196957956241500,
		        -0.01027017922497046100,
		        -0.00653603984882394470,
		        -0.00321978326912657950
};


