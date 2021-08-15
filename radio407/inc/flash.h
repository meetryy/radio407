#pragma once
#include <stdint.h>



typedef struct{
	uint32_t	ID;
	uint8_t		UniqID[8];
	uint16_t	PageSize;
	uint32_t	PageCount;
	uint32_t	SectorSize;
	uint32_t	SectorCount;
	uint32_t	BlockSize;
	uint32_t	BlockCount;
	uint32_t	CapacityInKiloByte;
	uint8_t		StatusRegister1;
	uint8_t		StatusRegister2;
	uint8_t		StatusRegister3;
	uint8_t		Lock;
	uint8_t		jM, jID, jC;
} flash_t;


extern flash_t flash;

void 		flashInit(void);
uint32_t 	flashReadID(void);
uint32_t 	flashBlockSize(void);

void 		flashReadUID(void);
void 		flashReadJEDEC(void);



