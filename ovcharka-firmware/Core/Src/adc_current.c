#include "adc_current.h"

volatile uint16_t adc[2];
_iq18 current[2];
EMA_iq18 filter1, filter2;


// uint32_t check;

int16_t CS_ADC_M1_Offset = M1_ADC_OFFSET;
int16_t CS_ADC_M2_Offset = M2_ADC_OFFSET;
float CS_ADC_M1_Gain = 0.00107;
float CS_ADC_M2_Gain = 0.00107;

void adc_cur_init()
{
    // Starting DMA for capturing current measures from ADC
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc, 2);

    // Initia;lization of filters
    initEMA_iq18(&filter1, 0.005, _IQ18(CS_ADC_M1_Offset));
    initEMA_iq18(&filter2, 0.005, _IQ18(CS_ADC_M2_Offset));
    adc[0] = CS_ADC_M1_Offset;
    adc[1] = CS_ADC_M2_Offset;
}

void adc_callback_handler()
{
    _iq18 adc0_filtered = updateEMA_iq18(&filter1, _IQ18(adc[0]));
    current[0] = _IQ18mpy((adc0_filtered - _IQ18(CS_ADC_M1_Offset)), _IQ18(CS_ADC_M1_Gain));

    _iq18 adc1_filtered = updateEMA_iq18(&filter2, _IQ18(adc[1]));
    current[1] = _IQ18mpy((adc1_filtered - _IQ18(CS_ADC_M2_Offset)), _IQ18(CS_ADC_M2_Gain));
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    adc_callback_handler();
}