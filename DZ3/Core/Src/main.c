/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "string.h"
#include "inttypes.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
struct info {
	char str[50];
	uint32_t uint32;
	float flt;
};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define FLASH_USER_SECTOR	FLASH_SECTOR_7
#define FLASH_USER_START_ADDR   0x08060000


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint32_t sectorError = 0xFFFFFFFFU;
struct info userInfo = {"abcdef", 123456789, 23.456};
struct info readInfo = {0};
uint32_t sizeOfSctruct;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
HAL_StatusTypeDef WriteFlash();
void readFlash(struct info* readInfo);
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
  HAL_Delay(1000);
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */





  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  if (!HAL_GPIO_ReadPin(BTN_GPIO_Port, BTN_Pin))
	  {
		  WriteFlash();
		  readFlash(&readInfo);
	  }
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : BTN_Pin */
  GPIO_InitStruct.Pin = BTN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BTN_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
HAL_StatusTypeDef WriteFlash()
{
	sizeOfSctruct = sizeof(userInfo);
	HAL_StatusTypeDef status = 0;

	FLASH_EraseInitTypeDef erase_struct = {0};
	erase_struct.Sector = FLASH_USER_SECTOR;
	erase_struct.NbSectors = 1;
	erase_struct.TypeErase = FLASH_TYPEERASE_SECTORS;
	erase_struct.VoltageRange = FLASH_VOLTAGE_RANGE_3;

	HAL_UART_Transmit(&huart2, (uint8_t*)"UNLOCK START\r\n", strlen("UNLOCK START\r\n"), HAL_MAX_DELAY);
	status = HAL_FLASH_Unlock();
	if (status)
	{
	  HAL_UART_Transmit(&huart2, (uint8_t*)"UNLOCK ERROR\r\n", strlen("UNLOCK ERROR\r\n"), HAL_MAX_DELAY);
	  return status;
	}

	HAL_UART_Transmit(&huart2, (uint8_t*)"ERASE START\r\n", strlen("ERASE START\r\n"), HAL_MAX_DELAY);
	status = HAL_FLASHEx_Erase(&erase_struct, &sectorError);
	if (status)
	{
	  HAL_UART_Transmit(&huart2, (uint8_t*)"ERASE ERROR\r\n", strlen("ERASE ERROR\r\n"), HAL_MAX_DELAY);
	  return status;
	}

	HAL_UART_Transmit(&huart2, (uint8_t*)"PROGRAM START\r\n", strlen("PROGRAM START\r\n"), HAL_MAX_DELAY);

	uint8_t* ptr = (uint8_t*) &userInfo;
	for (int i = 0; i < sizeOfSctruct; i++)
	{
	  status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, FLASH_USER_START_ADDR+i, ptr[i]);
	  if (status)
	  {
		  HAL_UART_Transmit(&huart2, (uint8_t*)"PROGRAM ERROR\r\n", strlen("PROGRAM ERROR\r\n"), HAL_MAX_DELAY);
		  return status;
	  }
	}

	HAL_UART_Transmit(&huart2, (uint8_t*)"LOCK START\r\n", strlen("LOCK START\r\n"), HAL_MAX_DELAY);
	status = HAL_FLASH_Lock();
	if (status)
	{
	  HAL_UART_Transmit(&huart2, (uint8_t*)"LOCK ERROR\r\n", strlen("LOCK ERROR\r\n"), HAL_MAX_DELAY);
	  return status;
	}

	return status;
}

void readFlash(struct info* readInfo)
{
	char buf[50];

	memcpy(readInfo, (uint32_t*)FLASH_USER_START_ADDR, sizeOfSctruct);

	HAL_UART_Transmit(&huart2, (uint8_t*)strcat(readInfo->str, "\r\n"), strlen(readInfo->str), HAL_MAX_DELAY);
	snprintf(buf, sizeof(buf), "%"PRIu32"\r\n%.2f\r\n", readInfo->uint32, readInfo->flt);
	HAL_UART_Transmit(&huart2, (uint8_t*) buf, strlen(buf), HAL_MAX_DELAY);
}
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
