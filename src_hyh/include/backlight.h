#ifndef __BACKLIGHT_H
#define __BACKLIGHT_H

#define GPX1DAT (*(volatile unsigned int *)(0x11000000 + 0x0C24))
#define GPX1CON (*(volatile unsigned int *)(0x11000000 + 0x0C20))

#define crc8_init(crc) ((crc) = 0XACU)
#define crc8(crc, v) ( (crc) = crc8_tab[(crc) ^(v)])

#define START 		0
#define REQUEST 	1
#define END		2

extern void set_gpx1_2_high(void);
extern void set_gpx1_2_low(void);
extern void do_timer1(void);
extern void set_backlight_start(int backlight);

#endif


