#include <common.h>
#include <key.h>
#include <uart.h>
#include <rtc.h>
#include <teris.h>

extern int  state;
static void draw_bg_arr(int j); 
static void display_bg(void);
#if DISPLAY
static void display_os1_bg(void);
static void display_os1_2y_bg(void);
#endif 

static void draw_os1_h_arr(void);
static void draw_os1_2y_arr(void);
static void draw_os3_digtal_arr(int flag);
static void draw_os3_digtal_arr_right(int num); 

/*start and over ..*/
static  int  is_game_over(void);
static  void game_over_bg(void);
static  void game_start_bg(void);
static  void shape_init(int n);

static unsigned long last1  = 0;
static unsigned long cur_shape  = 0;
static unsigned long next_shape = 0;
static unsigned long cur_score = 0;
static unsigned long last_score = 0;

extern int tik; //in rtc 

static int bg[HC][WC]; //os: 主操作区
static int os_1_h[N_HC][N_WC] = {
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1}, // 1 h
{0,0,0,1,1,0,0,0},
{0,0,0,1,1,0,0,0},
{1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0}
};
//static int os3_d0[10][D_HC_Y][D_WC_X] = {
static int os3_digtal[11][D_HC_Y][D_WC_X] = {
	{
		{0,1,1,1,1,1,0},
		{0,1,0,0,0,1,0},
		{0,1,0,0,0,1,0},
		{0,1,0,0,0,1,0},
		{0,1,0,0,0,1,0},
		{0,1,0,0,0,1,0},
		{0,1,1,1,1,1,0}
	},
	{
		{0,0,0,0,0,1,0},
		{0,0,0,0,1,1,0},
		{0,0,0,1,0,1,0},
		{0,0,0,0,0,1,0},
		{0,0,0,0,0,1,0},
		{0,0,0,0,0,1,0},
		{0,0,1,1,1,1,1}
	},
	{
		{0,1,1,1,1,1,0},
		{0,0,0,0,0,1,0},
		{0,0,0,0,0,1,0},
		{0,1,1,1,1,1,0},
		{0,1,0,0,0,0,0},
		{0,1,0,0,0,0,0},
		{0,1,1,1,1,1,0}
	},
	{
		{0,1,1,1,1,1,0},
		{0,0,0,0,0,1,0},
		{0,0,0,0,0,1,0},
		{0,1,1,1,1,1,0},
		{0,0,0,0,0,1,0},
		{0,0,0,0,0,1,0},
		{0,1,1,1,1,1,0}
	},
	{
		{0,1,0,0,0,1,0},
		{0,1,0,0,0,1,0},
		{0,1,0,0,0,1,0},
		{0,1,1,1,1,1,0},
		{0,0,0,0,0,1,0},
		{0,0,0,0,0,1,0},
		{0,0,0,0,0,1,0}
	},
	{
		{0,1,1,1,1,1,0},
		{0,1,0,0,0,0,0},
		{0,1,0,0,0,0,0},
		{0,1,1,1,1,1,0},
		{0,0,0,0,0,1,0},
		{0,0,0,0,0,1,0},
		{0,1,1,1,1,1,0}
	},
	{
		{0,1,1,1,1,1,0},
		{0,1,0,0,0,0,0},
		{0,1,0,0,0,0,0},
		{0,1,1,1,1,1,0},
		{0,1,0,0,0,1,0},
		{0,1,0,0,0,1,0},
		{0,1,1,1,1,1,0}
	},
	{
		{0,1,1,1,1,1,0},
		{0,0,0,0,0,1,0},
		{0,0,0,0,0,1,0},
		{0,0,0,0,0,1,0},
		{0,0,0,0,0,1,0},
		{0,0,0,0,0,1,0},
		{0,0,0,0,0,1,0}
	},
	{
		{0,1,1,1,1,1,0},
		{0,1,0,0,0,1,0},
		{0,1,0,0,0,1,0},
		{0,1,1,1,1,1,0},
		{0,1,0,0,0,1,0},
		{0,1,0,0,0,1,0},
		{0,1,1,1,1,1,0}
	},
	{
		{0,1,1,1,1,1,0},
		{0,1,0,0,0,1,0},
		{0,1,0,0,0,1,0},
		{0,1,1,1,1,1,0},
		{0,0,0,0,0,1,0},
		{0,0,0,0,0,1,0},
		{0,1,1,1,1,1,0}
	},
	{
		{0,1,1,1,1,1,0},
		{0,0,0,0,0,1,0},
		{0,0,0,0,0,1,0},
		{0,1,1,1,1,1,0},
		{0,1,0,0,0,1,0},
		{0,1,0,0,0,1,0},
		{0,1,1,1,1,1,0}
	}
};
static int os_2_y[N_HC_Y][N_WC_Y] = {
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},

