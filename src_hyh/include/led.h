#ifndef __LED_H__
#define __LED_H__

#include "common.h"
//typedef volatile unsigned int u32_t;
#define GPM4CON		*((u32_t *)0X110002e0)   
#define GPM4DAT		*((u32_t *)0X110002e4)


extern void led_init(void);
extern void led_on(int num);
extern void leds_on(void);
extern void led_off(int num);
extern void leds_off(void);


#endif 
