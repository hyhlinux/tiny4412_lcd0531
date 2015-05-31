
#ifndef __MY_TERIS_H__
#define __MY_TERIS_H__

#include "lcd.h"
/*lcd.h*/
/*lcd srcen size*/
#define X 800
#define Y 480
/*shape size*/
#define M 5
#define N 5
/*os 0 teris start  */ 
#define H 480
#define W 450
#define HC 12
#define WC 15
/*os 1 name*/
#define N_H  480
#define N_H_1 160
#define N_HC  8 
#define N_HC_Y  20  // 对应于 N_WC_Y
#define N_W  160 //超界 所以数组的最后一列不可以写， 180/20=9 > 5 所以不会影响os0
#define N_WC  8 
#define N_WC_Y  20 
/*os 3  digtal section */
#define D_H     210
//#define D_W     160 
#define D_W     70 
#define D_WC_X  7 
#define D_HC_Y  7 

// color  front / back   
/*FC红橙色*/
#define FC_R  240 
#define FC_G  60 
#define FC_B  10 
/*bc black*/
#define BC_R  5 
#define BC_G  2 
#define BC_B  1 
//////////////////////////////////////////////////////
/* teris.c */
#define KEY_CNT_L  50
#define KEY_CNT_R  50
#define KEY_CNT_U  35
#define KEY_CNT_D  10

#define RAND_C_R  (((CURTICCNT%1000)/1)%255)
#define RAND_C_G  (((CURTICCNT%2000)/2)%255)
#define RAND_C_B  (((CURTICCNT%3000)/3)%255)

#define START_Y	  -2
#define RATE_A    50000
#define NUM 	  20 
#define IS_GAME_OVER ()
/*debug info  */
#define debug_printf  0
#define debug_game_over 1
#define DISPLAY 0

/***********lcd.c**********/
extern void draw_line_white(int flag);
extern void draw_screen_white(int flag);
extern void draw_bg(void);
extern void draw_line(int x0, int y0, int x1, int y1, int c);
extern void draw_os_line(int c); //x, y lines
extern void draw_element(int x, int y, int r, int g, int b);
//extern void draw_os1_element(int x, int y, int r, int g, int b);
extern void draw_os1_1h_element(int x, int y, int r, int g, int b);
extern void draw_os1_2y_element(int x, int y, int r, int g, int b);
extern void draw_os1_3h_element(int x, int y, int r, int g, int b);
extern void draw_os3_digtal_element(int x, int y, int r, int g, int b);
extern void draw_os3_digtal_right_element(int x, int y, int r, int g, int b);
extern void draw_shape(int s[M][N], int x, int y, int r, int g, int b);
//extern void draw_bg_windmill(void);
extern void draw_both_sides(int postion_x, int flag);
/*os 1*/
extern void draw_os1_line(int c);
//////////////////////////////////////////////////////////////////////////
extern void init_shape(int n);
extern void clear_bg(void);
extern void set_bg(int s[M][N], int x, int y);
extern void draw_bg_arry( int j);
extern int  is_canmov(int s[M][N], int x, int y);
extern void check_full_bg(void);
extern void draw_bg_arry( int j);
extern void clear_line(int j);
extern void mov_up2bot(int j); //整体搬移，把上一层的mov到下一层，清空上一层
extern void turn_90(int s[M][N]);
extern void draw_bg_windmill(void);

//this func for main call
extern int my_teris(void);
#endif
