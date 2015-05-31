#include <teris.h>
#include <common.h>
#include <command.h>
#include <mmu.h>
#include <irq.h>
#include <rtc.h>
#include <uart.h>
#include <shell_info.h>
#include <tp.h>
#include <schdule.h>

#define  SIZE		1024
#define  SET_TIME 	0
#define  HELP_N 	14


extern int tik;
extern int state;
int
shell(void)
{
	schdule_w0();
//	init_board();
	char cmd[SIZE] = "";
	//char hyh[] = "[hyh@tplinux:1993.01.14]# ";
	//char hyh[] = "[hyh_tp@bs_1506 ]# ";
	char hyh[] = "[hyh_tp@root ]# ";
	int j = 0;

	while(1) {
			uprintf("[hyh@root]# ");  	//display in minicom 
			write_string(hyh,0,j); 			//display in lcd
/* ugets 会在此阻塞，发生中断后，会造成中断后，需要回车
 * 原因： 在中断中没有做处理工作，只是获取状态，然后在
 × 	   find_state_exec中做处理工作。
 * 解决： 在中断中调用 uputs('\n');
 */
			ugets(cmd);
			if(strcmp(cmd, "exit") == 0)
					break;
			else if (strcmp(cmd, "help") == 0) {
#if UART_DEG
					uart_display_help();
#endif
					write_string(cmd, strlen(hyh)*FONT_COL, j);
					lcd_display_help();
					j = (HELP_N+1) * FONT_RAW; 
			} else if (strcmp(cmd, "clc") == 0) {
					write_string(cmd, strlen(hyh)*FONT_COL, j);
					j = 0;
					clean_lcd(BACK_COL);
					continue;
			} else { 
//					write_string(cmd, strlen(hyh)*FONT_COL, j);
			}
			write_string(cmd, strlen(hyh)*FONT_COL, j);
			j+=FONT_RAW;

		   // 	find_state_exec();	//deal_irq
			if (state == APP_BACK)		//the same as mian.c
				return 0;
		    	find_cmd_exec(cmd);	//cmd_shell

			if (j > 480 - FONT_RAW) {
					j = 0;
					clean_lcd(BACK_COL);
			}
		
	}


	return 0;
}
