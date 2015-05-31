
/*
*schdule	:  操作wind资源,统一管理
*
*
*
*/
#include <lcd.h>
#include <schdule.h>
//只需要w1
void schdule_w1_rotator_del(void)
{
	VIDOSD1C = 0xffffff;
	VIDW01ADD0B0 = FRAMBUFFER_ROTATOR_DEL;
	VIDW01ADD1B0 = FRAMBUFFER_ROTATOR_DEL + VIDOSD1C*4; 
}
void schdule_w1_rotator(void)
{
	VIDOSD1C = 0xffffff;
	VIDW01ADD0B0 = FRAMBUFFER_ROTATOR;
	VIDW01ADD1B0 = FRAMBUFFER_ROTATOR + VIDOSD1C*4; 
}
void schdule_w1_rotator_menu(void)
{
	schdule_w1_pic20();
}
//只需要w1
void schdule_w1_pic20_display(void)
{
	VIDOSD1C = 0xffffff;
	VIDW01ADD0B0 = FRAMBUFFER_PIC20DIS;
	VIDW01ADD1B0 = FRAMBUFFER_PIC20DIS + VIDOSD1C*4; 
}
//只需要w1
void schdule_w1_pic20(void)
{
	VIDOSD1C = 0xffffff;
	VIDW01ADD0B0 = FRAMBUFFER_PIC20DST;
	VIDW01ADD1B0 = FRAMBUFFER_PIC20DST + VIDOSD1C*4; 
}
//只需要w1
void schdule_w1_ui(void)
{
	VIDOSD1C = 0xffffff;
	VIDW01ADD0B0 = FRAMBUFFER_UI;
	VIDW01ADD1B0 = FRAMBUFFER_UI + VIDOSD1C*4; 
}
//同时需要w1/0
void schdule_w1_alpha(void)
{
	//w0
	VIDW00ADD0B0 = FRAMBUFFER_ALPHA0;
	VIDW00ADD1B0 = FRAMBUFFER_ALPHA0 + VIDOSD0C*4; 
	//w1
	VIDOSD1C = 0xffffff;
	VIDW01ADD0B0 = FRAMBUFFER_ALPHA1;
	VIDW01ADD1B0 = FRAMBUFFER_ALPHA1 + VIDOSD1C*4; 
}
void schdule_w0(void)
{
	//w0
	VIDW00ADD0B0 = FRAMBUFFER0;
	VIDW00ADD1B0 = FRAMBUFFER0 + VIDOSD0C*4; 

	VIDOSD1C = 0x000000;
#if 1
	VIDW01ADD0B0 = FRAMBUFFER1;
	VIDW01ADD1B0 = FRAMBUFFER1 + VIDOSD1C*4; 
#endif 
}


