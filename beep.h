#ifndef __BEEP_H
#define	__BEEP_H

#include "stm32f10x.h"

void BEEP_Init(void);
void beep_ok(void);
void beep_err(void);
void beep_done(void);

#endif /* __BEEP_H */
