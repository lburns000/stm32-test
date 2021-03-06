/* USER CODE BEGIN Header */
/**
  * Using OLED driver library and fonts library that I modified courtesy of Tilen Majerle and Alexander Lutsai
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ssd1306.h"
#include "GPIOController.h"
#include "ball.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
//extern FontDef_t Font11x18;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
void printButtons(uint8_t reg); // For debug
void drawBallAnimation();
void ballControl(uint8_t reg);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t ball[] = {
		0x06, 0x0F, 0x0F, 0x06
};
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
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  SSD1306_Init();
  GPIOController_init();
  SSD1306_GotoXY(23, 25);
  SSD1306_Puts("Welcome", &Font_11x18, 1);
  SSD1306_UpdateScreen();
  HAL_Delay(1000);
  SSD1306_Clear();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  drawBallAnimation();
  SSD1306_Clear();

  uint8_t myButtons = 0x00;
  while (1)
  {
	  myButtons = GPIOController_getButtonState();
	  ballControl(myButtons);
	  HAL_Delay(1);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

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

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PC0 PC1 PC2 PC3
                           PC4 PC5 PC6 PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void printButtons(uint8_t reg) {
	char temp[22];
	sprintf(temp, "Current status: 0x%02x\n", reg);
	HAL_UART_Transmit(&huart2, temp, 21, 10);

	if (GPIOCONTROLLER_BUTTON_ACTION & reg) {
		HAL_UART_Transmit(&huart2, "Action Button Pressed\n", 22, 10);
		SSD1306_GotoXY(112, 22);
		SSD1306_Puts("A", &Font_11x18, 1);
	}
	else {
		SSD1306_GotoXY(112, 22);
		SSD1306_Puts(" ", &Font_11x18, 1);
	}

	if (GPIOCONTROLLER_BUTTON_SECONDARY & reg) {
		HAL_UART_Transmit(&huart2, "Secondary Button Pressed\n", 25, 10);
		SSD1306_GotoXY(96, 22);
		SSD1306_Puts("B", &Font_11x18, 1);
	}
	else {
		SSD1306_GotoXY(96, 22);
		SSD1306_Puts(" ", &Font_11x18, 1);
	}

	if (GPIOCONTROLLER_BUTTON_UP & reg) {
		HAL_UART_Transmit(&huart2, "UP Button Pressed\n", 18, 10);
		SSD1306_GotoXY(32, 0);
		SSD1306_Puts("UP", &Font_11x18, 1);
	}
	else {
		SSD1306_GotoXY(32,0);
		SSD1306_Puts("  ", &Font_11x18, 1);
	}

	if (GPIOCONTROLLER_BUTTON_RIGHT & reg) {
		HAL_UART_Transmit(&huart2, "RIGHT Button Pressed\n", 21, 10);
		SSD1306_GotoXY(64, 22);
		SSD1306_Puts("RT", &Font_11x18, 1);
	}
	else {
		SSD1306_GotoXY(64, 22);
		SSD1306_Puts("  ", &Font_11x18, 1);
	}

	if (GPIOCONTROLLER_BUTTON_DOWN & reg) {
		HAL_UART_Transmit(&huart2, "DOWN Button Pressed\n", 20, 10);
		SSD1306_GotoXY(32, 45);
		SSD1306_Puts("DN", &Font_11x18, 1);
	} else {
		SSD1306_GotoXY(32, 45);
		SSD1306_Puts("  ", &Font_11x18, 1);
	}

	if (GPIOCONTROLLER_BUTTON_LEFT & reg) {
		HAL_UART_Transmit(&huart2, "LEFT Button Pressed\n", 20, 10);
		SSD1306_GotoXY(0, 22);
		SSD1306_Puts("LT", &Font_11x18, 1);
	} else {
		SSD1306_GotoXY(0, 22);
		SSD1306_Puts("  ", &Font_11x18, 1);
	}

	SSD1306_UpdateScreen();
}

void drawBallAnimation() {
	ball_init();
	for (int x = 2; x + 4 <= WIDTH - 3; x += 4) {
		ball_setPosition(x, HEIGHT >> 1);
		ball_draw();
		SSD1306_UpdateScreen();
		HAL_Delay(50);
	}
	for (int x = WIDTH - 3; x - 4 >= 0; x -= 4) {
		ball_setPosition(x, HEIGHT >> 1);
		ball_draw();
		SSD1306_UpdateScreen();
		HAL_Delay(50);
	}
}

void ballControl(uint8_t reg) {
	int x = ball_getX();
	int y = ball_getY();

	if (GPIOCONTROLLER_BUTTON_UP & reg) {
		HAL_UART_Transmit(&huart2, "UP Button Pressed\n", 18, 10);
		if (y - 4 >= 2) {
			y -= 4;
		}
	}
	if (GPIOCONTROLLER_BUTTON_RIGHT & reg) {
		HAL_UART_Transmit(&huart2, "RIGHT Button Pressed\n", 21, 10);
		if (x + 4 < WIDTH - 2) {
			x += 4;
		}
	}
	if (GPIOCONTROLLER_BUTTON_DOWN & reg) {
		HAL_UART_Transmit(&huart2, "DOWN Button Pressed\n", 20, 10);
		if (y + 4 < HEIGHT - 2) {
			y += 4;
		}
	}
	if (GPIOCONTROLLER_BUTTON_LEFT & reg) {
		HAL_UART_Transmit(&huart2, "LEFT Button Pressed\n", 20, 10);
		if (x - 4 >= 2) {
			x -= 4;
		}
	}

	ball_setPosition(x, y);
	ball_draw();
	SSD1306_UpdateScreen();
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

#ifdef  USE_FULL_ASSERT
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
