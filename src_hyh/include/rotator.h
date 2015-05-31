
#ifndef __HYH_ROTATOR_H__
#define __HYH_ROTATOR_H__

#include "common.h"

#define CONFIG 	     *((u32_t *)0x12810000)  //Rotator configuration 0x0000_0000
#define CONTROL      *((u32_t *)0x12810010)  //Rotator image0 control 0x0000_0000
#define STATUS 	     *((u32_t *)0x12810020)  //Rotator status 0x0000_0000
#define SRCBASEADDR0 *((u32_t *)0x12810030)  //Rotator source image base address 0 0x0000_0000
#define SRCBASEADDR1 *((u32_t *)0x12810034)  //Rotator source image base address 1 0x0000_0000
#define SRCBASEADDR2 *((u32_t *)0x12810038)  //Rotator source image base address 2 0x0000_0000
#define SRCIMGSIZE   *((u32_t *)0x1281003C)  //Rotator source image X, Y size 0x0000_0000
#define SRC_XY 	     *((u32_t *)0x12810040)  //Rotator source image X, Y coordinates 0x0000_0000
#define SRCROTSIZE   *((u32_t *)0x12810044)  //Rotator source image rotation Size 0x0000_0000
#define DSTBASEADDR0 *((u32_t *)0x12810050)  //Rotator destination image base address0 0x0000_0000
#define DSTBASEADDR1 *((u32_t *)0x12810054)  //Rotator destination image base address1 0x0000_0000
#define DSTBASEADDR2 *((u32_t *)0x12810058)  //Rotator destination image base address2 0x0000_0000
#define DSTIMGSIZE   *((u32_t *)0x1281005C)  //Rotator destination image X, Y size 0x0000_0000
#define DST_XY 	     *((u32_t *)0x12810060)  //Rotator destination image X, Y coordinates 0x0000_000


#define WAIT_ROTAT_END while(STATUS & 0x3)


extern void flip_ver(void);
extern void flip_hor(void);
extern void start_rotat(void);
extern void image_rotat(void);

extern void my_rotator(void);
extern void rotator_src_image(int num);
extern void rotator_src_image_deal_90(int num);
extern void rotator_src_image_deal_270(int num);
extern void rotator(int rote);

#endif 
