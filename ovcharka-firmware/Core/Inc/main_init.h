#ifndef INC_MAIN_INIT_H_
#define INC_MAIN_INIT_H_

#include "pins_init.h"
#include "servo_init.h"
#include "adc_current.h"
#include "global_flags.h"
#include "potamon_bus_lowlvl_handle.h"

void init_mtr_ctrl();

extern EMA_iq18 IC_filter;


#endif /* INC_MAIN_INIT_H_ */