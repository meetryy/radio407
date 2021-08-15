/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY1_Pin GPIO_PIN_3
#define KEY1_GPIO_Port GPIOE
#define KEY0_Pin GPIO_PIN_4
#define KEY0_GPIO_Port GPIOE
#define LED1_Pin GPIO_PIN_6
#define LED1_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_7
#define LED2_GPIO_Port GPIOA
#define FLASH_CS_Pin GPIO_PIN_0
#define FLASH_CS_GPIO_Port GPIOB
#define KEY_PTT_Pin GPIO_PIN_7
#define KEY_PTT_GPIO_Port GPIOE
#define KEY_PTT_EXTI_IRQn EXTI9_5_IRQn
#define KEY_PADDLE_L_Pin GPIO_PIN_8
#define KEY_PADDLE_L_GPIO_Port GPIOE
#define KEY_PADDLE_L_EXTI_IRQn EXTI9_5_IRQn
#define KEY_PADDLE_R_Pin GPIO_PIN_9
#define KEY_PADDLE_R_GPIO_Port GPIOE
#define KEY_PADDLE_R_EXTI_IRQn EXTI9_5_IRQn
#define ENC1A_Pin GPIO_PIN_10
#define ENC1A_GPIO_Port GPIOE
#define ENC1A_EXTI_IRQn EXTI15_10_IRQn
#define ENC1B_Pin GPIO_PIN_11
#define ENC1B_GPIO_Port GPIOE
#define ENC1B_EXTI_IRQn EXTI15_10_IRQn
#define ENC2A_Pin GPIO_PIN_12
#define ENC2A_GPIO_Port GPIOE
#define ENC2A_EXTI_IRQn EXTI15_10_IRQn
#define ENC2B_Pin GPIO_PIN_13
#define ENC2B_GPIO_Port GPIOE
#define ENC2B_EXTI_IRQn EXTI15_10_IRQn
#define CODEC_CS_Pin GPIO_PIN_14
#define CODEC_CS_GPIO_Port GPIOB
#define LCD_DC_Pin GPIO_PIN_6
#define LCD_DC_GPIO_Port GPIOB
#define LCD_RST_Pin GPIO_PIN_7
#define LCD_RST_GPIO_Port GPIOB
#define LCD_CS_Pin GPIO_PIN_8
#define LCD_CS_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
