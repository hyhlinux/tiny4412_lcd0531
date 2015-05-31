#include <lcd.h>
#include <font10_18.h>
#include <font12_22.h>
#include <backlight.h>

//extern const unsigned char fontdata10x18[FONTDATAMAX];
//extern const unsigned char fontdata_sun12x22[FONTMAX];

static void gpio_init(void);
static void lcd_clksrc_set(void);
static void win0_init(void);
static void win1_init(void);

#define BPP888 SUIYI

void lcd_init(void)
{
	set_backlight_start(127);
	gpio_init();
	lcd_clksrc_set();


	VIDCON0 = (2 << 6);
	VIDCON1 = (1 << 5) | (1 << 6) | (1 << 7) | (1 << 9);//	
	LCDBLK_CFG |= 1 << 1; //P12 33.3
	VIDTCON0 = (12 << 16) | (21 << 8) | (9 << 0);
	VIDTCON1 = (25 << 16) | (209 << 8) | (19 << 0);
	VIDTCON2 = (479 << 11) | (799 << 0);

	win0_init();	
	win1_init();	

	VIDCON0 |= 3;
}

static void win0_init(void)
{
#ifdef BPP888
	 WINCON0 = (1 << 15) | (0xb << 2) | (1 << 0);
	 VIDOSD0C = 800*480;
#else
	 WINCON0 = (1 << 16) | (0x5 << 2) | (1 << 0);
	 VIDOSD0C = 800*480 >> 1;
#endif
	WINCHMAP2 &= ~(0x7 << 16);
	WINCHMAP2 |= (0x1 << 16);

	WINCHMAP2 &= ~0x7;
	WINCHMAP2 |= 0x1 << 0;

	SHADOWCON &= ~(1 << 5);
	SHADOWCON |= 1;

	VIDOSD0A = 0;
	VIDOSD0B = (799 << 11) | (479 << 0);

	VIDW00ADD0B0 = FRAMBUFFER0;
	VIDW00ADD1B0 = FRAMBUFFER0 + VIDOSD0C*4; 
}
static void win1_init(void)
{

#ifdef BPP888
	 WINCON1 = (1 << 15) | (0xb << 2) | (1 << 0);
	 VIDOSD1D = 800*480;
#else
	 WINCON1 = (1 << 16) | (0x5 << 2) | (1 << 0);
	 VIDOSD1D = 800*480 >> 1;
#endif
	WINCHMAP2 &= ~(0x7 << 19);
	WINCHMAP2 |= (0x2 << 19);

	WINCHMAP2 &= ~(0x7 << 3);
	WINCHMAP2 |= 0x2 << 3;

	SHADOWCON &= ~(1 << 6);
	SHADOWCON |= 1 << 1;

	VIDOSD1A = 0; //left-top
	//VIDOSD1A = (240 << 0) | (400 << 11); //left-top
	VIDOSD1B = (799 << 11) | (479 << 0);
	/*ALPHA 24bit:  0xffffff(w1 完全显示， 覆盖W0) --> 0x000000*/
	//VIDOSD1C = 0xffffff;
	VIDOSD1C = 0x555555;

/*w1...frambuffer0*/
	VIDW01ADD0B0 = FRAMBUFFER1;
	VIDW01ADD1B0 = FRAMBUFFER1 + VIDOSD1C*4; 
}

static void gpio_init(void)
{
	GPF0CON &= ~0xffffffff;//
	GPF0CON |= 0x22222222;
	GPF1CON &= ~0xffffffff;
	GPF1CON |= 0x22222222;
	GPF2CON &= ~0xffffffff;
	GPF2CON |= 0x22222222;
	GPF3CON &= ~0xffff;
	GPF3CON |= 0x2222;
}

