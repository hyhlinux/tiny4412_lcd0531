#ifndef __BUZZER_H__
#define __BUZZER_H__


#include "common.h"

#define GPD0CON		*((u32_t *)0X114000a0)
#define GPD0DAT		*((u32_t *)0X114000a4)

extern void buzzer_init(void);
extern void buzzer_on(void);
extern void buzzer_off(void);

#endif 

