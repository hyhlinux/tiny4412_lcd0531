#include <common.h>
#include <iic.h>
#include <irq.h>
#include <tp.h>
#include <isr.h>

void tp_int_init(void)
{
	GPX1CON |= 0xf << 24; //GPX1_6 [24:27] EXT_INT41

	EXT_INT41CON &= ~(0x7 << 24); //[24:26]
	EXT_INT41CON |= 3 << 24;	 //irq's trigger is failing edge

	EXT_INT41_FLTCON1 |= 0xff<<16;

	EXT_INT41_MASK &= ~(1 << 6); //enable irq

	iic1_init(3856);

	irq_request_cpu0(TP_IRQ, do_tp, LEV_TP);
}

