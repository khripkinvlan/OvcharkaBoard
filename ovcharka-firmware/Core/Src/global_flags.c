#include "global_flags.h"

volatile uint8_t system_enabled;
volatile uint8_t control_mode; // What to control via rs485. 0: velocity, 1: angle
volatile uint8_t reset_flag; // reset encoders
volatile uint8_t brg_fault_flag;
volatile uint8_t comms_fault_flag;
volatile uint8_t overcurrent_flag;
volatile uint8_t axis_define;