#include "hw.h"
#include "spi.h"




void initHardware(void){

	LCDinit();
	spiChangeMode(SPI_MODE_CODEC);
	AICinit();
	spiChangeMode(SPI_MODE_FLASH);
	flashInit();
}


