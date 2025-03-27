#include "loops_handler.h"

uint16_t irq_counter250;

uint8_t fault1, fault2, fault3, fault4, loops_op_mode, prev_control_mode;

float cur_debug_set_1, cur_debug_set_2, vel_debug_set_1, vel_debug_set_2, ang_debug_set_1, ang_debug_set_2;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM3){

        if ((get_crc_success_rate() < 50) && !loops_op_mode){
            system_enabled = 0;
            comms_fault_flag = 1;
        } else {
            comms_fault_flag = 0;
        }

        // Check if control mode was changed
        if(control_mode != prev_control_mode){
            TIM3->CCR1 = 0;
            TIM3->CCR2 = 0;
            servo_iq18_reset(&servo1_g);
            servo_iq18_reset(&servo2_g);
            prev_control_mode = control_mode;
        }

        if (system_enabled){
            servo_iq18_currentLoop(&servo1_g, current[0]);
            servo_iq18_currentLoop(&servo2_g, current[1]);
        }
    
        irq_counter250++;
    
        if (irq_counter250 == 36)
        {
            encoder_updatePosition_iq18(&servo1_g.encoder);
            encoder_updateVelocity_qep_iq18(&servo1_g.encoder);
            if (system_enabled){
                servo_iq18_velocityLoop(&servo1_g);
                ind_led_set_opmode(&ind_led_red, BLINK_1HZ);
            }
            
            fault1 = HAL_GPIO_ReadPin(nFAULT_L1_GPIO_Port, nFAULT_L1_Pin);
            fault2 = HAL_GPIO_ReadPin(nFAULT_R1_GPIO_Port, nFAULT_R1_Pin);
            fault3 = HAL_GPIO_ReadPin(nFAULT_L2_GPIO_Port, nFAULT_L2_Pin);
            fault4 = HAL_GPIO_ReadPin(nFAULT_R2_GPIO_Port, nFAULT_R2_Pin);

            if(!(fault1 && fault2 && fault3 && fault4)){
                system_enabled = 0;
                brg_fault_flag = 1;
            } else{
                brg_fault_flag = 0;
            }
            ind_led_handler(&ind_led_red);
        }
    
        if (irq_counter250 == 72)
        {
            encoder_updatePosition_iq18(&servo2_g.encoder);
            encoder_updateVelocity_qep_iq18(&servo2_g.encoder);
            if (system_enabled){
                servo_iq18_velocityLoop(&servo2_g);
            }
            
            irq_counter250 = 0;
    
            // TODO: Write a switch for debug and operation
    
            switch (loops_op_mode)
            {
            case 0:
                if(!control_mode){
                    _iq18 comms_vel1 = (_iq18)data_ctrl.velocity_1 << 9;
                    _iq18 comms_vel2 = (_iq18)data_ctrl.velocity_2 << 9;
                    servo_iq18_controlVelocity(&servo1_g, comms_vel1);
                    servo_iq18_controlVelocity(&servo2_g, comms_vel2);
                } else {
                    _iq18 comms_ang1 = (_iq18)data_ctrl.angle_1 << 8;
                    _iq18 comms_ang2 = (_iq18)data_ctrl.angle_2 << 8;
                    servo_iq18_controlPosition(&servo1_g, comms_ang1);
                    servo_iq18_controlPosition(&servo2_g, comms_ang2);
                }
                
                break;
            case 1: // Current debug
                servo_iq18_controlCurrent(&servo1_g, _IQ18(cur_debug_set_1));
                servo_iq18_controlCurrent(&servo2_g, _IQ18(cur_debug_set_2));
                break;
            case 2: // Velocity debug
                servo_iq18_controlVelocity(&servo1_g, _IQ18(vel_debug_set_1));
                servo_iq18_controlVelocity(&servo2_g, _IQ18(vel_debug_set_2));
                break;
            case 3:// Angle debug
                servo_iq18_controlPosition(&servo1_g, _IQ18(ang_debug_set_1));
                servo_iq18_controlPosition(&servo2_g, _IQ18(ang_debug_set_2));
            default:
                system_enabled = 0;
                break;
            }
        }
        
        if(!system_enabled)
        {
            TIM3->CCR1 = 0;
            TIM3->CCR2 = 0;
            servo_iq18_reset(&servo1_g);
            servo_iq18_reset(&servo2_g);
            ind_led_set_opmode(&ind_led_red, BLINK_05HZ);
        }

        if (brg_fault_flag){
            ind_led_set_opmode(&ind_led_red, BLINK_8HZ);
        }

        if (comms_fault_flag){
            ind_led_set_opmode(&ind_led_red, BLINK_4HZ);
        }
        
        if (reset_flag)
        {
            encoder_reset_iq18(&servo1_g.encoder);
            encoder_reset_iq18(&servo2_g.encoder);
            reset_flag = 0;
        }
    }
}