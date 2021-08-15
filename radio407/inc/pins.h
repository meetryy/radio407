#pragma once

#include "stm32f4xx_hal.h"
#include "global.h"

// LCD PIN ASSIGNMENTS
#define LCD_CS_PORT		GPIOB
#define LCD_CS_PIN		LCD_CS_Pin

#define LCD_DC_PORT		GPIOB
#define LCD_DC_PIN		LCD_DC_Pin

#define	LCD_RST_PORT	GPIOB
#define	LCD_RST_PIN		LCD_RST_Pin

#define	CODEC_CS_PORT	GPIOC
#define	CODEC_CS_PIN	GPIO_PIN_0

//ENCODER PINS
#define	ENC1_PORT		GPIOE
#define	ENC1A_PIN		GPIO_PIN_10
#define	ENC1B_PIN		GPIO_PIN_11

#define	ENC2_PORT		GPIOE
#define	ENC2A_PIN		GPIO_PIN_12
#define	ENC2B_PIN		GPIO_PIN_13

//CW KEY PINS
#define	KEY_L_PORT		GPIOE
#define	KEY_L_PIN		GPIO_PIN_8

#define	KEY_R_PORT		GPIOE
#define	KEY_R_PIN		GPIO_PIN_9

#define	KEY_PTT_PORT	GPIOE
#define	KEY_PTT_PIN		GPIO_PIN_7
