#include "main_init.h"

EMA_iq18 IC_filter;

void init_mtr_ctrl()
{
    system_enabled = 0;
    servo_init();

    // Reset servos
    servo_iq18_reset(&servo1_g);
    servo_iq18_reset(&servo2_g);

    servo_periph_init();
    adc_cur_init();

    initEMA_iq18(&IC_filter, VEL_EMA, 0);

    TXOFF;
    HAL_UART_Receive_DMA(&huart1, (uint8_t*)&packet_sync, S_SYNC);
    
}


