#pragma once

#include "ili9341.h"
#include "ili9341_gfx.h"
#include "ili9341_font.h"
#include "pins.h"

SPI_HandleTypeDef								hspi1;
#define HSPI_INSTANCE							&hspi1

extern ili9341_t *_screen;

void LCDinit(void);
void LCDdebugText(char* text);
void LCDtestDraw(void);
void LCDdrawIndicator(int isOn);
void LCDdrawFFT(void);
