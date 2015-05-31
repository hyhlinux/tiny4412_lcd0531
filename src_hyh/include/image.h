#ifndef MILLET_IMAGE_H
#define MILLET_IMAGE_H

#include <common.h>

#define IMAGEBASE 0x12810000

#define CONFIG 			*((u32 *)(IMAGEBASE + 0x0000)) 
#define CONTROL 		*((u32 *)(IMAGEBASE + 0x0010))
#define STATUS 			*((u32 *)(IMAGEBASE + 0x0020))
#define SRCBASEADDR0 	*((u32 *)(IMAGEBASE + 0x0030))
#define SRCBASEADDR1 	*((u32 *)(IMAGEBASE + 0x0034))
#define SRCBASEADDR2 	*((u32 *)(IMAGEBASE + 0x0038))
#define SRCIMGSIZE		*((u32 *)(IMAGEBASE + 0x003C))
#define SRC_XY 			*((u32 *)(IMAGEBASE + 0x0040))
#define SRCROTSIZE 		*((u32 *)(IMAGEBASE + 0x0044))
#define DSTBASEADDR0 	*((u32 *)(IMAGEBASE + 0x0050))
#define DSTBASEADDR1 	*((u32 *)(IMAGEBASE + 0x0054))
#define DSTBASEADDR2 	*((u32 *)(IMAGEBASE + 0x0058))
#define DSTIMGSIZE 		*((u32 *)(IMAGEBASE + 0x005C)) 
#define DST_XY			*((u32 *)(IMAGEBASE + 0X0060))



#endif
