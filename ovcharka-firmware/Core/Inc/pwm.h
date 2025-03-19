/*
 * pwm.h
 *
 *  Created on: 28/06//2023
 *      Author: JV4K
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

#endif /* INC_PWM_H_ */

#include <main.h>

typedef struct {
	// Timer handler
	TIM_HandleTypeDef *htim;
	GPIO_TypeDef *dir1_Port;
	int32_t _duty;
	uint32_t dir1_Pin;
	uint16_t maxDuty;
	uint16_t minDuty;
	int8_t dir; // Stores current direction
	uint8_t timerChannel;

// } pwmControl_t;
}__attribute__((packed, aligned(4))) pwmControl_t;

void pwm_initDriver(pwmControl_t *driver, TIM_HandleTypeDef *htim, uint8_t pwmChannel,
		GPIO_TypeDef *dir1_Port, uint32_t dir1_Pin);

void pwm_dutyLimits(pwmControl_t *driver, uint16_t minDuty, uint16_t maxDuty);

void pwm_setSpeed(pwmControl_t *driver, int32_t duty);