/*
 * ema_iq18.c
 *
 *  Created on: Dec 18, 2023
 *      Author: JV4K
 */

#include "ema_iq18.h"

// Initialize the EMA filter
void initEMA_iq18(EMA_iq18* filter, float alpha, _iq18 initial_value) {
	filter->alpha = _IQ18(alpha);
	filter->previous = initial_value;
}

// Update the EMA filter with a new value and return the filtered result
_iq18 updateEMA_iq18(EMA_iq18 *filter, _iq18 newValue) {
	_iq18 ema = _IQ18mpy(filter->alpha, newValue)
			+ _IQ18mpy((_IQ18(1) - filter->alpha), filter->previous);
	filter->previous = ema;
	return ema;
}