{0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,0},
{1,0,1,0, 1,0,1,0, 1,0,1,0, 1,0,1,0, 1,0,1,0},

{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{1,1,1,0, 1,1,1,0, 1,1,1,1, 0,1,1,1, 0,1,1,1},
{0,1,0,0, 1,0,0,0, 1,0,0,1, 0,0,1,0, 0,1,0,0},
{0,1,0,0, 1,1,1,0, 1,1,1,1, 0,0,1,0, 0,1,1,1},
{0,1,0,0, 1,0,0,0, 1,0,0,1, 0,0,1,0, 0,0,0,1},
{0,1,0,0, 1,1,1,0, 1,0,0,1, 0,1,1,1, 0,1,1,1},
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},

{0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1},//                 0
{0,0,1,0, 1,0,1,0, 1,0,1,0, 1,0,1,0, 1,0,1,0}, // 1 h

{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}	           //0
};
/*通过索引，查表-- 找到NEXT_cute*/
static int rand_arr[NUM] = {
2, 5, 4, 2, 6,
2, 5, 1, 4, 2, 
3, 2, 3, 2, 6,
5, 1, 1, 5, 5
};
static unsigned long rate  = 0;

int shape[M][N] = {
{0, 0, 0, 0, 0},
{0, 0, 1, 1, 0},
{0, 0, 1, 1, 0},
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0} 
};
int shape_1[M][N] = {
{0, 0, 0, 0, 0},
{0, 0, 1, 1, 0},
{0, 0, 1, 1, 0},
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0} 
};
int shape_2[M][N] = {
{0, 0, 0, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 0, 0, 0} 
};
int shape_3[M][N] = {
{0, 0, 0, 0, 0},
{0, 1, 1, 1, 0},
{0, 0, 1, 0, 0},
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0} 
};
int shape_4[M][N] = {
{0, 0, 0, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 1, 1, 0},
{0, 0, 0, 0, 0} 
};
int shape_5[M][N] = {
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 1, 1, 0},
{0, 0, 0, 0, 0} 
};
int shape_6[M][N] = {
{0, 0, 0, 0, 0},
{0, 1, 0, 0, 0},
{0, 1, 1, 0, 0},
{0, 1, 1, 1, 0},
{0, 0, 0, 0, 0} 
};
/*a windmill 分车 跟随器*/
int shape_windmill[M][N] = {
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0},
{0, 0, 1, 0, 0},
{0, 0, 0, 0, 0},
{0, 0, 0, 0, 0}
};

void board_init(void)
{
	key_init();
//	lcd_init();
	draw_screen_white(0);
	draw_bg();	
/*display GO !*/
	game_start_bg();
	draw_bg_arr(HC-1);  
	udelay(1000*10*2);
/*check key and start gaming **/
	while(!IS_UP)
		printf("tik %d\n",tik);
	shape_init(tik);
	tik = 0;
	draw_bg();	
/*GO end ..*/
	draw_os1_h_arr(); // 同时画出1/3
	draw_os1_2y_arr();
/*score*/
	draw_os3_digtal_arr(0);
	draw_os3_digtal_arr_right(0);
}

