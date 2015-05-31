#ifndef IRQ_H_
#define IRQ_H_

#include "common.h"

#define ICCBASE 0x10480000

#define ICCICR_CPU0 	*(u32 *)(ICCBASE + 0x0000) 
#define ICCPMR_CPU0 	*(u32 *)(ICCBASE + 0x0004)
#define ICCIAR_CPU0 	*(u32 *)(ICCBASE + 0x000C) 
#define ICCEOIR_CPU0	*(u32 *)(ICCBASE + 0x0010) 

#define ICDBASE 0x10490000

#define ICDDCR 		*(u32 *)(ICDBASE + 0x0000) 
#define ICDIPR0_CPU0 	((u32 *)(ICDBASE + 0x0400)) 
#define ICDIPTR0_CPU0 	((u32 *)(ICDBASE + 0x0800)) 
#define ICDISER0_CPU0 	((u32 *)(ICDBASE + 0x0100)) 
#define ICDSGIR 	*(u32 *)(ICDBASE + 0x0f00) 

#define TOT 160

typedef void (*isr_t)(void);
extern void irq_request_cpu0(int num, void (*do_isr)(void), int pri);

#endif
