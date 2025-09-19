/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define NUM_START (uint32_t) 9999
typedef union {
	uint8_t ALL_SEG;
	struct 
	{
		uint8_t SEG_A	:1;
		uint8_t SEG_B	:1;
		uint8_t SEG_C	:1;
		uint8_t SEG_D	:1;
		uint8_t SEG_E	:1;
		uint8_t SEG_F	:1;
		uint8_t SEG_G	:1;
		uint8_t DP		:1;
	} SEG;
} SEGbit;

typedef struct {
	uint32_t PIN_SEG_A;
	uint32_t PIN_SEG_B;
	uint32_t PIN_SEG_C;
	uint32_t PIN_SEG_D;
	uint32_t PIN_SEG_E;
	uint32_t PIN_SEG_F;
	uint32_t PIN_SEG_G;
	uint32_t PIN_SEG_DP;
	
	GPIO_TypeDef* PORT;
} LED_pin;


char _7seg_code[] = {
	0x3F, // -> 0
	0x06, // -> 1
	0x5B, // -> 2
	0x4F, // -> 3
	0x66, // -> 4
	0x6D, // -> 5
	0x7D, // -> 6
	0x07, // -> 7
	0x7F, // -> 8
	0x6F, // -> 9
};

LED_pin L1 = {
	.PIN_SEG_A = GPIO_PIN_0,
	.PIN_SEG_B = GPIO_PIN_1,
	.PIN_SEG_C = GPIO_PIN_2,
	.PIN_SEG_D = GPIO_PIN_3,
	.PIN_SEG_E = GPIO_PIN_4,
	.PIN_SEG_F = GPIO_PIN_5,
	.PIN_SEG_G = GPIO_PIN_6,
	.PORT			 = GPIOA
};

LED_pin L2 = {
	.PIN_SEG_A = GPIO_PIN_8,
	.PIN_SEG_B = GPIO_PIN_9,
	.PIN_SEG_C = GPIO_PIN_10,
	.PIN_SEG_D = GPIO_PIN_11,
	.PIN_SEG_E = GPIO_PIN_12,
	.PIN_SEG_F = GPIO_PIN_13,
	.PIN_SEG_G = GPIO_PIN_14,
	.PORT			 = GPIOA
};

LED_pin L3 = {
	.PIN_SEG_A = GPIO_PIN_0,
	.PIN_SEG_B = GPIO_PIN_1,
	.PIN_SEG_C = GPIO_PIN_2,
	.PIN_SEG_D = GPIO_PIN_3,
	.PIN_SEG_E = GPIO_PIN_4,
	.PIN_SEG_F = GPIO_PIN_5,
	.PIN_SEG_G = GPIO_PIN_6,
	.PORT			 = GPIOB
};

LED_pin L4 = {
	.PIN_SEG_A = GPIO_PIN_8,
	.PIN_SEG_B = GPIO_PIN_9,
	.PIN_SEG_C = GPIO_PIN_10,
	.PIN_SEG_D = GPIO_PIN_11,
	.PIN_SEG_E = GPIO_PIN_12,
	.PIN_SEG_F = GPIO_PIN_13,
	.PIN_SEG_G = GPIO_PIN_14,
	.PORT			 = GPIOB
};

LED_pin* LED_ARR[] = {&L1, &L2, &L3, &L4};

void LED_put(LED_pin *led, uint8_t num) {
	SEGbit num_split_bit;
	num_split_bit.ALL_SEG = _7seg_code[num%10];
	HAL_GPIO_WritePin(led->PORT, led->PIN_SEG_A, (GPIO_PinState) num_split_bit.SEG.SEG_A);
	HAL_GPIO_WritePin(led->PORT, led->PIN_SEG_B, (GPIO_PinState) num_split_bit.SEG.SEG_B);
	HAL_GPIO_WritePin(led->PORT, led->PIN_SEG_C, (GPIO_PinState) num_split_bit.SEG.SEG_C);
	HAL_GPIO_WritePin(led->PORT, led->PIN_SEG_D, (GPIO_PinState) num_split_bit.SEG.SEG_D);
	HAL_GPIO_WritePin(led->PORT, led->PIN_SEG_E, (GPIO_PinState) num_split_bit.SEG.SEG_E);
	HAL_GPIO_WritePin(led->PORT, led->PIN_SEG_F, (GPIO_PinState) num_split_bit.SEG.SEG_F);
	HAL_GPIO_WritePin(led->PORT, led->PIN_SEG_G, (GPIO_PinState) num_split_bit.SEG.SEG_G);
}
void LED_Display(LED_pin* led[], uint32_t num) {
	for(int8_t idx = 3; idx >= 0; idx--) {
		LED_put(led[idx], num%10);
		num /= 10;
	}
}
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

uint16_t num = NUM_START;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
	
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		LED_Display(LED_ARR, num);
		HAL_Delay(300);
		if(num == 0) {
			num = NUM_START;
		} else {
			num--;
		}
		
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, L1A_Pin|L1B_Pin|L1C_Pin|L1D_Pin
                          |L1E_Pin|L1F_Pin|L1G_Pin|L2A_Pin
                          |L2B_Pin|L2C_Pin|L2D_Pin|L2E_Pin
                          |L2F_Pin|L2G_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, L3A_Pin|L3B_Pin|L3C_Pin|L4C_Pin
                          |L4D_Pin|L4E_Pin|L4F_Pin|L4G_Pin
                          |L3D_Pin|L3E_Pin|L3F_Pin|L3G_Pin
                          |L4A_Pin|L4B_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : L1A_Pin L1B_Pin L1C_Pin L1D_Pin
                           L1E_Pin L1F_Pin L1G_Pin L2A_Pin
                           L2B_Pin L2C_Pin L2D_Pin L2E_Pin
                           L2F_Pin L2G_Pin */
  GPIO_InitStruct.Pin = L1A_Pin|L1B_Pin|L1C_Pin|L1D_Pin
                          |L1E_Pin|L1F_Pin|L1G_Pin|L2A_Pin
                          |L2B_Pin|L2C_Pin|L2D_Pin|L2E_Pin
                          |L2F_Pin|L2G_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : L3A_Pin L3B_Pin L3C_Pin L4C_Pin
                           L4D_Pin L4E_Pin L4F_Pin L4G_Pin
                           L3D_Pin L3E_Pin L3F_Pin L3G_Pin
                           L4A_Pin L4B_Pin */
  GPIO_InitStruct.Pin = L3A_Pin|L3B_Pin|L3C_Pin|L4C_Pin
                          |L4D_Pin|L4E_Pin|L4F_Pin|L4G_Pin
                          |L3D_Pin|L3E_Pin|L3F_Pin|L3G_Pin
                          |L4A_Pin|L4B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
