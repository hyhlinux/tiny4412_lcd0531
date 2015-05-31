
#include <common.h>

//IROM
//int (*copy_sd_mmc_to_mem)(int , int , int ) = (void *)(*(unsigned int *)(0x02020030));
//UBOOT
int (*printf)(const char *, ...) = (void *)0x43e11434; 
int (*udelay)(int ) = (void *)0x43e25e88;
int (*sdelay)(int ) = (void *)0x43e04ddc;      
//unsigned long (*get_timer)(unsigned long) = (void *)0x43e04f38;
//..int rtc
int (*get_random_val)(void) = (void *)0x43e1fe54;//get_random_val

void delay(u32 n)
{
	int i,j;
	for(i = 0; i < n; i++){
		for(j = 0; j < 50000; j++){
			;
		}
	}
}


int strcmp(char *cs, const char *ct);
void *memcpy(void *__dest, __const void *__src,int __n);
void *memset(void *s, int c, int count);
void *mymemcpy(void *dest, const void *src, u32 n);
char *mystrcpy(char *dst, const char *src);

extern void uart_init(void);
extern void uputchar(int c);
extern int  ugetchar(void);
extern char *ugets(char *buf);
extern void uputs(char *buf);
extern void xtoa(u32 num, char *buf);
extern void itoa(u32 num, char *buf);
extern int  uprintf(const char *fmt, ...);


/**
 * strlen - Find the length of a string
 * @s: The string to be sized
 */
size_t strlen(const char *s)
{
        const char *sc;

        for (sc = s; *sc != '\0'; ++sc)
                /* nothing */;
        return sc - s;
}

void *memset(void *s, int c, int count)
{
	char *xs = s;
	while (count--)
		*xs++ = c;
	return s;
}


int  my_mdelay(int n) 
{
	if(n>0)
		return 	udelay(1000*n);
	return -1;
}
int strcmp(char *cs, const char *ct)
{
	unsigned char c1, c2;
	int res = 0;

	do {
		c1 = *cs++;
		c2 = *ct++;
		res = c1 - c2;
		if (res)
			break;
	} while (c1);
	return res;
}
void *memcpy(void *__dest, __const void *__src, int  __n)
{
	int i = 0;
	unsigned char *d = (unsigned char *)__dest, *s = (unsigned char *)__src;

	for (i = __n >> 3; i > 0; i--) {
		*d++ = *s++;
		*d++ = *s++;
		*d++ = *s++;
		*d++ = *s++;
		*d++ = *s++;
		*d++ = *s++;
		*d++ = *s++;
		*d++ = *s++;
	}

	if (__n & 1 << 2) {
		*d++ = *s++;
		*d++ = *s++;
		*d++ = *s++;
		*d++ = *s++;
	}

	if (__n & 1 << 1) {
		*d++ = *s++;
		*d++ = *s++;
	}

	if (__n & 1)
		*d++ = *s++;

	return __dest;
}
//lib.c 
void *mymemcpy(void *dest, const void *src, u32 n)
{
	char *dt = dest;
	const char *sr = src;

	while(n--){
		*dt++ = *sr++;
	}

	return dest;
}
char *mystrcpy(char *dst, const char *src)
{
	char *tmp = dst;
	while(*src){
		*dst++ = *src++;
	}
	*dst = '\0';

	return tmp;
}
