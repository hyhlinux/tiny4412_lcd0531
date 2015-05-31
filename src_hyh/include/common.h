#ifndef __COMMON_H__
#define __COMMON_H__

typedef volatile unsigned int   u32;
typedef volatile unsigned short u16;
typedef volatile unsigned char  u8;
typedef volatile unsigned int 	u32_t;

typedef long unsigned int size_t;
extern size_t strlen(const char *s);
//IROM
extern int (*copy_sd_mmc_to_mem)(int, int, int);
//UBOOT
extern int (*printf)(const char *, ...);
extern int (*udelay)(int );
extern int (*sdelay)(int );
extern int  my_delay(int ); 
extern void delay(u32 n);

//unsigned long (*get_timer)(unsigned long);
int strcmp(char *cs, const char *ct);

extern void *memcpy(void *__dest, __const void *__src, int __n);
extern int (*get_random_val)(void);//get_random_val
extern void *memset(void *s, int c, int count);


extern void *mymemcpy(void *dest, const void *src, u32 n);
extern char *mystrcpy(char *dst, const char *src);

#define NULL (void *)0
//state == APP_BACK
#define APP_BACK 2
#define debug		 	 0
#define debug_pic	 	 0
#define debug_alpha	 	 0
#define debug_alpha_value 	 1
#define debug_rotator		 1
#define debug_print		 0
#define debug_func 	 	 0
#define debug_func_filp 	 1

#endif 
