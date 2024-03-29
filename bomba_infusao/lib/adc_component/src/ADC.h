
#ifndef __ADC_COMPONENT__
#define __ADC_COMPONENT__

#include <Arduino.h>
/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * DECLARATIONS
 ****************************************************************************************
 */

typedef struct _adc
{
    u16 value;
    float voltage;
} adc;

void ADC_setup(void);
int ADC_read(u8 ch);
adc ADC_get_from_adc(u8 ch);

/*
 * GETTERS
 ****************************************************************************************
 */

#endif