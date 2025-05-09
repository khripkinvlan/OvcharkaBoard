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
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "drv8106.h"
#include "IQmathLib.h"
#include "main_init.h"
#include "ind_led.h"
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

/* USER CODE BEGIN PV */

// uint16_t duty1, duty2, dir1, dir2;
_iq18 test_iq;
servo_iq18_t servo1_g, servo2_g;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  TXOFF; // Turn off transceiver during init

  // Pull down all CS pins of drivers
  HAL_GPIO_WritePin(SPI1_SS1_GPIO_Port, SPI1_SS1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(SPI1_SS2_GPIO_Port, SPI1_SS2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(SPI1_SS3_GPIO_Port, SPI1_SS3_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(SPI1_SS4_GPIO_Port, SPI1_SS4_Pin, GPIO_PIN_SET);
  HAL_Delay(1);

  // Wake up drivers
  HAL_GPIO_WritePin(BRIDGESLEEP1_GPIO_Port, BRIDGESLEEP1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(BRIDGESLEEP2_GPIO_Port, BRIDGESLEEP2_Pin, GPIO_PIN_SET);

  // Turn high nHIZ pins, allowing the driver to switch on pwm command
  HAL_GPIO_WritePin(HIZ1_GPIO_Port, HIZ1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(HIZ2_GPIO_Port, HIZ2_Pin, GPIO_PIN_SET);
  HAL_Delay(1);

  // Write defaults to all bridges in case MCU was reset
  drv8106_reset_blocking(&drv_l1_dd6);
  drv8106_reset_blocking(&drv_r1_dd7);
  drv8106_reset_blocking(&drv_l2_dd8);
  drv8106_reset_blocking(&drv_r2_dd9);

  // Clear faults (since there is power-on-reset fault at start)
  drv8106_clear_fault_blocking(&drv_l1_dd6);
  drv8106_clear_fault_blocking(&drv_r1_dd7);
  drv8106_clear_fault_blocking(&drv_l2_dd8);
  drv8106_clear_fault_blocking(&drv_r2_dd9);

  // read all registers of a driver
  drv8106_read_all_blocking(&drv_l1_dd6);
  drv8106_read_all_blocking(&drv_r1_dd7);
  drv8106_read_all_blocking(&drv_l2_dd8);
  drv8106_read_all_blocking(&drv_r2_dd9);

  // Enable current sensor with gain 10
  drv8106_CSA_enable_g10_blocking(&drv_l1_dd6);
  drv8106_CSA_enable_g10_blocking(&drv_r1_dd7);
  drv8106_CSA_enable_g10_blocking(&drv_l2_dd8);
  drv8106_CSA_enable_g10_blocking(&drv_r2_dd9);

  // Enable bridge to autorecover from most faults
  drv8106_set_fault_autorecovery_blocking(&drv_l1_dd6);
  drv8106_set_fault_autorecovery_blocking(&drv_r1_dd7);
  drv8106_set_fault_autorecovery_blocking(&drv_l2_dd8);
  drv8106_set_fault_autorecovery_blocking(&drv_r2_dd9);

  // Enable drivers via SPI bit
  drv8106_Enable_blocking(&drv_l1_dd6);
  drv8106_Enable_blocking(&drv_r1_dd7);
  drv8106_Enable_blocking(&drv_l2_dd8);
  drv8106_Enable_blocking(&drv_r2_dd9);
  HAL_Delay(1);

  // Init led indication module
  ind_led_init(&ind_led_red, IND_LED_GPIO_Port, IND_LED_Pin, 250, 0);

  // Init stuff for motor control
  init_mtr_ctrl();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
// {
//   if(htim == &htim3){
//     static uint16_t cntr = 0;
//     cntr++;
//     if (cntr >= 3600){
//       HAL_GPIO_TogglePin(IND_LED_GPIO_Port, IND_LED_Pin);
//       cntr = 0;
//     }

//     fault1 = HAL_GPIO_ReadPin(nFAULT_L1_GPIO_Port, nFAULT_L1_Pin);
//     fault2 = HAL_GPIO_ReadPin(nFAULT_R1_GPIO_Port, nFAULT_R1_Pin);
//     fault3 = HAL_GPIO_ReadPin(nFAULT_L2_GPIO_Port, nFAULT_L2_Pin);
//     fault4 = HAL_GPIO_ReadPin(nFAULT_R2_GPIO_Port, nFAULT_R2_Pin);

//     TIM3->CCR1 = duty1;
//     TIM3->CCR2 = duty2;
//     HAL_GPIO_WritePin(DIR1_1_GPIO_Port, DIR1_1_Pin, dir1);   
//     HAL_GPIO_WritePin(DIR2_1_GPIO_Port, DIR2_1_Pin, dir2);   

//   }
  
// }

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
