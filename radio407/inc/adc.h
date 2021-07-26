#pragma once
#include <stdint.h>

//#define ADC_CHANNELS	3
#define ADC_BIT			12

enum adcChNames {ADC_BUTTONS, ADC_VOLTAGE, ADC_SWR, ADC_CHANNELS};

typedef struct {
	uint16_t	ADCold;
	uint16_t	ADCraw;
	uint16_t	ADCsmooth;
	uint16_t	ADCmax;
	float		ADCperUnit;
	float		units;
	float		LPFalpha;
	int16_t	test;
} adcChannel_t;


extern adcChannel_t adcCh[ADC_CHANNELS];

void adcStart(void);
void adcSmoothen(void);

