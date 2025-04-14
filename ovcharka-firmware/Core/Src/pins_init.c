#include "pins_init.h"

void pin_init_mtcrl()
{
    // Init DMA
    MX_DMA_Init();
    // Initialize gpio; dma for adc
    MX_GPIO_Init();
}