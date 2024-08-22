/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include <stdio.h>
#include <string.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config_HSE(uint8_t clock_freq);
void Error_Handler(void);
void TIMER2_INIT(void);
/* USER CODE BEGIN PFP */
#define TRUE 1
#define FALSE 0
#define SYS_CLOCK_FREQ_50_MHZ 50
#define SYS_CLOCK_FREQ_80_MHZ 80
#define SYS_CLOCK_FREQ_120_MHZ 120
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint32_t pulse1_value = 250000; //500Hz
uint32_t pulse2_value = 12500; //1 kHz
uint32_t pulse3_value = 6250; // 2 kHz
uint32_t pulse4_value = 3125; // 4 kHz
uint32_t ccr_content; // Capture and Compare register value
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{


  HAL_Init();


  SystemClock_Config_HSE(SYS_CLOCK_FREQ_50_MHZ);

  TIMER2_INIT();

  if (HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_1) != HAL_OK)
  {
	  Error_Handler();
  }

  if (HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_2) != HAL_OK)
  {
	  Error_Handler();
  }


  if (HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_3) != HAL_OK)
  {
	  Error_Handler();
  }


  if (HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_4) != HAL_OK)
  {
	  Error_Handler();
  }

  HAL_UART_Transmit(&huart2, (uint8_t *)("Hello"), strlen("Hello"), HAL_MAX_DELAY);




  while (1);


}



void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{

	char log[100] = "Hello";

	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		ccr_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, ccr_content + pulse1_value);
		sprintf(log, "Value of ccr_content is: %lu\r\n", ccr_content);
		HAL_UART_Transmit(&huart2, (uint8_t *)("Hello"), strlen("Hello"), HAL_MAX_DELAY);
	}

	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
	{
		ccr_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_2, ccr_content + pulse2_value);

		sprintf(log, "Value of ccr_content is: %lu\r\n", ccr_content);
		HAL_UART_Transmit(&huart2, (uint8_t *)log, strlen(log), HAL_MAX_DELAY);
	}

	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
	{
		ccr_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_3, ccr_content + pulse3_value);
		sprintf(log, "Value of ccr_content is: %lu\r\n", ccr_content);
		HAL_UART_Transmit(&huart2, (uint8_t *)log, strlen(log), HAL_MAX_DELAY);
	}

	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
	{
		ccr_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_4, ccr_content + pulse4_value);
		sprintf(log, "Value of ccr_content is: %lu\r\n", ccr_content);
		HAL_UART_Transmit(&huart2, (uint8_t *)log, strlen(log), HAL_MAX_DELAY);
	}

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config_HSE(uint8_t clock_freq)
	{
		RCC_OscInitTypeDef Osc_Init;
		RCC_ClkInitTypeDef Clock_Init;
	    uint8_t flash_latency=0;

		Osc_Init.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_HSI ;
		Osc_Init.HSEState = RCC_HSE_ON;
		Osc_Init.LSEState = RCC_LSE_ON;
		Osc_Init.HSIState = RCC_HSI_ON;
		Osc_Init.PLL.PLLState = RCC_PLL_ON;
		Osc_Init.PLL.PLLSource = RCC_PLLSOURCE_HSE;

		switch(clock_freq)
		 {
		  case SYS_CLOCK_FREQ_50_MHZ:
			  Osc_Init.PLL.PLLM = 4;
			  Osc_Init.PLL.PLLN = 50;
			  Osc_Init.PLL.PLLP = RCC_PLLP_DIV2;
			  Osc_Init.PLL.PLLQ = 2;
			  //Osc_Init.PLL.PLLR = 2;
			  Clock_Init.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
		                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
			  Clock_Init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			  Clock_Init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			  Clock_Init.APB1CLKDivider = RCC_HCLK_DIV2;
			  Clock_Init.APB2CLKDivider = RCC_HCLK_DIV1;
	          flash_latency = 1;
		     break;

		  case SYS_CLOCK_FREQ_80_MHZ:
			  Osc_Init.PLL.PLLM = 4;
			  Osc_Init.PLL.PLLN = 84;
			  Osc_Init.PLL.PLLP = RCC_PLLP_DIV2;
			  Osc_Init.PLL.PLLQ = 2;
			 // Osc_Init.PLL.PLLR = 2;
			  Clock_Init.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
		                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
			  Clock_Init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			  Clock_Init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			  Clock_Init.APB1CLKDivider = RCC_HCLK_DIV2;
			  Clock_Init.APB2CLKDivider = RCC_HCLK_DIV1;
	          flash_latency = 2;
		     break;

		  case SYS_CLOCK_FREQ_120_MHZ:
			  Osc_Init.PLL.PLLM = 4;
			  Osc_Init.PLL.PLLN = 120;
			  Osc_Init.PLL.PLLP = RCC_PLLP_DIV2;
			  Osc_Init.PLL.PLLQ = 2;
			 //Osc_Init.PLL.PLLR = 2;
			  Clock_Init.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
		                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
			  Clock_Init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			  Clock_Init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			  Clock_Init.APB1CLKDivider = RCC_HCLK_DIV4;
			  Clock_Init.APB2CLKDivider = RCC_HCLK_DIV2;
	          flash_latency = 3;
		     break;

		  default:
		   return ;
		 }

			if (HAL_RCC_OscConfig(&Osc_Init) != HAL_OK)
		{
				Error_Handler();
		}



		if (HAL_RCC_ClockConfig(&Clock_Init, flash_latency) != HAL_OK)
		{
			Error_Handler();
		}


		/*Configure the systick timer interrupt frequency (for every 1 ms) */
		uint32_t hclk_freq = HAL_RCC_GetHCLKFreq();
		HAL_SYSTICK_Config(hclk_freq/1000);

		/**Configure the Systick
		*/
		HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

		/* SysTick_IRQn interrupt configuration */
		HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);



	 }


/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
void TIMER2_INIT(void)
{
	TIM_OC_InitTypeDef tim2OC_init;

	htim2.Instance = TIM2;
	htim2.Init.Period = 0xFFFF;
	htim2.Init.Prescaler = 1; //25 Mhz
	//htim2.Init.Prescaler = 50; //1 Mhz

	if(HAL_TIM_OC_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}

	tim2OC_init.OCMode = TIM_OCMODE_TOGGLE;
	tim2OC_init.Pulse = pulse1_value;
	tim2OC_init.OCNPolarity = TIM_OCNPOLARITY_HIGH; // Controls output control block

	if(HAL_TIM_OC_ConfigChannel(&htim2, &tim2OC_init, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}

	tim2OC_init.Pulse = pulse2_value;
	if(HAL_TIM_OC_ConfigChannel(&htim2, &tim2OC_init, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}

	tim2OC_init.Pulse = pulse3_value;
	if(HAL_TIM_OC_ConfigChannel(&htim2, &tim2OC_init, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}

	tim2OC_init.Pulse = pulse4_value;
	if(HAL_TIM_OC_ConfigChannel(&htim2, &tim2OC_init, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
void GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef ledgpio;
	ledgpio.Pin = GPIO_PIN_5;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&ledgpio);
}



void UART2_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	if ( HAL_UART_Init(&huart2) != HAL_OK )
	{
		//There is a problem
		Error_Handler();
	}


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
