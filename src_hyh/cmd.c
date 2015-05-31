#include <lcd.h>
#include <shell_info.h>
#include <key.h>
#include <common.h>
#include <command.h>
#include <buzzer.h>
#include <uart.h>
#include <schdule.h>
#include <teris.h>
#include <alpha.h>
#include <pic20.h>
#include <rotator.h>
#include <myppt.h>

extern int state;
extern int ts[5][5];

void  find_cmd_exec(char *buf)
{
	int ret = 0;
	cmd_t *p = &start_shell_cmd_add;

	while(p < &end_shell_cmd_add) {
//		printf("p->name..%s   buf...%s\n", p->name, buf);
		if( !(ret=strcmp(buf, p->name))  ) {
			(p->cmd_func)();
			return ;
		}
		p++;
	}
	printf("%s command not find\n", buf);
}
/******************************************
*positon:
		x = ts[0][0]
		y = ts[0][1]
*
*	: 对应(x,y)-->app
******************************************/

extern int direct_x;

void enter_app(void)
{
	printf("cmd.c %s\n",__func__);
	int x, y;
	
	x = (ts[0][0]/200); // 0 1 2 3
	y = ts[0][1] - 300;

	direct_x = 1;//default  pic20--> k1 改变

	//if ((y > 0) && (direct_x)) {
	if ((y > 0) && (direct_x) && state == 1) {
		switch(x) {
		case 0://tetris 
			//printf("%s %d\n",__func__,x);
			sh_cmd2();
			break;
		case 1://alpha 
			//printf("%s %d\n",__func__,x);
			sh_cmd3();
			break;
		case 2://pic_20 
			//printf("%s %d\n",__func__,x);
			sh_cmd4();
			break;
		case 3://rotator
			//printf("%s %d\n",__func__,x);
			sh_cmd5();
			break;
		default:
			break;

		}
	} else if ( (ts[0][1] < 120)  && (ts[0][0] > 200*3) ) {
		//display ppt by time 
		sh_cmd6();
	} else {

	}
	
}
void sh_cmd1(void)
{
//	time_tt t = {};
//	clean_lcd(BACK_COL);
//	gettime(&t);

	buzzer_init();
	buzzer_on();
	udelay(1000*1000);
	buzzer_off();
	udelay(1000*1000);
}
CMD_T(test, sh_cmd1, "test--help");
//teteris
void sh_cmd2(void)
{
	VIDW01ADD0B0 = FRAMBUFFER1;
	VIDW01ADD1B0 = FRAMBUFFER1 + VIDOSD1C*4; 

	clean_lcd(BACK_COL);
	write_string("\n Loading in #####.................",CMD_X,CMD_Y);
	udelay(1*100*1000);

	clean_lcd(BACK_COL);
	write_string("\n Loading in ##########............",CMD_X,CMD_Y);
	udelay(1*100*1000);

	clean_lcd(BACK_COL);
	write_string("\n Loading in ##################....",CMD_X,CMD_Y);
	udelay(1*100*1000);

	clean_lcd(BACK_COL);
	write_string("\n ....HYH....READY GO TETERIS.......\n",CMD_X,CMD_Y);
	udelay(4*100*1000);
	VIDOSD1C = 0xffffff;
	my_teris();
	clean_lcd(BACK_COL1);
	VIDOSD1C = 0x000000;
	udelay(4*100*1000);
}
CMD_T(tetris, sh_cmd2, "tetris--help");//150504 10:30 ok
/*******************************************
alpha	:	透明度
	 仿照tetris来实现

显示效果：
	 k1-4 来进行控制，实现两张图片重合和覆盖。
	 k1	:----显示w0---底色
	 k2	:----more
	 k3	:----less
	 k4	:----显示w1---上层颜色

规则	： 显示时，独占w1->frambuffer 
	   退出时，对资源释放。
	
return	: 
	UI--> ui
	shell-->cmd
*******************************************/
void sh_cmd3(void)
{
	printf("%s\n",__func__);
	schdule_w0();

	clean_lcd(BACK_COL);
	write_string("\n Loading in #####.................",CMD_X,CMD_Y);
	udelay(1*1000*1000);

	clean_lcd(BACK_COL);
	write_string("\n Loading in ##########............",CMD_X,CMD_Y);
	udelay(1*1000*1000);

	clean_lcd(BACK_COL);
	write_string("\n Loading in ##################....",CMD_X,CMD_Y+20);
	udelay(1*1000*1000);

	clean_lcd(BACK_COL);
	write_string("\n ....HYH....GO. ALPHA......\n",CMD_X,CMD_Y+200);
	udelay(1*1000*1000);

	//printf("\nb. alpha\n");
	schdule_w1_alpha();
	my_alpha();
	schdule_w1_ui();
	//printf("\na. alpha\n");

	udelay(4*100*1000);
}
CMD_T(alpha, sh_cmd3, "alpha--help");
/***************************************
pic20	:
***************************************/
void sh_cmd4(void)
{
	printf("pic20 %s\n",__func__);
	schdule_w0();

	clean_lcd(BACK_COL);
	write_string("\n Loading in #####.................",CMD_X,CMD_Y);
	udelay(7*100*1000);

	clean_lcd(BACK_COL);
	write_string("\n Loading in ##########............",CMD_X,CMD_Y);
	udelay(6*100*1000);

	clean_lcd(BACK_COL);
	write_string("\n Loading in ##################....",CMD_X,CMD_Y+20);
	udelay(5*100*1000);

	clean_lcd(BACK_COL);
	write_string("\n ....HYH....GO....PIC20...\n",CMD_X,CMD_Y+200);
	udelay(8*100*1000);

	//printf("\nb. pic20\n");
	schdule_w1_pic20();
	clean_lcd_w1_PIC(BACK_COL);
	my_pic20();
	schdule_w1_ui();
	//printf("\na. pic20\n");
}
CMD_T(pic20, sh_cmd4, "pic20--help");
//rotator
void sh_cmd5(void)
{
	printf("rotator %s\n",__func__);
	schdule_w0();

	clean_lcd(BACK_COL);
	write_string("\n Loading in #####.................",CMD_X,CMD_Y);
	udelay(7*100*1000);

	clean_lcd(BACK_COL);
	write_string("\n Loading in ##########............",CMD_X,CMD_Y);
	udelay(6*100*1000);

	clean_lcd(BACK_COL);
	write_string("\n Loading in ##################....",CMD_X,CMD_Y+20);
	udelay(5*100*1000);

	clean_lcd(BACK_COL);
	write_string("\n ....HYH....ROTATOR.......\n",CMD_X,CMD_Y+200);
	udelay(9*100*1000);

	schdule_w1_rotator_menu();
	clean_lcd_w1_ROTATOR(BACK_BLACK);
	my_rotator();
	schdule_w1_ui();
}
CMD_T(rotator, sh_cmd5, "rotator--help");
void sh_cmd6(void)
{
	printf("rotator %s\n",__func__);
	schdule_w0();

	clean_lcd(BACK_COL);
	write_string("\n Loading in #####.................",CMD_X,CMD_Y);
	udelay(7*100*1000);

	clean_lcd(BACK_COL);
	write_string("\n Loading in ##########............",CMD_X,CMD_Y);
	udelay(6*100*1000);

	clean_lcd(BACK_COL);
	write_string("\n Loading in ##################....",CMD_X,CMD_Y+20);
	udelay(5*100*1000);

	clean_lcd(BACK_COL);
	write_string("\n ....HYH....PPT.......\n",CMD_X,CMD_Y+200);
	udelay(9*100*1000);

	//schdule_w1_rotator_menu();
	my_ppt();
	schdule_w1_ui();
}
CMD_T(myppt, sh_cmd6, "myppt--help");
