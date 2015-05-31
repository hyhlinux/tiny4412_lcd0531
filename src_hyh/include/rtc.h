#ifndef RTC_H_
#define RTC_H_

#include "common.h"

extern void rtc_interrupt_init(void);
extern void settime(u32 h, u32 m);
extern void setalarm(u32 h, u32 m);
extern unsigned long get_timer(void);

#define ALARM_INT  76
#define TIC_INT  77 
#define LEVEL    0

#define GPD0CON  *(u32 *)0x114000a0
#define GPD0DAT  *(u32 *)0x114000a4
#define INTP   		*(u32 *)0x10070030 
#define RTCCON 		*(u32 *)0x10070040 
#define TICCNT 		*(u32 *)0x10070044 
#define RTCALM 		*(u32 *)0x10070050 
#define ALMSEC 		*(u32 *)0x10070054 
#define ALMMIN 		*(u32 *)0x10070058 
#define ALMHOUR		*(u32 *)0x1007005C 
#define ALMDAY 		*(u32 *)0x10070060 
#define ALMMON 		*(u32 *)0x10070064 
#define ALMYEAR		*(u32 *)0x10070068 
#define BCDSEC 		*(u32 *)0x10070070 
#define BCDMIN 		*(u32 *)0x10070074 
#define BCDHOUR		*(u32 *)0x10070078 
#define BCDDAYWEEK 	*(u32 *)0x1007007C 
#define BCDDAY 		*(u32 *)0x10070080 
#define BCDMON 		*(u32 *)0x10070084 
#define BCDYEAR 	*(u32 *)0x10070088 
#define CURTICCNT 	*(u32 *)0x10070090 


#endif
