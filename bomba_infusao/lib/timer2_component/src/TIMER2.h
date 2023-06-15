
#ifndef __TIMER2_COMPONENT__
#define __TIMER2_COMPONENT__

/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * DECLARATIONS
 ****************************************************************************************
 */

typedef void (*TIMER2_Callback)(char* data);

void TIMER2_setup(TIMER2_Callback callback);
void TIMER2_start();
void TIMER2_stop();

/*
 * GETTERS
 ****************************************************************************************
 */

unsigned int TIMER2_get_segundos();
unsigned int TIMER2_get_cont();

#endif