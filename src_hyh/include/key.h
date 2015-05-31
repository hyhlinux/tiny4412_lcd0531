#ifndef __KEY_H__
#define __KEY_H__

#include "common.h"
//typedef volatile unsigned int u32_t;
#define GPX3CON		*((u32_t *)0X11000c60) 
#define GPX3DAT		*((u32_t *)0X11000c64) 
//teris
#define IS_LEFT 	(((GPX3DAT>>2)&0xf) == 0xe ? 1 : 0)
#define IS_RIGHT 	(((GPX3DAT>>2)&0xf) == 0xd ? 1 : 0)
#define IS_DOWN 	(((GPX3DAT>>2)&0xf) == 0xb ? 1 : 0)
#define IS_UP	 	(((GPX3DAT>>2)&0xf) == 0x7 ? 1 : 0)
//alpha
#define ALPHA_W0	(((GPX3DAT>>2)&0xf) == 0xe ? 1 : 0)
#define ALPHA_INC 	(((GPX3DAT>>2)&0xf) == 0xd ? 1 : 0)
#define ALPHA_DEC 	(((GPX3DAT>>2)&0xf) == 0xb ? 1 : 0)
#define ALPHA_W1	(((GPX3DAT>>2)&0xf) == 0x7 ? 1 : 0)
//pic20
#define PIC_DIRECTION_CHANGE 	(((GPX3DAT>>2)&0xf) == 0xe ? 1 : 0)
#define PIC_INC 	(((GPX3DAT>>2)&0xf) == 0xd ? 1 : 0)
#define PIC_DEC 	(((GPX3DAT>>2)&0xf) == 0xb ? 1 : 0)
#define PIC_MENU	(((GPX3DAT>>2)&0xf) == 0x7 ? 1 : 0)
//rotator
#define ROTATOR_MODE_CHANGE 	(((GPX3DAT>>2)&0xf) == 0xe ? 1 : 0)
#define ROTATOR_INC 		(((GPX3DAT>>2)&0xf) == 0xd ? 1 : 0)
#define ROTATOR_DEC 		(((GPX3DAT>>2)&0xf) == 0xb ? 1 : 0)
#define ROTATOR_PIC_MENU	(((GPX3DAT>>2)&0xf) == 0x7 ? 1 : 0)


extern void key_init(void);
extern int  key_read(void);
extern int  key_id(void);


#endif 