int 
my_teris( void )
{
	int x = 0;
	int y = START_Y;
//	int key_cnt = 0;

	board_init();
	tik = 0;

	while (1) {
// 1s/刷新一次
		last1 = CURTICCNT;
		if (tik == 1) {
			draw_shape(shape, x, y, BC_R, BC_G, BC_B);      //back os is green
			draw_both_sides(X/2-W/2, 0); 			//用左边作为参考
		        draw_shape(shape_windmill, WC + 1, 0,RAND_C_R, RAND_C_G, RAND_C_B);
			/*跟新颜色  and 战绩*/
			draw_os1_h_arr(); 	// 同时画出1/3
			draw_os1_2y_arr(); 	// 刷新 TERIS 标签
			/*  检测 是否需要刷分 */
			if ( (cur_score > last_score) || (cur_score <= 10) )  {
				last_score = cur_score%10; 	// 以免数组越界
				//backgroud
			}
			draw_os3_digtal_arr(last_score); 	// 一直都显示
			draw_os3_digtal_arr_right(0);

			if (is_canmov(shape, x, y+1)) {
				y++;
		      		draw_shape(shape, x, y, RAND_C_R, RAND_C_G, RAND_C_B);
				draw_os_line(0);	
			} else {
		        	draw_shape(shape, x, y, RAND_C_R, RAND_C_G, RAND_C_B);
				set_bg(shape, x, y);
				y = START_Y;
				x = last1%4 + 2; 		  //控制x的位置
				init_shape(RAND_C_R);		  //rand_c_r是255%的数 ,模仿 rand()
				rate++;
				if (rate > RATE_A*30)
					rate = 5000;
			}
			tik = 0; //tick = 0;
		}
		check_full_bg();
/////////////////////////////////key control
		if ( IS_LEFT ) { 
			udelay(50*1000); //50ms
			if ( IS_LEFT ) { 
				draw_shape(shape, x, y, BC_R, BC_G, BC_B);     //back os is green
				if ( is_canmov(shape, x-1, y) ) { 
					x--;
				}
				draw_shape(shape, x, y, RAND_C_R, RAND_C_G, RAND_C_B);
				draw_os_line(0);	
			}
		}
		if ( IS_RIGHT ) {
			udelay(50*1000); //50ms
			if ( IS_RIGHT ) {
				draw_shape(shape, x, y, BC_R, BC_G, BC_B);     //back os is green
				if ( is_canmov(shape, x+1, y) ) { 
					x++;
				}
				draw_shape(shape, x, y, RAND_C_R, RAND_C_G, RAND_C_B);
				draw_os_line(0);	
			}
		}
		if ( IS_DOWN ) {
			udelay(50*1000); //50ms
			if ( IS_DOWN ) {
				draw_shape(shape, x, y, BC_R, BC_G, BC_B);     //back os is green
				if ( is_canmov(shape, x, y + 1) ) { 
					y++;
					draw_shape(shape, x, y, RAND_C_R, RAND_C_G, RAND_C_B);
					draw_os_line(0);	
				} else {
					draw_shape(shape, x, y, RAND_C_R, RAND_C_G, RAND_C_B);
					set_bg(shape, x, y);	
					init_shape(last1%100);		  //模仿 rand()
					x = 3;
					y = 0;	
				}
			}
		}
		if ( IS_UP ) {
			udelay(50*1000); //50ms
			if ( IS_UP ) {
				draw_shape(shape, x, y, BC_R, BC_G, BC_B);     //back os is green
				turn_90(shape);
				if ( is_canmov(shape, x, y) ) { 
				} else {
					turn_90(shape);
					turn_90(shape);
					turn_90(shape);
				}
				draw_shape(shape, x, y, RAND_C_R, RAND_C_G, RAND_C_B);
				draw_os_line(0);	
			}
		}
		if ( is_game_over() == 1  ) {
			/*软切换*/	
			game_over_bg();	
			draw_os1_2y_arr(); 		 // 刷新 TERIS 标签
			draw_os3_digtal_arr(last_score); // 一直都显示
			draw_os3_digtal_arr_right(0);
#if debug_game_over
			printf("pc...will go lcd\n");
		  	display_bg();
			return 0;// so back to start.S
#endif
			/* back to start.s */
		}
		if (state == APP_BACK)
			return 0;
	}

	return 0;
}
static int is_game_over(void)
{
	int ret = -1;
	int x; 

	for (x = 0; x < WC; x++) {
		if ( bg[1][x] == 1 ) {
			ret = 1;
		}
	}
	return ret;
}
static  void game_over_bg(void)
{
//  12 15
/*game over ...*/
	int tmp[HC][WC] = {
	{0,0,0,0,0, 0,0,0,0, 0,0,0,0,0,0},			
	{0,0,0,0,0, 0,0,0,0, 0,0,0,0,0,0},			
	{0,0,0,0,0, 0,0,0,0, 0,0,0,0,0,0},			
	{1,1,1,0,0, 1,0,0,1, 0,1,1,1,1,0},			
	{1,0,0,1,0, 1,0,0,1, 0,1,0,0,0,0},			
	{1,0,0,1,0, 1,0,0,1, 0,1,0,0,0,0},			
	{1,1,1,0,0, 1,1,1,1, 0,1,1,1,1,0},			
	{1,0,0,1,0, 0,0,0,1, 0,1,0,0,0,0},			
	{1,0,0,1,0, 0,0,0,1, 0,1,0,0,0,0},			
	{1,1,1,0,0, 0,0,1,1, 0,1,1,1,1,0},			
	{0,0,0,0,0, 0,0,0,0, 0,0,0,0,0,0},			
	{1,0,1,0,1, 0,1,0,1, 0,1,0,1,0,1}
	}; 
	memcpy(bg, tmp, sizeof(tmp));	
	draw_bg();	
	display_bg();
	draw_bg_arr(HC-1); 
	clear_bg();
/*game over ...end enter pc*/
}
static  void game_start_bg(void)
{
/*display GO !*/
	int tmp[HC][WC] = {
	{0,0,0,0,0,0,0, 0, 0,0,0,0,0,0,0},			
	{0,0,0,0,0,0,0, 0, 0,0,0,0,0,0,0},			
	{0,1,1,1,1,1,1, 0, 1,1,1,1,1,0,0},			
	{0,1,0,0,0,0,0, 0, 1,0,0,0,1,0,0},			
	{0,1,0,0,0,0,0, 0, 1,0,0,0,1,0,0},			
	{0,1,0,0,1,1,1, 0, 1,0,0,0,1,0,0},			
	{0,1,0,0,0,0,1, 0, 1,0,0,0,1,0,0},			
	{0,1,0,0,0,0,1, 0, 1,0,0,0,1,0,0},			
	{0,1,1,1,1,1,1, 0, 1,1,1,1,1,0,0},			
	{0,0,0,0,0,0,0, 0, 0,0,0,0,0,0,0},			
	{0,0,0,0,0,0,0, 0, 0,0,0,0,0,0,1},			
	{0,0,0,0,0,0,0, 0, 0,0,0,0,0,0,0}
	}; 
	memcpy(bg, tmp, sizeof(tmp));	
	draw_bg_arr(HC-1); 
	clear_bg();
	//display_bg();
/*GO end ..and clear bg */
}

