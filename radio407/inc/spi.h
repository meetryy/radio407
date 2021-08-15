#pragma once 
#include <stdint.h>
#include <stdbool.h>

extern bool spiBusy;


enum spiModes {SPI_MODE_CODEC, SPI_MODE_FLASH};

void spiChangeMode(int mode);


