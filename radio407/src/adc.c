#include "adc.h"
#include "global.h"


volatile uint16_t adcDMAdata[ADC_CHANNELS];

adcChannel_t adcCh[ADC_CHANNELS] = {
		[ADC_BUTTONS].LPFalpha = 0.01f,
		[ADC_BUTTONS].ADCmax = (1 << ADC_BIT) - 1.0/0.01f,
		[ADC_VOLTAGE].ADCperUnit = 273.0f,
		[ADC_VOLTAGE].LPFalpha = 0.0001f,
		[ADC_SWR].ADCperUnit = 50.0f,
		[ADC_SWR].LPFalpha = 0.0001f
};

ADC_HandleTypeDef hadc1;

void adcStart(void){
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adcDMAdata[0], ADC_CHANNELS);
}

//filtered_output[i] = α*raw_input[i] + (1-α)*filtered_output[i-1]

void adcSmoothen(void){
	for (int i=0; i<ADC_CHANNELS; i++){
		/*
		adcCh[i].ADCraw = adcDMAdata[i];
		int16_t delta = adcCh[i].ADCraw - adcCh[i].ADCold;
		//adcCh[i].units = 1.0f / (adcCh[i].ADCperUnit / adcCh[i].ADCsmooth);
		//adcCh[i].ADCsmooth = (uint16_t)(adcCh[i].LPFalpha*(float)adcCh[i].ADCraw + (1.0f-adcCh[i].LPFalpha)*(float)adcCh[i].ADCold);
		adcCh[i].ADCsmooth = adcCh[i].ADCold + ((int16_t)(adcCh[i].LPFalpha * (float)delta));
		adcCh[i].test = (int16_t)(delta * adcCh[i].LPFalpha);
		adcCh[i].ADCold = adcCh[i].ADCsmooth;
		*/

		adcCh[i].ADCraw = adcDMAdata[i];              			//read the sensor value using ADC
		adcCh[i].ADCsmooth = (adcCh[i].LPFalpha*adcCh[i].ADCraw) + ((1-adcCh[i].LPFalpha) * adcCh[i].ADCsmooth);  //run the EMA


	}
}


