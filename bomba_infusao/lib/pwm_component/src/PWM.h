
#ifndef __PWM_COMPONENT__
#define __PWM_COMPONENT__

#include <Arduino.h>
/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * DECLARATIONS
 ****************************************************************************************
 */

void PWM_setup(void);
void PWM_stop(void);
void PWM_active(void);
void PWM_set_duty_cycle(float duty_cycle);
float PWM_get_duty_cycle(void);

/*
 * GETTERS
 ****************************************************************************************
 */

#endif