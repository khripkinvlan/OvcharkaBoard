#include "ind_led.h"

ind_led_t ind_led_red;

void ind_led_init(ind_led_t* led, GPIO_TypeDef* port, uint16_t pin, uint16_t call_freq_hz, uint8_t lowtrig_flag)
{
    led->port = port;
    led->pin = pin;
    led->call_freq = call_freq_hz;
    led->div8_hz = call_freq_hz >> 3;
    led->div4_hz = call_freq_hz >> 2;
    led->div2_hz = call_freq_hz >> 1;
    led->div05_hz = call_freq_hz << 1;
    led->lowtrigflag = lowtrig_flag;
    led->opmode = OFF;
    led->prev_opmode = OFF;
    led->CNT_LED = 0;
    HAL_GPIO_WritePin(led->port, led->pin, led->lowtrigflag);
}

void ind_led_handler(ind_led_t* led){
    if(led->opmode != led->prev_opmode){
        led->CNT_LED = 0;
        led->prev_opmode = led->opmode;
    }
    if(led->opmode == OFF){
        HAL_GPIO_WritePin(led->port, led->pin, led->lowtrigflag);
    } else if (led->opmode == STATIC){
        HAL_GPIO_WritePin(led->port, led->pin, !led->lowtrigflag);
    } else {
        if (led->CNT_LED < (led->cur_div >> 1)){
            HAL_GPIO_WritePin(led->port, led->pin, !led->lowtrigflag);
        } else {
            HAL_GPIO_WritePin(led->port, led->pin, led->lowtrigflag);
        }
        if (led->CNT_LED >= (led->cur_div-1)){
            led->CNT_LED = 0;
        }
        led->CNT_LED++;
    }
}

void ind_led_set_opmode(ind_led_t* led, ind_led_opmode opmode){
    led->opmode = opmode;
    switch (opmode)
    {
    case BLINK_05HZ:
        led->cur_div = led->div05_hz;
        break;
    case BLINK_1HZ:
        led->cur_div = led->call_freq;
        break;
    case BLINK_2HZ:
        led->cur_div = led->div2_hz;
        break;
    case BLINK_4HZ:
        led->cur_div = led->div4_hz;
        break;
    case BLINK_8HZ:
        led->cur_div = led->div8_hz;
    default:
        break;
    }
}