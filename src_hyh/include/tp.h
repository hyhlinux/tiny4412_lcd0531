#ifndef MILLET_TP_H_
#define MILLET_TP_H_

#define GPX1CON 		(*(u32 *)(0x11000000 + 0x0C20)) 
#define EXT_INT41CON 		(*(u32 *)(0x11000000 + 0x0E04))
#define EXT_INT41_MASK 		(*(u32 *)(0x11000000 + 0x0F04))
#define EXT_INT41_PEND 		(*(u32 *)(0x11000000 + 0x0F44))
#define EXT_INT41_FLTCON1 	(*(u32 *)(0x11000000 + 0x0E8C))

extern void tp_int_init(void);

#define TP_IRQ 				62
#define LEV_TP				0

#endif
