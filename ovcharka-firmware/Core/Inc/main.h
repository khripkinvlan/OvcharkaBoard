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
#include <string.h>

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
#define nFAULT_L2_Pin GPIO_PIN_0
#define nFAULT_L2_GPIO_Port GPIOC
#define nFAULT_R2_Pin GPIO_PIN_1
#define nFAULT_R2_GPIO_Port GPIOC
#define BRIDGESLEEP1_Pin GPIO_PIN_2
#define BRIDGESLEEP1_GPIO_Port GPIOC
#define DRVOFF2_Pin GPIO_PIN_3
#define DRVOFF2_GPIO_Port GPIOC
#define DIR2_1_Pin GPIO_PIN_1
#define DIR2_1_GPIO_Port GPIOA
#define CS2_Pin GPIO_PIN_2
#define CS2_GPIO_Port GPIOA
#define CS1_Pin GPIO_PIN_3
#define CS1_GPIO_Port GPIOA
#define SPI1_SS1_Pin GPIO_PIN_4
#define SPI1_SS1_GPIO_Port GPIOA
#define SPI1_SS2_Pin GPIO_PIN_4
#define SPI1_SS2_GPIO_Port GPIOC
#define SPI1_SS3_Pin GPIO_PIN_5
#define SPI1_SS3_GPIO_Port GPIOC
#define SPI1_SS4_Pin GPIO_PIN_0
#define SPI1_SS4_GPIO_Port GPIOB
#define DIR1_1_Pin GPIO_PIN_1
#define DIR1_1_GPIO_Port GPIOB
#define HIZ1_Pin GPIO_PIN_2
#define HIZ1_GPIO_Port GPIOB
#define HIZ2_Pin GPIO_PIN_11
#define HIZ2_GPIO_Port GPIOB
#define DRVOFF1_Pin GPIO_PIN_12
#define DRVOFF1_GPIO_Port GPIOB
#define BRIDGESLEEP2_Pin GPIO_PIN_13
#define BRIDGESLEEP2_GPIO_Port GPIOB
#define nFAULT_R1_Pin GPIO_PIN_14
#define nFAULT_R1_GPIO_Port GPIOB
#define nFAULT_L1_Pin GPIO_PIN_15
#define nFAULT_L1_GPIO_Port GPIOB
#define PWM1_Pin GPIO_PIN_6
#define PWM1_GPIO_Port GPIOC
#define PWM2_Pin GPIO_PIN_7
#define PWM2_GPIO_Port GPIOC
#define ENC1_Z_Pin GPIO_PIN_8
#define ENC1_Z_GPIO_Port GPIOC
#define ENC2_Z_Pin GPIO_PIN_9
#define ENC2_Z_GPIO_Port GPIOC
#define ENC1_CH1_Pin GPIO_PIN_8
#define ENC1_CH1_GPIO_Port GPIOA
#define ENC1_CH2_Pin GPIO_PIN_9
#define ENC1_CH2_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define ENC2_CH1_Pin GPIO_PIN_15
#define ENC2_CH1_GPIO_Port GPIOA
#define ENC2_CH2_Pin GPIO_PIN_3
#define ENC2_CH2_GPIO_Port GPIOB
#define IND_LED_Pin GPIO_PIN_4
#define IND_LED_GPIO_Port GPIOB
#define RS485_CTRL_Pin GPIO_PIN_5
#define RS485_CTRL_GPIO_Port GPIOB
#define ENC1_CH1_F_Pin GPIO_PIN_8
#define ENC1_CH1_F_GPIO_Port GPIOB
#define ENC2_CH1_F_Pin GPIO_PIN_9
#define ENC2_CH1_F_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
