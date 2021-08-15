#include "spi.h"
#include "global.h"


#include <stdbool.h>

SPI_HandleTypeDef				hspi1;

bool spiBusy = 0;

int spiMode = 5;
void spiChangeMode(int mode){
	if (spiMode != mode){
		switch (mode){
		case SPI_MODE_CODEC: {
			if(HAL_SPI_DeInit(&hspi1) != HAL_ERROR){
				hspi1.Instance = SPI1;
				hspi1.Init.Mode = SPI_MODE_MASTER;
				hspi1.Init.Direction = SPI_DIRECTION_2LINES;
				hspi1.Init.DataSize = SPI_DATASIZE_16BIT;
				hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
				hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
				hspi1.Init.NSS = SPI_NSS_SOFT;
				hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
				hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
				hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
				hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
				hspi1.Init.CRCPolynomial = 10;
				if (HAL_SPI_Init(&hspi1) != HAL_OK){
					Error_Handler();
				}
			}
			break;
		}
		case SPI_MODE_FLASH: {
				if(HAL_SPI_DeInit(&hspi1) != HAL_ERROR){
					hspi1.Instance = SPI1;
					hspi1.Init.Mode = SPI_MODE_MASTER;
					hspi1.Init.Direction = SPI_DIRECTION_2LINES;
					hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
					hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
					hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
					hspi1.Init.NSS = SPI_NSS_SOFT;
					hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
					hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
					hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
					hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
					hspi1.Init.CRCPolynomial = 10;
					if (HAL_SPI_Init(&hspi1) != HAL_OK){
						Error_Handler();
					}
				}
				break;
			}
		}


		spiMode = mode;
	}

}
