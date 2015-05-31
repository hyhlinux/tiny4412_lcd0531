#ifndef MMU_H_
#define MMU_H_

#include "common.h"

#define create_descriptor(ttb, va,pa)  \
		(ttb[va >> 20] = ((pa&0xfff00000) | (0x2)))
		
				 
extern void create_vector_add(u32 *ttb);

#define VECTOR_BASE_VA 0xffff0000
#define VECTOR_BASE_PA 0x500f0000
#define TTB	       0x51000000

extern unsigned int vec_start;
extern unsigned int vec_end;

#endif


















