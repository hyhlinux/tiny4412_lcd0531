#include <iic.h>
#include <common.h>
#include <irq.h>
#include <tp.h>
#include <lcd.h>
#include <uart.h>
#include <command.h>

/***********************************
state	: 
	=3，表示回到UI
	=2, 表示进入cmd
	=1, 表示进入app
***********************************/
#define BACK_UI		3
#define ENTER_CMD	2
#define ENTER_APP	1
int double_hit = 0;
int state = 0;
int ts[5][2]= {
{0,0},
{0,0},
{0,0},
{0,0},
{0,0}
};
void do_tp(void)
{
	int i;
	char data[32];

	if(EXT_INT41_PEND & (1 << 6)){
		EXT_INT41_PEND = EXT_INT41_PEND;

		if (read_data(data, sizeof(data)) == -2) 
		{
			if (read_data(data, sizeof(data)) == -2)
			{
				printf("no ack\n");	
				return;
			}
		}

		if (data[2] <= 0)
			return;
//		printf("gestrue: %#x\n", data[1]&0xff);
//		printf("points=%d: ", data[2]);
		state = data[2];
		if (state == 1)
			double_hit++;
		for (i = 0; i < (data[2]&0xf); i++)
		{
/*
			printf("(x%d=%d,y%d=%d); ", i, \
			((data[i*6+3]&0xf)<<8)|data[i*6+4], i, \
			((data[i*6+5]&0xf)<<8)|data[i*6+6]);
*/
			ts[i][0] = ((data[i*6+3]&0xf)<<8)|data[i*6+4];
			ts[i][1] = ((data[i*6+5]&0xf)<<8)|data[i*6+6];
		}
		printf("\n\n");
	}
//	find_state_exec();	//deal_irq
	//在中断上下文
	return;
}
