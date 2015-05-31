#ifndef __LCD_H_
#define __LCD_H_

#include "common.h"

//gpio  --> lcdinterface
#define GPF0CON 		*((u32_t *)0x11400180)
#define GPF1CON 		*((u32_t *)0x114001a0)
#define GPF2CON 		*((u32_t *)0x114001c0)
#define GPF3CON 		*((u32_t *)0x114001e0)

#define LCDBLK_CFG 		*((u32_t *)0x10010210)
#define CLK_SRC_LCD0		*((u32_t *)0x1003c234)
#define CLK_DIV_LCD		*((u32_t *)0x1003c534)


#define LCDBASE 0x11C00000
/*bus */
#define VIDCON0 		*((u32_t *)(0x0000+LCDBASE)) 
#define VIDCON1 		*((u32_t *)(0x0004+LCDBASE))
#define VIDCON2 		*((u32_t *)(0x0008+LCDBASE))
#define VIDCON3 		*((u32_t *)(0x000C+LCDBASE))
#define VIDTCON0		*((u32_t *)(0x0010+LCDBASE))
#define VIDTCON1		*((u32_t *)(0x0014+LCDBASE))
#define VIDTCON2		*((u32_t *)(0x0018+LCDBASE))
/*w 0/1/2/3/4/5 con */
#define WINCON0 		*((u32_t *)(0x0020+LCDBASE))
#define WINCON1 		*((u32_t *)(0x0024+LCDBASE))
/*bus */
#define SHADOWCON		*((u32_t *)(0x0034+LCDBASE))
#define WINCHMAP2		*((u32_t *)(0x003C+LCDBASE))
/*w0 A B C position */
#define VIDOSD0A 		*((u32_t *)(0x0040+LCDBASE))
#define VIDOSD0B 		*((u32_t *)(0x0044+LCDBASE))
#define VIDOSD0C 		*((u32_t *)(0x0048+LCDBASE)) 
/*w1 A B C  Dposition */
#define VIDOSD1A 		*((u32_t *)(0x0050+LCDBASE))
#define VIDOSD1B 		*((u32_t *)(0x0054+LCDBASE))
#define VIDOSD1C 		*((u32_t *)(0x0058+LCDBASE)) 
#define VIDOSD1D 		*((u32_t *)(0x005c+LCDBASE)) 
/*w0 frambuffer ..buf..0*/
#define VIDW00ADD0B0 		*((u32_t *)(0x00A0+LCDBASE)) 
#define VIDW00ADD1B0 		*((u32_t *)(0x00D0+LCDBASE)) 
/*w1 frambuffer ..buf..0*/
#define VIDW01ADD0B0 		*((u32_t *)(0x00A8+LCDBASE)) 
#define VIDW01ADD1B0 		*((u32_t *)(0x00D8+LCDBASE)) 
/*add start frambuf*/
#define FRAMBUFFER0 		0x60000000
#define FRAMBUFFER1 		0x61000000
//app
//#define SRC_IMAGE 		0x60000000
#define DST_IMAGE 		0x65000000

#define FRAMBUFFER_UI 		0x62000000
#define FRAMBUFFER_ALPHA0 	0x63000000
#define FRAMBUFFER_ALPHA1 	0x64000000

#define FRAMBUFFER_ROTATOR 	0x65000000 //dst--- 
#define FRAMBUFFER_ROTATOR_DEL 	0x66000000 //dst--- 

#define FRAMBUFFER_PIC20DST 	0x68000000 //dst
#define FRAMBUFFER_PIC20DIS 	0x69000000 //display
#define FRAMBUFFER_PIC20SRC 	0x70000000 //src  rotat | pic
#define FRAMBUFFER_PIC20SRC_90 	0x72000000 //src  rotat | pic
#define FRAMBUFFER_PIC15SRC	0x74000000 //src  ppt15
//0x1 000 0000
//1 * 2^28
// 2 ^ 8 ^ M = 256M --> 30M
//0x800000 
//8 * 2^20
// 2 ^ 3 ^ M = 8M
//0x2000000 
//2 * 2^24
// 2 ^ 5 ^ M = 32M
extern void lcd_init(void);
extern void draw_point(int x, int y, int r, int g, int b);

extern void draw_point_char(int x, int y, int col);
extern void clean_lcd(u32 col);
extern void clean_lcd_w1(u32 col);
extern void clean_lcd_w1_PIC(u32 col);
extern void clean_lcd_w1_ROTATOR(u32 col);
extern void write_string(char *str,int i, int j);
//extern void write_word_pos(unsigned char c, int *pos_x, int *pos_y);
extern void write_word_pos(unsigned char c, int pos_x, int pos_y);

#ifdef BPP888
	#define MKCOL(R,G,B) ((R << 16) | (G << 8) | (B << 0))
#else
	#define MKCOL(R,G,B) ((R << 11) | (G << 5) | (B << 0))
#endif

//#define WORD_COL MKCOL(0,0,255)
#define COL_R		MKCOL(255,0,0)
#define COL_G		MKCOL(0,255,0)
#define COL_B		MKCOL(0,0,255)

#define WORD_COL 	COL_R	
#define BACK_COL 	COL_G
#define BACK_BLACK 	MKCOL(0,0,0)
#define BACK_COL1 	COL_B
#define BACK_COL_2 	MKCOL(100,100,100)

#undef FONT22_12
#ifdef FONT22_12
	#define FONT_RAW 22
	#define FONT_COL 12
#else
	#define FONT_RAW 18 
	#define FONT_COL 10
#endif
//------------------------------
#endif
