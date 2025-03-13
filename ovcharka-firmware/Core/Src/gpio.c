/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, BRIDGESLEEP1_Pin|DRVOFF2_Pin|SPI1_SS2_Pin|SPI1_SS3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DIR2_1_Pin|SPI1_SS1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SPI1_SS4_Pin|DIR1_1_Pin|HIZ1_Pin|HIZ2_Pin
                          |DRVOFF1_Pin|BRIDGESLEEP2_Pin|IND_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : nFAULT_L2_Pin nFAULT_R2_Pin ENC1_Z_Pin ENC2_Z_Pin */
  GPIO_InitStruct.Pin = nFAULT_L2_Pin|nFAULT_R2_Pin|ENC1_Z_Pin|ENC2_Z_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : BRIDGESLEEP1_Pin DRVOFF2_Pin */
  GPIO_InitStruct.Pin = BRIDGESLEEP1_Pin|DRVOFF2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : DIR2_1_Pin */
  GPIO_InitStruct.Pin = DIR2_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DIR2_1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI1_SS1_Pin */
  GPIO_InitStruct.Pin = SPI1_SS1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(SPI1_SS1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI1_SS2_Pin SPI1_SS3_Pin */
  GPIO_InitStruct.Pin = SPI1_SS2_Pin|SPI1_SS3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI1_SS4_Pin */
  GPIO_InitStruct.Pin = SPI1_SS4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(SPI1_SS4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DIR1_1_Pin HIZ1_Pin HIZ2_Pin DRVOFF1_Pin
                           BRIDGESLEEP2_Pin IND_LED_Pin */
  GPIO_InitStruct.Pin = DIR1_1_Pin|HIZ1_Pin|HIZ2_Pin|DRVOFF1_Pin
                          |BRIDGESLEEP2_Pin|IND_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : nFAULT_R1_Pin nFAULT_L1_Pin RS485_CTRL_Pin */
  GPIO_InitStruct.Pin = nFAULT_R1_Pin|nFAULT_L1_Pin|RS485_CTRL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_ID_Pin */
  GPIO_InitStruct.Pin = USB_ID_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_ID_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
