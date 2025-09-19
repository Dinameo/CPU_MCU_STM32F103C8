/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f1xx_hal.h"

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
#define L1A_Pin GPIO_PIN_0
#define L1A_GPIO_Port GPIOA
#define L1B_Pin GPIO_PIN_1
#define L1B_GPIO_Port GPIOA
#define L1C_Pin GPIO_PIN_2
#define L1C_GPIO_Port GPIOA
#define L1D_Pin GPIO_PIN_3
#define L1D_GPIO_Port GPIOA
#define L1E_Pin GPIO_PIN_4
#define L1E_GPIO_Port GPIOA
#define L1F_Pin GPIO_PIN_5
#define L1F_GPIO_Port GPIOA
#define L1G_Pin GPIO_PIN_6
#define L1G_GPIO_Port GPIOA
#define L3A_Pin GPIO_PIN_0
#define L3A_GPIO_Port GPIOB
#define L3B_Pin GPIO_PIN_1
#define L3B_GPIO_Port GPIOB
#define L3C_Pin GPIO_PIN_2
#define L3C_GPIO_Port GPIOB
#define L4C_Pin GPIO_PIN_10
#define L4C_GPIO_Port GPIOB
#define L4D_Pin GPIO_PIN_11
#define L4D_GPIO_Port GPIOB
#define L4E_Pin GPIO_PIN_12
#define L4E_GPIO_Port GPIOB
#define L4F_Pin GPIO_PIN_13
#define L4F_GPIO_Port GPIOB
#define L4G_Pin GPIO_PIN_14
#define L4G_GPIO_Port GPIOB
#define L2A_Pin GPIO_PIN_8
#define L2A_GPIO_Port GPIOA
#define L2B_Pin GPIO_PIN_9
#define L2B_GPIO_Port GPIOA
#define L2C_Pin GPIO_PIN_10
#define L2C_GPIO_Port GPIOA
#define L2D_Pin GPIO_PIN_11
#define L2D_GPIO_Port GPIOA
#define L2E_Pin GPIO_PIN_12
#define L2E_GPIO_Port GPIOA
#define L2F_Pin GPIO_PIN_13
#define L2F_GPIO_Port GPIOA
#define L2G_Pin GPIO_PIN_14
#define L2G_GPIO_Port GPIOA
#define L3D_Pin GPIO_PIN_3
#define L3D_GPIO_Port GPIOB
#define L3E_Pin GPIO_PIN_4
#define L3E_GPIO_Port GPIOB
#define L3F_Pin GPIO_PIN_5
#define L3F_GPIO_Port GPIOB
#define L3G_Pin GPIO_PIN_6
#define L3G_GPIO_Port GPIOB
#define L4A_Pin GPIO_PIN_8
#define L4A_GPIO_Port GPIOB
#define L4B_Pin GPIO_PIN_9
#define L4B_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
