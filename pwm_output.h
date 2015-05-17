#ifndef __PWM_OUTPUT_H
#define	__PWM_OUTPUT_H

#include "stm32f10x.h"

void TIM3_PWM_Init(void);
void TIM3_Mode_Config(u16 CCR1_Val);

#endif /* __PWM_OUTPUT_H */

