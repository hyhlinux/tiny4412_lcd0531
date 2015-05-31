#include <lcd.h>
#include <common.h>
#include <schdule.h>
#include <pic20.h>
#include <myppt.h>

extern int state;
extern int tik;
void ppt_menu(void)
{
	schdule_w1_pic20();
        int *dst = (void *)(FRAMBUFFER_PIC20DST);
        int *src = (void *)(FRAMBUFFER_PIC15SRC);


        int x, y;
        for (x=0; x<800; x++)
                for (y=0; y<480; y++) {
                        dst[y*800+x] = src[((y/160)*5+x/160)*480*800 + \
					(y%160)*3*800+(x%160*5)];
        }
}

void my_ppt(void)
{
//	picture_menu();//w1->buf  --> pic20_dst
	tik = 0;
	while(tik < 8)
		ppt_menu();//w1->buf  --> pic20_dst

	//double_hit = 0;
	int x = 0, y = 0;
	state = 0;
	tik = 0;
	while(1){
		udelay(10*1000); //10ms
		if (state == APP_BACK)
			break;

		if (tik == 2) {
			 x++;
                         x %= 15;
                         y = 0;
                         tik = 0;
		}

		display_ppt_myppt(x,y);//w1->buf ---> pic20_dis
	}
	printf("back from myppt \n");
}
