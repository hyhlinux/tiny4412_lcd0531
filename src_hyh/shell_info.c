//#include <shell_ui.h>
#include <uart.h>
#include <lcd.h>

void uart_display_help(void)
{
	uputchar('\n');
	uprintf("\b\t############################################\t\n");
	uprintf("\b\t##      called by cmd: help                #\t\n");
	uprintf("\b\t##DOS_HYH:         9527 ****                #\t\n");
	uprintf("\b\t##                                         #\t\n");
	uprintf("\b\t##menu_cmd:#                               #\t\n");
	uprintf("\b\t##       1:test---(buzzer)                 #\t\n");
	uprintf("\b\t##       2:tetris                          #\t\n");
	uprintf("\b\t##       3:alpha--(w0/1)                   #\t\n");
	uprintf("\b\t##       4:pic20                           #\t\n");
	uprintf("\b\t##       5:rotator                         #\t\n");
	uprintf("\b\t##       6:myppt                           #\t\n");
	uprintf("\b\t##       7:wait_for_future                 #\t\n");
	uprintf("\b\t##       0:help --display this info        #\t\n");
	uprintf("\b\t############################################\t\n");
	uputchar('\n');
	uputchar('\n');
	uputchar('\n');
	uputchar('\n');
	uputchar('\n');
}
void lcd_display_help(void)
{
	clean_lcd(BACK_COL);
	write_string("",0,0);
	write_string("  #####################################################", 0,  FONT_RAW*1);
	write_string("  ##        Wellcom enjoy my os :                     #", 0,  FONT_RAW*2);
	write_string("  ##Dos_Hyh :                9527 ****                #", 0,  FONT_RAW*3);
	write_string("  ##                                                  #", 0,  FONT_RAW*4);
	write_string("  ##menu_cmd:#                                        #", 0,  FONT_RAW*5);
	write_string("  ##       1:test		----(buzzer)                #", 0,  FONT_RAW*6);
	write_string("  ##       2:tetris       ----(game  )                #", 0,  FONT_RAW*7);
	write_string("  ##       3:alpha	----(w0/1  )                #", 0,  FONT_RAW*8);
	write_string("  ##       4:pic20	----(bs    )                #", 0,  FONT_RAW*9);
	write_string("  ##       5:rotator      ----(bs	   )                #", 0,  FONT_RAW*10);
	write_string("  ##       6:myppt	----(bs    )                #", 0,  FONT_RAW*11);
	write_string("  ##       7:wait_for_future                          #", 0,  FONT_RAW*12);
	write_string("  ##       0:help         ----display this info       #", 0,  FONT_RAW*13);
	write_string("  #####################################################", 0,  FONT_RAW*14);

}
void uart_welcom_login(void)
{
	uputchar('\n');
	uprintf("\b\t############################################\t\n");
	uprintf("\b\t##-----------------------------------------#\t\n");
	uprintf("\b\t##   WELLCOM LOGIN HYH_DOS                 #\t\n");
	uprintf("\b\t##        thank you using this os  ^1^...  #\t\n");
	uprintf("\b\t##=========================================#\t\n");
}
void lcd_welcom_login(void)
{
	clean_lcd(BACK_COL);
	write_string("",0,0);
	write_string("\t############################################\t\n", 0,  FONT_RAW*0);
	write_string("\t##-----------------------------------------#\t\n", 0,  FONT_RAW*1);
	write_string("\t##   WELLCOM LOGIN HYH_DOS                 #\t\n", 0,  FONT_RAW*2);
	write_string("\t##        thank you using this os  ^1^...  #\t\n", 0,  FONT_RAW*3);
	write_string("\t##=========================================#\t\n", 0,  FONT_RAW*4);
	write_string("",0,FONT_RAW*4);
}
