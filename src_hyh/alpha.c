
#include <alpha.h>
#include <lcd.h>
#include <common.h>
#include <key.h>

extern int state;

/***********************************
核心操作：	透明度
-----------------------------------
w1完全显示	VIDOSD1C = 0xffffff;
w0完全显示	VIDOSD1C = 0x000000;

k1:--w1
k2:
k3:
k4:--w0

state == 1 ---> app
state == 2 ---> cmd
***********************************/
void my_alpha(void)
{
	while(1){
#if debug_alpha
		printf("here \n");
#endif
		udelay(10*1000); //50ms
		if (state == APP_BACK)
			break;
		if (ALPHA_W0) {
			udelay(100*1000); //50ms
			if (ALPHA_W0) {
				VIDOSD1C = 0x000000;
			}
		} else if (ALPHA_W1) {
			udelay(100*1000); //50ms
			if (ALPHA_W1) {
				VIDOSD1C = 0xffffff;
			}
		} else if (ALPHA_INC) {
			udelay(100*1000); //50ms
			if (ALPHA_INC) {
				if (VIDOSD1C < 0xffffff) {
					VIDOSD1C += 0x111111;
#if debug_alpha_vaule
					printf("alpha-> %#x\n",VIDOSD1C);
#endif
				}
			}
		} else if (ALPHA_DEC) {
			udelay(100*1000); //50ms
			if (ALPHA_DEC) {
				if (VIDOSD1C > 0x000000) {
					VIDOSD1C -= 0x111111;
#if debug_alpha_value
					printf("alpha-> %#x\n",VIDOSD1C);
#endif
				}
			}
		} else {

		}
	}
	printf("back from alpha \n");
}
