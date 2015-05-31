#include <lcd.h>
#include <rotator.h>
#include <pic20.h>
#include <schdule.h>
#include <key.h>

static int angle = 0;
static int mode  = 0;
static int num_pos = 0;
extern int ts[5][5];
extern int state;
/***************************************************
核心	： 0.旋转	1.翻转 	
	   0-270	 水平/垂直
mode	 : 0 / 1 
rate	 : 0/1/2/3 决定度数： 0/90/180/270
inc	 : rate++
dec	 : rate--
change	 : mode
menu	 : picture_menu
注意w1->roate 和 w1->pic_dis 之间的切换
***************************************************/
static void deal_angle(int *prote);
static void flip_ver_disable(void);
static void flip_hor_disable(void);
void my_rotator(void)
{
	picture_menu(); //已经调用schdule  w1->buf pic_dst
	int x = 2;
	int y = 2;
	int cnt_ver = 0;
	int cnt_hor = 0;
	state = 0;
	mode  = 0;

	while(1) {
		udelay(50*1000); //10ms
		if (state == APP_BACK)
			break;
		if ((state == 1) && (VIDW01ADD0B0 == FRAMBUFFER_PIC20DST)) {
			x = (ts[0][0] / 160);
			y = (ts[0][1] / 120);
#if debug_rotator
			printf("x %d\ny %d\n",x,y);
#endif
			display_ppt(x,y);//w1->buf ---> pic20_dis
			num_pos = y*5 + x;
			//rotator_src_image(y*5+x);//rotator src	
			rotator_src_image(num_pos);//rotator src	
		}else if (VIDW01ADD0B0  == FRAMBUFFER_ROTATOR) { //w1->buf  -->rotator
			rotator(angle);	//w1->buf  --> pic20_dis
		}
/////////////////////////////////////////////////////////////////////////////key  control
		if (ROTATOR_MODE_CHANGE) {
			udelay(100*1000); //10ms
			if (ROTATOR_MODE_CHANGE) {
				mode = !mode;
#if debug_rotator
				printf("a> %d [0: rotator 1: flip]\n",mode);
#endif
			}
		} else if (ROTATOR_INC) {
			udelay(100*1000); //10ms
			if ((ROTATOR_INC) && !mode) {		//rotator
				flip_hor_disable();
				flip_ver_disable();
				angle++;
				angle %= 4;
#if debug_rotator
				printf("inc angle %d\n",angle*90);	
#endif
				schdule_w1_rotator();
			} else if ((ROTATOR_INC) && mode) {	//flip
				cnt_ver++;
				if (cnt_ver == 1) {
					WAIT_ROTAT_END;
					flip_ver();
					start_rotat();
					schdule_w1_rotator();//w1->buf --> rotator
				} else {
					cnt_ver = 0;
					display_ppt(x,y);//w1->buf ---> pic20_dis
				}
			}
		} else if (ROTATOR_DEC) {		 	//rotator
			udelay(100*1000); 
			if ((ROTATOR_DEC) && !mode) {
				if(angle >= 1) {
					angle--;
#if debug_rotator
				printf("dec angle %d\n",angle*90);	
#endif
			//		deal_angle(); // 影响angle
					schdule_w1_rotator();
				}
			} else if ((ROTATOR_DEC) && mode) {
				cnt_hor++;
				if (cnt_hor == 1) {
					WAIT_ROTAT_END;
					flip_hor();
					start_rotat();
					schdule_w1_rotator();//w1->buf --> rottator
				} else {
					cnt_hor = 0;
					display_ppt(x,y);//w1->buf ---> pic20_dis
				}
			}
		} else if (ROTATOR_PIC_MENU) {
			udelay(100*1000); //50ms if (PIC_DIRECTION_CHANGE) { }
			if (ROTATOR_PIC_MENU) {
				picture_menu();//w1->buf -->pic_dst			
				state = 0;
			}
		} else {

		}
	}
}
void rotator_src_image(int num)
{
#if debug_func 
	printf("%s num_pos %d arg:num %d\n",__func__,num_pos,num);
#endif
        SRCBASEADDR0 = (FRAMBUFFER_PIC20SRC+800*480*num*4);
       // SRCBASEADDR0 = (FRAMBUFFER_PIC20SRC_90+800*480*num*4); //test ok
}
void rotator_src_image_deal_90(int num)
{
#if debug_func 
	printf("%s num_pos %d arg:num %d\n",__func__,num_pos,num);
#endif
        SRCBASEADDR0 = (FRAMBUFFER_PIC20SRC_90+800*480*num*4);
}
void rotator_src_image_deal_270(int num)
{
// 使用r90 + rate = 2
//        SRCBASEADDR0 = (FRAMBUFFER_PIC20SRC_270+800*480*num*4);
}
void flip_ver(void)
{
#if debug_func_filp
	printf("%s \t up<->donw\n",__func__);	
#endif
	CONTROL &= ~(0x3 << 6);
	CONTROL |= 0x2 << 6;
}
static void flip_ver_disable(void)
{
	CONTROL &= ~(0x3 << 6);
}
void flip_hor(void)
{
#if debug_func_filp
	printf("%s\t left<->right\n",__func__);	
#endif
	CONTROL &= ~(0x3 << 6);
	CONTROL |= 0x3 << 6;
}
static void flip_hor_disable(void)
{
	CONTROL &= ~(0x3 << 6);
}
void start_rotat(void)
{
	CONTROL |= 0x1;
}
#if 1
void  rotator(int rote)
{
        CONFIG = 0;
        //CONTROL = (0x6<<8) | (0x0<<6) | ((rote&0x3)<<4);
        CONTROL &= ~((0x7<<8) | ((0x3)<<4));
	//printf("%s %d\n",__func__, rote);
        //CONTROL |= (0x6<<8)  | ((rote&0x3)<<4);
	//rotator_src_image(num_pos);	
	deal_angle(&rote);
        CONTROL |= (0x6<<8)  | ((rote&0x3)<<4);
        //CONTROL = (0x6<<8)  | ((rote&0x3)<<4); 会影响翻转

        SRCIMGSIZE = (480<<16) | (800);
        SRC_XY = 0;
        SRCROTSIZE = (480<<16) | (800);

        DSTBASEADDR0 = FRAMBUFFER_ROTATOR;

        if (rote%2 == 0) {
                DSTIMGSIZE = (480<<16) | (800);
                DST_XY = 0; //dst_y = 0 显示时从0行开始显示。
        }else {
                DSTIMGSIZE = (800<<16) | (800);
                DST_XY = 160; //dst_x =150 从x=150出开始显示.
        }
        //CONTROL |= 0x1;
	start_rotat();
}
#endif 
static void deal_angle(int *prote) 
{
#if debug_func 
	printf("%s\n",__func__);
#endif

	switch (*prote) {
		case 0: 
			rotator_src_image(num_pos);//rotator src	
			break;
		case 1: 
			rotator_src_image_deal_90(num_pos);//rotator src	
			*prote = 0;
			//printf("%s 90 angle %d\n",__func__,*prote);
			break;
		case 2: 
			rotator_src_image(num_pos);//rotator src	
			break;
		case 3: 
			rotator_src_image_deal_90(num_pos);//rotator src	
			*prote = 2;
			//printf("%s 270 angle %d\n",__func__,*prote);
			break;
		default :
			printf("erro %s\n",__func__);
			break;
	}
} 
