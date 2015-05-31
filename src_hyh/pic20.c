#include <lcd.h>
#include <common.h>
#include <key.h>
#include <schdule.h>
#include <pic20.h>

int direct_x = 0;
extern int state;
/***********************************
核心操作：	相册预览
-----------------------------------
k1:
k2:
k3:
k4:
--------------------------在ui界面
state == 1 ---> app
state == 2 ---> cmd
---------------------------
state == APP_BACK ---> 2 
---------------------------x_size: 800/5=160
1	|2	|3	|4	|5
6	|7	|8	|9	|10
11	|12	|13	|14	|15
16	|17	|18	|19	|20
---------------------------y_size: 480/4=120
*positon:
		x = ts[0][0] / 160  --[0,4]
		y = ts[0][1] / 120  --[0,3]

*	: 对应(x,y)-->app(0,0)---(4,3)
******************************************/
extern int ts[5][5];
extern int double_hit;


void my_pic20(void)
{
	picture_menu();//w1->buf  --> pic20_dst

	//double_hit = 0;
	int x = 2, y = 2;
	state = 0;

	while(1){
		udelay(10*1000); //10ms
		if (state == APP_BACK)
			break;

		if ((state == 1) && (VIDW01ADD0B0 == FRAMBUFFER_PIC20DST)) {
			x = (ts[0][0] / 160);
			y = (ts[0][1] / 120);
#if debug_pic 
			printf("x %d\ny %d\n",x,y);
#endif 
			display_ppt(x,y);//w1->buf ---> pic20_dis
		}

////////////////////////////////////////////////////key control
		if (PIC_DIRECTION_CHANGE) {
			udelay(100*1000); //50ms
			if (PIC_DIRECTION_CHANGE) {
#if debug_printf 
				printf("b^ %d\n",direct_x);
#endif 
				direct_x = !direct_x; //!!!direct_x;
				printf("%d [1:x left<-->right   0:y up<-->down ]\n",direct_x);
#if debug_printf 
				printf("a^ %d\n",direct_x);
#endif 
			}
		} else if (PIC_INC) {
			udelay(10*1000); //10ms
			if (direct_x) {
				x++;
				if (x == 5)
					y++, y %= 4;
				x %= 5;
#if debug_pic 
				printf("inc x:%d\n",x);
#endif
			}
			else  {
#if debug_pic
				printf("inc y:%d\n",y);
#endif
				y++, y %= 4;
			}
			display_ppt(x,y);//w1->buf ---> pic20_dis
		} else if (PIC_DEC) {
			udelay(10*1000); //10ms
			if (PIC_DEC) {
				if (direct_x && (x >= 0)) {
						x--;
						if((x < 0) && (y > 0))
							y--, y %= 4, x = 4;
						x %= 5;
#if debug_pic 
					printf("dec x:%d\n",x);
#endif
				}
				else  {
					if (y > 0)
						y--; //回到上一行
#if debug_pic 
					printf("dec y:%d\n",y);
#endif
				}
				display_ppt(x,y);//w1->buf ---> pic20_dis
			}
		} else if (PIC_MENU) {
			udelay(10*1000); //10ms
			if (PIC_MENU) {
				picture_menu();//w1->buf ---> pic_dst
				state = 0;
			}
		} else {

		}
	}
	printf("back from pic20 \n");
}
void picture_menu(void)
{
	schdule_w1_pic20();
        int *dst = (void *)(FRAMBUFFER_PIC20DST);
        int *src = (void *)(FRAMBUFFER_PIC20SRC);

        int x, y;
        for (x=0; x<800; x++)
                for (y=0; y<480; y++) {
                        dst[y*800+x] = src[((y/120)*5+x/160)*480*800 + \
					(y%120)*4*800+(x%160*5)];
        }
}
/***************************************
copy_date2display:
	copy from pic20_src
	copy to   pic20_dst
		both by x,y
	num = y*5 + x 
***************************************/
void copy_date2display_myppt(int x, int y, void *pic20_dis)
{ 
        int *dst = (void *)(pic20_dis);
        int *src = (void *)(FRAMBUFFER_PIC15SRC); //ppt
        int i;

	if (((y*5+x) >= 15) || (y*5+x < 0 )) //最小在调用方处理，为了安区再次处理，程序猿必须保证在自己的函数不出错
		x = 0,y = 0;
        src += (y*5+x)*800*480;

        for (i=0; i<480*800; i++) {
                dst[i] = src[i];
        }

}
void copy_date2display(int x, int y, void *pic20_dis)
{ 
        int *dst = (void *)(pic20_dis);
        int *src = (void *)(FRAMBUFFER_PIC20SRC);
        //int *src = (void *)(FRAMBUFFER_PIC20SRC_90); for test pic20_90, is ok
        int i;

	if (((y*5+x) >= 20) || (y*5+x < 0 )) //最小在调用方处理，为了安区再次处理，程序猿必须保证在自己的函数不出错
		x = 0,y = 0;
        src += (y*5+x)*800*480;

        for (i=0; i<480*800; i++) {
                dst[i] = src[i];
        }

}
void copy_date2display_r90(int x, int y, void *pic20_dis)
{ 
        int *dst = (void *)(pic20_dis);
        //int *src = (void *)(FRAMBUFFER_PIC20SRC);
        int *src = (void *)(FRAMBUFFER_PIC20SRC_90); //for test pic20_90, is ok
        int i;

        src += (y*5+x)*800*480;
	if ((y*5+x) >= 20 )
		x=0,y=0;
        for (i=0; i<480*800; i++) {
                dst[i] = src[i];
        }

}
void display_ppt_myppt(int x,int y)
{
//step1: copy_date_source --> display
	 copy_date2display_myppt(x, y,(void *)FRAMBUFFER_PIC20DIS);		
//step2: schdule_w1
	schdule_w1_pic20_display();
#if debug 
	printf("%s\n",__func__);
#endif
}
void display_ppt(int x,int y)
{
//step1: copy_date_source --> display
	 copy_date2display(x, y,(void *)FRAMBUFFER_PIC20DIS);		
//step2: schdule_w1
	schdule_w1_pic20_display();
#if debug 
	printf("%s\n",__func__);
#endif
}
void display_ppt_r90(int x,int y)
{
//step1: copy_date_source --> display
	 copy_date2display_r90(x, y,(void *)FRAMBUFFER_PIC20DIS);		
//step2: schdule_w1
	schdule_w1_pic20_display();
#if debug 
	printf("%s\n",__func__);
#endif
}
