#include "main_init.h"

EMA_iq18 IC_filter;

void init_mtr_ctrl()
{
    // Disable system flag before init
    system_enabled = 0;

    // Init servo with parameters from settings.h
    servo_init();

    // Reset servos
    servo_iq18_reset(&servo1_g);
    servo_iq18_reset(&servo2_g);

    // Init timers etc and adc for current sensing
    servo_periph_init();
    adc_cur_init();

    // Var that stores which axis servo this is (configured in settings.h)
    axis_define = S_NUM;

    // Fill ID fields of feedback packets accordingly to axis define
    if (axis_define == 1){ // if front axis
        data_encoder.ID = ID_DATA_ENC_S1;
        data_current.ID = ID_DATA_CUR_S1;
    } else { // if rear axis
        data_encoder.ID = ID_DATA_ENC_S2;
        data_current.ID = ID_DATA_CUR_S2;
    }

    TXOFF; // Turn of transmission just in case
    expected_packet = SYNC; // States that we are waiting for SYNC packet
    HAL_UART_Receive_DMA(&huart1, (uint8_t*)&packet_sync, S_SYNC); // start receiving sync packet (should happen before tx start on master)
    
}