void display_bg(void)
{
	int x,  y;

	for (y = 0; y < HC; y++) {
		for (x = 0; x < WC; x++) {
			uprintf("%d ",  bg[y][x]);
		}
		printf("\t %d\n",y);
	}
}
#if DISPLAY
void display_os1_bg(void)
{
	int x,  y;

	for (y = 0; y < N_HC; y++) {
		for (x = 0; x < N_WC; x++) {
			uprintf("%d ",  os_1_h[y][x]);
		}
		printf("\t %d\n",y);
	}
}
void display_os1_2y_bg(void)
{
	int x,  y;

	for (y = 0; y < N_HC_Y; y++) {
		for (x = 0; x < N_WC_Y; x++) {
			uprintf("%d ",  os_2_y[y][x]);
		}
		printf("\t %d\n",y);
	}
}

#endif 

void turn_90(int s[M][N])
{
	int i,j;
	int t[M][N] = {};

	for (j = 0; j < M; j++) {
		for (i = 0; i < N; i++) {
			t[j][i] = s[M-i-1][j];
		}
	}
	memcpy(s, t, sizeof(t));
}
void clear_bg(void)
{
	int i, j;
	for (j = 0; j < HC; j++) 
		for (i = 0; i < WC; i++)
			bg[j][i] = 0;
}
void set_bg(int s[M][N], int x, int y) 
{
//在bg[HC][WC] 中记录 s[][]
	int i, j;
	for (j = 0; j < M; j++) {
		for (i = 0; i < N; i++) {
			if (s[j][i] != 0)
				bg[j+y][i+x] = s[j][i];
		}	

	}
}

