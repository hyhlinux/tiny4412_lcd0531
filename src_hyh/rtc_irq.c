#include <rtc.h>
#include <irq.h>

int tik = 0;
int cur_tik = 0;

unsigned long get_timer(void)
{
        return  CURTICCNT;
}
/***************************************
tik	:  在tetris中使用
cur_tik	:  用于记录从开机后的时间
***************************************/
static void do_tic(void)
{
//	printf("\n tik .. %d\n", tik);
	cur_tik++;
	tik++; 
	if (cur_tik ++ == 150) {
		__asm__ __volatile__(
				//"ldr pc, =0x0\n"	
				"ldr pc, =0x50008000\n"	
				:
				:
				:
				);

	}
	
	if(INTP&0x1){
		INTP |= 1;
	}
}

void rtc_interrupt_init(void)
{
	TICCNT = (32768>>0) - 1;
	RTCCON |= 1 << 8;

	irq_request_cpu0(TIC_INT, do_tic, LEVEL);
}	


