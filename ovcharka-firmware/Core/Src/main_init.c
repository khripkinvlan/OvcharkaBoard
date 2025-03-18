#include "main_init.h"

void init_mtr_ctrl()
{
    servo_init();
    // pin_init_mtcrl();
    // Init TIMERS and start them
    // Init servo structures

    // Init ADC&DMA

    // Reset servos
    servo_iq18_reset(&servo1_g);
    servo_iq18_reset(&servo2_g);

    // Init finished
    system_enabled = 0;
    servo_periph_init();
    adc_cur_init();


}
