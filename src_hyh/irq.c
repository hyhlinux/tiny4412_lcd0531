#include <irq.h>


isr_t isrs[TOT] = {NULL};
u32 flag = 0;

void do_irq(void)
{
	u32 stat;
	void (*handler)(void) = NULL;

	stat = ICCIAR_CPU0;	

	handler = isrs[stat&0x3ff];

	if(handler){
		handler();
		handler = NULL;
	}

	ICCEOIR_CPU0 = stat;
}

void irq_request_cpu0(int num, void (*do_isr)(void), int pri)
{
	if(!flag){
		/*使能中断信号可以转发给目标CORE*/
		ICCICR_CPU0 = 0x1;
		
		/*设置CPU0可以处理的中断优先级的阈值*/
		ICCPMR_CPU0 = 0xff;

		/*使能GIC监视和转发外设中断*/
		ICDDCR = 0x1;
		flag = 1;
	}

	/*设置对应中断号的优先级*/
	ICDIPR0_CPU0[num/4] &= ~(0xff << ((num%4)*8)); 
	ICDIPR0_CPU0[num/4] |= (pri << ((num%4)*8)); 

	/*选择对应中断号的中断被处理的目标处理器*/
	ICDIPTR0_CPU0[num/4] &= ~(0xff << ((num%4)*8));
	ICDIPTR0_CPU0[num/4] |= (0x1 << ((num%4)*8));

	/*对应GIC来说使能对应中断号的中断*/
	ICDISER0_CPU0[num/32] |= 0x1 << (num%32);

	isrs[num] = do_isr;

	/*使能CPU CORE对GIC转发过来的中断响应*/
	__asm__ __volatile__(
		"mrs r0,cpsr\n\t"
		"bic r0,r0,#(1 << 7)\n\t"
		"msr cpsr, r0\n\t"
	);
}
