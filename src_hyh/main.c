#include <common.h>
#include <command.h>
#include <mmu.h>
#include <irq.h>
#include <rtc.h>
#include <uart.h>
#include <tp.h>
#include <shell.h>
#include <lcd.h>
#include <ui.h>
#include <sd_to_mem.h>
#include <rotator.h>

void irq_init(void);
void init_board(void);

//extern int tik;
extern int state;

int
main(void)
{

	init_board();

	//while(1) {
	while(state == 5) {
		udelay(1000*1000);	
		printf("%s state:%d\n",__func__,state);
		switch(state) {
		case 0://ui	
			ui();
			continue;
		case 1://app --> state=2 return app  
			enter_app();
			state = 0;
			break;
		case 2:
			state = 0;
		case 3://back --ui
			shell();
			state = 0;
			continue;
		case 4:
			state = 0;
			continue;
		default:
			break;
		}
	}

	printf("main is return \n");
	return 0;
}

void init_board(void)
{
	lcd_init();
	irq_init();

	sd_to_mem();
	//image_rotat();
}
void irq_init(void)
{
	create_vector_add((u32 *)TTB);
	rtc_interrupt_init();
	tp_int_init();
}
