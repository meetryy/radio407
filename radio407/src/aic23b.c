#include "aic23b.h"
#include "tools.h"
#include "global.h"
#include "main.h"

SPI_HandleTypeDef			hspi1;
#define AIC_SPI_HANDLE		&hspi1

enum {	AIC_REG_LINEIN_L = 0, AIC_REG_LINEIN_R = 1,
		AIC_REG_HP_L = 2, AIC_REG_HP_R = 3,
		AIC_REG_ANALOG_PATH = 4, AIC_REG_DIGI_PATH = 5,
		AIC_REG_POWER = 6, AIC_REG_FORMAT = 7, AIC_REG_SAMPLERATE = 8,
		AIC_REG_ACTIVATION = 9, AIC_REG_RESET = 15};

bool lineInMute = 0;
bool lineInOn = 0;
uint8_t lineInVol = 0;
uint8_t HPvol = 0;
				
void AICtx(uint8_t addr, uint16_t data){
	uint16_t txData = (data | (addr << 9));
	uint8_t dataToTx[2] = {txData & 0xFF, ((txData >> 8) & 0xFF)};

	HAL_GPIO_WritePin(CODEC_CS_PORT, CODEC_CS_PIN, 0);
		HAL_SPI_Transmit(AIC_SPI_HANDLE, (uint8_t*)dataToTx, 1, 10);
	HAL_GPIO_WritePin(CODEC_CS_PORT, CODEC_CS_PIN, 1);
}

void AICsetLineInMute(bool mute){
	lineInMute = mute;
	AICtx(AIC_REG_LINEIN_L, ((lineInVol & 0x1f) | (lineInMute << 7) | (1 << 8)));
	AICtx(AIC_REG_LINEIN_R, ((lineInVol & 0x1f) | (lineInMute << 7) | (1 << 8)));
}

void AICsetLineVol(uint8_t vol){
	uint8_t newVol = vol;
	if (newVol > 32) newVol = 32;
	uint8_t data = newVol | 0x180;
	lineInVol = newVol;
	AICtx(AIC_REG_LINEIN_L, data); // line left
	AICtx(AIC_REG_LINEIN_R, data);	// line right
}

void AICsetHPVol(uint8_t vol){
	uint8_t newVol = vol;
	if (newVol > 127) newVol = 127;
	if (newVol < 48) newVol = 48;
	HPvol = newVol;
	uint16_t data = newVol | 0x180;
	AICtx(AIC_REG_HP_L, data); // hp left
	AICtx(AIC_REG_HP_R, data);	// hp right
}

void AICsetHPVolPercent(uint8_t percent){
	uint8_t newVol = 48 + 79 * percent / 100;
	HPvol = newVol;
	uint8_t data = newVol | 0x180;
	AICtx(AIC_REG_HP_L, data); 
	AICtx(AIC_REG_HP_R, data);	
}

void AICsetLineVolPercent(uint8_t percent){
	uint16_t newVol = 32 * percent / 100;
	lineInVol = newVol;
	uint8_t data = newVol;// | 0x100; //180
	AICtx(AIC_REG_LINEIN_L, data);
	AICtx(AIC_REG_LINEIN_R, data);	
}

bool DACmute = 0;
void AICmuteDAC(bool mute){
	DACmute = mute;
	uint8_t data = (mute << 3);
	AICtx(AIC_REG_DIGI_PATH, data); // hp left
}

void AICpowerUp(void){
	/*
	0	line
	1	mic
	2	adc
	3	dac
	4	output
	5	osc
	6	clk
	7	power
	8	x
	
	0 = ON!
	*/

	AICtx(AIC_REG_RESET, 0);

		//			line		mic			adc			dac		out			osc			clk			power
	uint8_t data = (0 << 0) | (0 << 1) | (0 << 2) | (0 << 3) | (0 << 4) | (1 << 5) | (1 << 6) | (0 << 7);
	AICtx(AIC_REG_POWER, data);
}

void AICpowerDowm(void){
	uint8_t data = (1 << 7);
	AICtx(AIC_REG_POWER, data); 
}


// digi format
// analog path

enum {AIC_16BIT = 0, AIC_20BIT = 1, AIC_24BIT = 2, AIC_32BIT = 3};
enum {AIC_MSBFIRST = 0, AIC_LSBFIRST = 1, AIC_I2S = 2, AIC_DSP = 3};
enum {AIC_48K = 0, AIC_32K = 6,  AIC_8K = 3};

void AICinit(void){

	HAL_GPIO_WritePin(CODEC_CS_PORT, CODEC_CS_PIN, 1);

	AICtx(AIC_REG_RESET, 0);
		//			line		mic			adc		  dac		  out		osc			clk		 power
	uint8_t data = 	(1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
	AICtx(AIC_REG_POWER, data);
	data = 			(0 << 0) | (0 << 1) | (0 << 2) | (0 << 3) | (0 << 4) | (1 << 5) | (0 << 6) | (0 << 7);
	AICtx(AIC_REG_POWER, data);
	// 						for0					iwl0			lrp			l�swap		ms
	AICtx(AIC_REG_FORMAT, ((AIC_I2S << 0) | (AIC_16BIT << 2)  | (0 << 4) | (0 << 5) | (0 << 6))); // 7
	AICtx(AIC_REG_SAMPLERATE, (AIC_48K << 2));
								// micb		micm		insel		byp		 dac		ste			sta0		sta1	sta2
	AICtx(AIC_REG_ANALOG_PATH, ((0 << 0) | (1 << 1) | (0 << 2) | (0 << 3) | (1 << 4) | (0 << 5) | (1 << 6) | (1 << 7) | (1 << 8)));
							 // adchp	 deemp0		 deemp1		dacm
	AICtx(AIC_REG_DIGI_PATH, ((1 << 0) | (1<< 1) | (1<< 2) | (0 << 3)));

	AICsetLineVolPercent(90); // 0, 1
	AICsetHPVolPercent(90);	// 2, 3

	AICtx(AIC_REG_ACTIVATION, 1); // 9
	AICsetLineInMute(0);
}




