#ifndef _INC_IND_LED_
#define _INC_IND_LED_

#include "gpio.h"

typedef enum
{
    OFF,
    STATIC,
    BLINK_05HZ,
    BLINK_1HZ,
    BLINK_2HZ,
    BLINK_4HZ,
    BLINK_8HZ
} ind_led_opmode;

typedef struct
{
    GPIO_TypeDef* port;
    uint16_t pin;
    uint16_t call_freq;
    uint16_t CNT_LED;
    uint16_t div8_hz;
    uint16_t div4_hz;
    uint16_t div2_hz;
    uint16_t div05_hz;
    uint16_t cur_div;
    ind_led_opmode opmode;
    ind_led_opmode prev_opmode;
    uint8_t lowtrigflag;
}__attribute__((packed, aligned(4))) ind_led_t;

void ind_led_init(ind_led_t* led, GPIO_TypeDef* port, uint16_t pin, uint16_t call_freq_hz, uint8_t lowtrig_flag);
void ind_led_handler(ind_led_t* led);
void ind_led_set_opmode(ind_led_t* led, ind_led_opmode opmode);

extern ind_led_t ind_led_red;

#endif