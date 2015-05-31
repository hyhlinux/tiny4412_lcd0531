#ifndef __HYH_PIC20_H
#define __HYH_PIC20_H_

extern void my_pic20(void);
extern void picture_menu(void);
extern void display_ppt(int x,int y);
extern void display_ppt_myppt(int x,int y);
extern void display_ppt_r90(int x,int y);
extern void copy_date2display_myppt(int x, int y, void *pic20_dis);
extern void copy_date2display(int x, int y, void *pic20_dis);
extern void copy_date2display_r90(int x, int y, void *pic20_dis);

#endif
