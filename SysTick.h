#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

void SysTick_Init(void);
void delay_us(__IO u32 nTime);
void delay_ms(__IO u32 nTime);
void TimingDelay_Decrement(void);
	
#endif /* __SYSTICK_H */
