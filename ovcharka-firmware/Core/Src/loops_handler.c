#include "loops_handler.h"

uint16_t irq_counter9k, irq_counter250;

uint8_t fault1, fault2, fault3, fault4, debug_mode;

float cur_set_1, cur_set2, vel_set_1, vel_set_2;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (system_enabled)
    {
        // if (!irq_counter9k)
        // {
        //     servo_iq18_currentLoop(&servo1_g, current[0]);
        // }
        // else
        // {
        //     servo_iq18_currentLoop(&servo2_g, current[1]);
        // }

        // irq_counter9k = !irq_counter9k;
        
        servo_iq18_currentLoop(&servo1_g, current[0]);
        servo_iq18_currentLoop(&servo2_g, current[1]);

        irq_counter250++;

        if (irq_counter250 == 36)
        {
            // encoder_updatePosition_iq18(&servo1_g.encoder);
	        // encoder_updateVelocity_qep_iq18(&servo1_g.encoder);
            servo_iq18_velocityLoop(&servo1_g);
            fault1 = HAL_GPIO_ReadPin(nFAULT_L1_GPIO_Port, nFAULT_L1_Pin);
            fault2 = HAL_GPIO_ReadPin(nFAULT_R1_GPIO_Port, nFAULT_R1_Pin);
            fault3 = HAL_GPIO_ReadPin(nFAULT_L2_GPIO_Port, nFAULT_L2_Pin);
            fault4 = HAL_GPIO_ReadPin(nFAULT_R2_GPIO_Port, nFAULT_R2_Pin);
        }

        if (irq_counter250 == 72)
        {
            // encoder_updatePosition_iq18(&servo2_g.encoder);
	        // encoder_updateVelocity_qep_iq18(&servo2_g.encoder);
            servo_iq18_velocityLoop(&servo2_g);
            irq_counter250 = 0;

            if(debug_mode == 1){
                servo_iq18_controlCurrent(&servo1_g, cur_set_1);
                servo_iq18_controlCurrent(&servo2_g, cur_set2);
            }

            if(debug_mode == 2){
                servo_iq18_controlVelocity(&servo1_g, _IQ18(vel_set_1));
                servo_iq18_controlVelocity(&servo2_g, _IQ18(vel_set_2));
            }

            
            
        }
    }
    else
    {
        TIM3->CCR1 = 0;
        TIM3->CCR2 = 0;
        servo_iq18_reset(&servo1_g);
        servo_iq18_reset(&servo2_g);
    }
    if (reset_flag)
    {
        servo_iq18_reset(&servo1_g);
        servo_iq18_reset(&servo2_g);
    }
}