static void shape_init(int n)
{
	int rand = (n%10)%7 ; //n = tik
	printf("rand %d\n",rand);
	switch(rand) {
	case 1:
		memcpy(shape, shape_1, sizeof(shape));
		break;
	case 2:
		memcpy(shape, shape_2, sizeof(shape));
		break;
	case 3:
		memcpy(shape, shape_3, sizeof(shape));
		break;
	case 4:
		memcpy(shape, shape_4, sizeof(shape));
		break;
	case 5:
		memcpy(shape, shape_5, sizeof(shape));
		break;
	case 6:
		memcpy(shape, shape_6, sizeof(shape));
		break;

	default:
		memcpy(shape, shape_5, sizeof(shape));
		break;
	}
}
/*init_shape init_next_shape*/
void init_shape(int n) 
{
	//int rand = n % 18; //现在就可以认为rand 是一个随机值
	cur_shape ++; // 索引随机表
	cur_shape %= 20;
	uprintf("cur_shape %d\n",cur_shape);

	if (cur_shape+1 > 19 )
		next_shape = 0;
	else  {
		next_shape = cur_shape + 1;
	}
	uprintf("next_shape %d\n",next_shape);

/*init cur_shape*/
	switch(rand_arr[cur_shape]) {
	case 1:
		memcpy(shape, shape_1, sizeof(shape));
		break;
	case 2:
		memcpy(shape, shape_2, sizeof(shape));
		break;
	case 3:
		memcpy(shape, shape_3, sizeof(shape));
		break;
	case 4:
		memcpy(shape, shape_4, sizeof(shape));
		break;
	case 5:
		memcpy(shape, shape_5, sizeof(shape));
		break;
	case 6:
		memcpy(shape, shape_6, sizeof(shape));
		break;

	default:
		memcpy(shape, shape_5, sizeof(shape));
		break;
	}
/*init next_shape*/
	switch(rand_arr[next_shape]) {
	case 1:
		memcpy(shape_windmill, shape_1, sizeof(shape));
		break;
	case 2:
		memcpy(shape_windmill, shape_2, sizeof(shape));
		break;
	case 3:
		memcpy(shape_windmill, shape_3, sizeof(shape));
		break;
	case 4:
		memcpy(shape_windmill, shape_4, sizeof(shape));
		break;
	case 5:
		memcpy(shape_windmill, shape_5, sizeof(shape));
		break;
	case 6:
		memcpy(shape_windmill, shape_6, sizeof(shape));
		break;

	default:
		break;
	}
}
int is_canmov(int s[M][N], int x, int y)
{
	int i, j;
	for (j = 0; j < M; j++) {
		for (i = 0; i < N; i++) {
			if (s[j][i]  != 0 ) {
				if (y + j >= HC)
					return 0;
				if (x + i >= WC)
					return 0;
				if (x + i < 0)
					return 0;
				if (bg[y+j][x+i] != 0)
					return 0;
			}
		}
	}
	return 1;
}
static void draw_bg_arr(int j)
{
	int x, y;
	for (y = j; y > 1; y--) {
		for (x = 0; x < WC; x++ ) {
			if ( bg[y][x] == 1 ) {
				//draw_shape(shape, x, y-1, BC, BC_G, BC);     //back os is green
				draw_element(x, y, FC_R, FC_G, FC_B);   
				draw_element(x, y-1, BC_R, BC_G, BC_B);
			}
		} 
	}		
}
static void draw_os1_h_arr(void) // 1h 2h were called ...
{
	int x, y;
	for (y = 0; y < N_HC; y++) {
		for (x = 0; x < N_WC; x++ ) {
			if ( os_1_h[y][x] == 1 ) {
				//draw_os1_1h_element(x, y, 0, 0, 0);   
				draw_os1_1h_element(x, y, RAND_C_R/2, RAND_C_G/2, RAND_C_B/2);   
				draw_os1_3h_element(x, y, RAND_C_R/2, RAND_C_G/2, RAND_C_B/2);   
				//draw_os1_3h_element(x, y, 0, 0, 0);   
			}
		} 
	}		
}
static void draw_os1_2y_arr(void) // 2y 
{
	int x, y;
	for (y = 0; y < N_HC_Y; y++) {
		for (x = 0; x < N_WC_Y; x++ ) {
			if ( os_2_y[y][x] == 1 ) {
				//draw_os1_2y_element(x, y, 35, 45, 20);   
				draw_os1_2y_element(x, y, RAND_C_R/3, RAND_C_G/2, RAND_C_B/1);   
			}
		} 
	}		
}
static void draw_os3_digtal_arr(int num) // 2y 
{
	int x, y;
	for (y = 0; y < D_HC_Y; y++) {
		for (x = 0; x < D_WC_X; x++ ) {
			/*画出十位*/
			if ( os3_digtal[num][y][x] == 1 ) {
				draw_os3_digtal_element(x, y, RAND_C_R, RAND_C_G, RAND_C_B);   
			}
			/* 画出个位 y + D_WC*/
/*
			if ( os3_digtal[0][y][x] == 1 ) {
				draw_os3_digtal_element(x, y + D_WC_X, RAND_C_R, RAND_C_G, RAND_C_B);   
			} */
		} 

	}		
}
static void draw_os3_digtal_arr_right(int num) // 2y 
{
	int x, y;
	for (y = 0; y < D_HC_Y; y++) {
		for (x = 0; x < D_WC_X; x++ ) {
			/*画出RIGHT位*/
			if ( os3_digtal[num][y][x] == 1 ) {
				draw_os3_digtal_right_element(x, y, RAND_C_R, RAND_C_G, RAND_C_B);   
			}
		} 

	}		
}
void check_full_bg(void)
{
	int i, j;
	int flag_line = 0; //check line is full, and clear line

	for (j = HC-1; j > 0; j--) {
		flag_line = 0;
		for (i = 0; i < WC; i++) {
			if ( bg[j][i] == 1 )  {
				flag_line++;				
			}		
		}
		if ( flag_line == WC ) {
			rate += RATE_A;
			/* 清除一行后 刷新成绩*/
			cur_score++; // 控制战绩, 在main里面刷新战绩
			clear_line(j);
			draw_bg_arr(HC-1); // 从底部往上遍历数组bg[][]
		}  
	}	
}
void drop_move(int shape[M][N], int x, int y)
{
	draw_shape(shape, x, y, BC_R, BC_G, BC_B);     //back os is green

	if (is_canmov(shape, x, y+1)) {
		y++;
		draw_shape(shape, x, y, FC_R, FC_G, FC_B);
	        draw_os_line(0);	
	} else {
		draw_shape(shape, x, y, FC_R, FC_G, FC_B);
		set_bg(shape, x, y);
		y = -1;
		x = last1%5 + 1; 		  //控制x的位置
		init_shape(RAND_C_R);		  //rand_c_r是255%的数 ,模仿 rand()
		rate++;
		if (rate > 1000)
			rate = 500;
	}

}
void mov_up2bot(int j)
{
	int x, y;
	for (y = j; y > 0; y--) 
		for (x = 0; x < WC; x++) 
			if ( bg[y][x] == 0 ) {
				bg[y][x]   = bg[y-1][x];
				bg[y-1][x] = 0;
			}
}
void clear_line(int j)
{
	int x;
	//int y;
	for (x = 0; x < WC; x++) {
		bg[j][x] = 0; 
		draw_element(x, j, BC_R, BC_G, BC_B);//note: 画成绿色
	}
	mov_up2bot(j);
}
void draw_bg_windmill(void)
{
	int i, j;
	int l, t;
	
	l = X/2-W/2;
	t = Y/2-H/2;

	for (j=0; j<5; j++) {
		for (i=0; i<5; i++) {
			if (shape[j][i] == 1) {
				draw_point(i+X/2+W/2, j, BC_R, BC_G, BC_B);
			}
		}
	}
}
/***********************************************************
this func for teris 
122-------------340
***********************************************************/
void draw_line_white(int flag)
{
	int i;
	int j;

	flag = !!flag; // flag = 1: white  0: black
	if (flag)
		flag = 255;

	for (j=0; j<480; j++) {
		udelay(1000*50);
		for(i=0; i<800; i++)
			draw_point(i, j, flag, flag, flag);
	}

}
void draw_screen_white(int flag)
{
	int i;
	int j;
	flag = !!flag; // flag = 1: white  0: black
	if (flag)
		flag = 255;

	for (j=0; j<480; j++) {
		for(i=0; i<800; i++)
			draw_point(i, j, flag, flag, flag);
	}
}
void draw_line(int x0, int y0, int x1, int y1, int c) 
{
	int xstep = x1 > x0 ? 1: -1;
	int ystep = y1 > y0 ? 1: -1;

// c = 0; black
	if (y0 == y1) {
		for (; x0 != x1; x0+=xstep)
			draw_point(x0, y0, c, c, c);
	} else if (x0 == x1) {
		for (; y0 != y1; y0 +=ystep)
			draw_point(x0, y0, c, c, c);
	} else {

	}
	
}
void draw_os_line(int c)
{
	int i;
	int l, t;
	
	l = X/2-W/2;
	t = Y/2-H/2;
	
	for (i=0; i<=HC; i++) {
		draw_line(l, t + i*H/HC, l + W, t + i*H/HC, c);		
	}
	for (i=0; i<=WC; i++) {
		draw_line(l + i*W/WC, t , l + i*W/WC , t + H, c);		
	}
	

}
void draw_os1_line(int c)
{
	int i;
	
	for (i=0; i<=N_HC; i++) {
		draw_line(0, 0 + i*N_H/HC, X, 0 + i*H/HC, c);		
	}
//N_WC 可能越界 
	for (i=0; i<=N_WC; i++) {
		draw_line(0 + i*N_W/N_WC, 0 , 0 + i*N_W/N_WC , Y, c);		
	}
	

}
void draw_both_sides(int postion_x, int flag)
{
	int i, j;
	int l, t;
	
	l = X/2-W/2;
	t = Y/2-H/2;
	
	//for (i=0; i<X/2-W/2; i++) {
	for (i=0; i<postion_x; i++) {
		for (j=0; j<Y; j++) {
			if (flag)
			   	draw_point(i,   j, 127, 255, 1); //选择
			draw_point(X-i, j, 127, 255, 1);
		}
	}
/*从右向左*/
/*
	for (i=X; i>X/2+W/2; i++) {
		for (j=0; j<Y; j++) {
			draw_pint(i, j, 255, 192, 203);
		}
	}	
*/
	
}
void draw_bg(void)
{
	int i, j;
	int l, t;
	
	l = X/2-W/2;
	t = Y/2-H/2;

	draw_both_sides(X/2, 1);

	for(i=X/2-W/2; i<(X/2+W/2); i++) {
		for(j=Y/2-H/2; j<(Y/2+H/2); j++) {
			draw_point(i, j, BC_R, BC_G, BC_B);
		}
	}
//add line 
	draw_os_line(0);
/*
	draw_os1_line(0);
*/
//两侧着色
}
void draw_os1_1h_element(int x, int y, int r, int g, int b)
{
        int i, j;
        int left, top;
	top  = 0;
	left = 0;

        for(j=top+y*(N_H_1/N_HC); j<top+(y+1)*(N_H_1/N_HC); j++) {
                for(i=left+x*(N_W/N_WC); i<left+(x+1)*(N_W/N_WC); i++) {
			draw_point(i, j, r, g, b);
                }
        }
}
void draw_os1_2y_element(int x, int y, int r, int g, int b)
{
        int i, j;
        int left, top;
	top  = 160;
	left = 0;

        for(j=top+y*(N_H_1/N_HC_Y); j<top+(y+1)*(N_H_1/N_HC_Y); j++) {
                for(i=left+x*(N_W/N_WC_Y); i<left+(x+1)*(N_W/N_WC_Y); i++) {
			draw_point(i, j, r, g, b);
                }
        }
}
void draw_os3_digtal_element(int x, int y, int r, int g, int b)
{
        int i, j;
        int left, top;
	top  = Y/2+20;
	left = X/2+W/2+20;

        for(j=top+y*(D_H/D_HC_Y); j<top+(y+1)*(D_H/D_HC_Y); j++) {
                for(i=left+x*(D_W/D_WC_X); i<left+(x+1)*(D_W/D_WC_X); i++) {
			draw_point(i, j, r, g, b);
                }
        }
}
void draw_os3_digtal_right_element(int x, int y, int r, int g, int b)
{
        int i, j;
        int left, top;
	top  = Y/2+20;
	left = X/2+W/2+D_W + 10*2; // 

        for(j=top+y*(D_H/D_HC_Y); j<top+(y+1)*(D_H/D_HC_Y); j++) {
                for(i=left+x*(D_W/D_WC_X); i<left+(x+1)*(D_W/D_WC_X); i++) {
			draw_point(i, j, r, g, b);
                }
        }
}
void draw_os1_3h_element(int x, int y, int r, int g, int b)
{
        int i, j;
        int left, top;
	top  = 320;
	left = 0;

        for(j=top+y*(N_H_1/N_HC); j<top+(y+1)*(N_H_1/N_HC); j++) {
                for(i=left+x*(N_W/N_WC); i<left+(x+1)*(N_W/N_WC); i++) {
			draw_point(i, j, r, g, b);
                }
        }
}



void draw_element(int x, int y, int r, int g, int b)
{
        int i, j;
        int left, top;

        top = Y/2-H/2; 
	left = X/2-W/2;
        for(j=top+y*(H/HC); j<top+(y+1)*(H/HC); j++) {
                for(i=left+x*(W/WC); i<left+(x+1)*(W/WC); i++) {
			draw_point(i, j, r, g, b);
                }
        }
}
void draw_shape(int s[M][N], int x, int y, int r, int g, int b)
{
	int i, j;
	for (j = 0; j < M; j++) {
		for (i = 0; i < N; i++) {
			if (s[j][i] != 0 ) 	
				draw_element(i+x, j+y, r, g, b);
		}
	}
}

