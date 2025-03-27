#ifndef INC_GLOBAL_FLAGS_H_
#define INC_GLOBAL_FLAGS_H_

#include "main.h"

extern volatile uint8_t system_enabled;
extern volatile uint8_t control_mode;
extern volatile uint8_t reset_flag;
extern volatile uint8_t brg_fault_flag;
extern volatile uint8_t comms_fault_flag;
extern volatile uint8_t overcurrent_flag;

#endif /* INC_GLOBAL_FLAGS_H_ */