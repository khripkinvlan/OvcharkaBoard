#ifndef INC_SETTINGS_H_
#define INC_SETTINGS_H_

/* --- Enable servo ---*/
#define SERVO1_ENABLE 1
#define SERVO2_ENABLE 1

/* --- Directions ---*/

// Choose whether it's front or rear axis controller (uncomment needed)
#define AXIS_FRONT
// #define AXIS_REAR

/* --- Spec of servo (assuming they are the same) ---*/

#define MT_VELOCITY 1065 // Velocity before gearbox (rad/s)
#define MT_GEAR_RATIO 21.3

#define ENC_TPR 44 // Ticks of timer per revolution (no gearbox) TODO: CHECK

/* Motor current limit (Amps).
For max safety use rated current of a motor.    */
#define CUR_LIMIT 1

#define CUR_SENSOR_GAIN 0.001221 // Gain to calculate current out of adc val

/* --- PID controllers settings ---*/

/* Current controller */
// #define CUR_KP 4.284
// #define CUR_KI 901.403
// #define CUR_KD 0
// #define CUR_KB 901.403 // Back-calc antiwindup gain
// #define CUR_DT 0.000111111

#define CUR_KP 5.9949
#define CUR_KI 1802.846
#define CUR_KD 0
#define CUR_KB 1298.224 // Back-calc antiwindup gain
#define CUR_DT 0.000055555

/* Velocity controller */
#define VEL_KP 0.05722
#define VEL_KI 0.19
#define VEL_KD 0
#define VEL_KB 0.572 // Back-calc antiwindup gain
#define VEL_DT 0.004

/* Angle controller */
#define ANG_KP 3.576
#define ANG_KI 0
#define ANG_KD 0
#define ANG_KB 0 // Back-calc antiwindup gain
#define ANG_DT 0.004
#define ANG_TOLERANCE 0.02


// Current sense amplifier offset values for different axes
#ifdef AXIS_FRONT
#define M1_ADC_OFFSET 2056
#define M2_ADC_OFFSET 2049
#endif

#ifdef AXIS_REAR
#define M1_ADC_OFFSET 2054
#define M2_ADC_OFFSET 2055
#endif


// Defines for servo directions for different axis (defined in the beginning of file)
/*  This is done in case of wrong electrical connection 
    (e.g. inverse motor polarity, encoder channels) and physical direction of motor */
#ifdef AXIS_FRONT

#define S_NUM 1

#define SERVO1_REVERSE 0
#define SERVO1_ENC_REVERSE 1
#define SERVO2_REVERSE 0
#define SERVO2_ENC_REVERSE 1

#endif

#ifdef AXIS_REAR

#define S_NUM 2

#define SERVO1_REVERSE 1
#define SERVO1_ENC_REVERSE 0
#define SERVO2_REVERSE 1
#define SERVO2_ENC_REVERSE 1

#endif

#endif /* INC_SETTINGS_H_ */