//set sclk_fimd = 100MHz
static void lcd_clksrc_set(void)
{
	CLK_SRC_LCD0 &= ~0xf;
	CLK_SRC_LCD0 |= 0x6;

	CLK_DIV_LCD &= ~0xf;
	CLK_DIV_LCD |= 0x7;
}
//this for string 
void draw_point_char(int x, int y, int col)
{
#ifdef BPP888
        u32 *p = (void *)FRAMBUFFER0;
#else
        u16 *p = (void *)FRAMBUFFER0;
#endif
        *(p + y*800 + x) =      col;
}
//this for teris
void draw_point(int x, int y, int r, int g, int b)
{
	//unsigned int *p = (unsiged int *)FRAMBUFFER0;
	unsigned int *p = (unsigned int *)FRAMBUFFER1;

	*(p + y*800 + x) = (r << 16) | (g << 8) | b;
}
/******************************************************************
this func was write by millet: 1503

******************************************************************/
/*
 * 功能：清屏 
 * 参数：$0:颜色
 */
void clean_lcd(u32 col)
{
	u32 *p = (void*)FRAMBUFFER0;
	int i;
	for (i=0; i<800*480; i++) {
		p[i] = col;
	}
}
void clean_lcd_w1(u32 col)
{
	u32 *p = (void*)FRAMBUFFER1;
	int i;
	for (i=0; i<800*480; i++) {
		p[i] = col;
	}
}
void clean_lcd_w1_PIC(u32 col)
{
	u32 *p = (void*)FRAMBUFFER_PIC20DIS;
	int i;
	for (i=0; i<800*480; i++) {
		p[i] = col;
	}
}
void clean_lcd_w1_ROTATOR(u32 col)
{
	u32 *p = (void*)FRAMBUFFER_ROTATOR;
	int i;
	for (i=0; i<800*480; i++) {
		p[i] = col;
	}
}
void write_word_pos(unsigned char c, int pos_x, int pos_y)
{
	int i,j;
	u16 cchar;

	if(c == '\n'){
		pos_y += FONT_RAW;
		if(pos_y > 479 - FONT_RAW){
			pos_y = 0;
			clean_lcd(BACK_COL);
		}
		return;
	}

	if(c == '\r'){
		pos_x = 0;
		return;
	}
//check pos  x [0-799] y [0-479]
	if(pos_x > 799 - FONT_COL){
		pos_x = 0;
		pos_y += FONT_RAW;
		if(pos_y > 479 - FONT_RAW){
			pos_y = 0;
			clean_lcd(BACK_COL);
		}
	}
#ifdef FONT12_22
	const unsigned char *p = &fontdata_sun12x22[c*22*2]; 
#else
	const unsigned char *p = &fontdata10x18[c*18*2];
#endif 	
	for(i = 0; i < FONT_RAW; i++){
		cchar = (p[2*i] << 8) | p[2*i+1];	 
		for(j = 0; j < FONT_COL; j++){ 
			if(0x8000&(cchar << j)){  
				draw_point_char(pos_x+j, pos_y+i, WORD_COL);
			}		
		}
	}
//	x += FONT_COL;
}
/*****************************************
func_name : write_string 
arg		  : char *str, like as "hello world"
		   i,j is positions in screen [800*480]
dscription: 
		  display a string in screen, start (i,j)
	   	  x=i y=j;
note	  :
		  x += FONT_COL;
		  j +=FONT_RAW;
		when you call write_string ,you must know 
		where you position and you can call 
		clean_lcd(BACK_COL) first;
		x,y = x+FONT_COL , y = y+FONT_RAW	
*****************************************/
void write_string(char *str,int i, int j)
{
 	char *tmp = str;
	for (; *tmp != '\0'; tmp++,i+=FONT_COL) {
//		printf("*tmp = %c i=%d j=%d\n",*tmp, i, j);
		if (i > 800) {
			i -= 800;
			j+=FONT_RAW;
		}
		if (*tmp == '\n') {
			i = 0;
			j+=FONT_RAW;
			write_word_pos(*tmp, i, j);
			tmp++;
		}
		write_word_pos(*tmp, i, j);
	}
}
