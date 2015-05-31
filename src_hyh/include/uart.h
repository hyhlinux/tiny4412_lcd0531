#ifndef UART_H_
#define UART_H_

#include "common.h"

#define GPA0CON *(u32 *)0x11400000 
typedef struct{
	u32 ULCONn; 		
	u32 UCONn;
	u32 UFCONn; 		
	u32 UMCONn ;		
	u32 UTRSTATn; 	
	u32 UERSTATn;	
	u32 UFSTATn;	
	u32 UMSTATn;	
	u32 UTXHn;		
	u32 URXHn;		
	u32 UBRDIVn; 	
	u32 UFRACVALn; 	
	u32 UINTPn;		
	u32 UINTSPn; 	
	u32 UINTMn; 		
}uart_t;

typedef char *uva_list; 

#define uva_start(ap, argN)  (ap = (uva_list)&argN+sizeof(argN))
#define uva_arg(ap, type)  ({\
		               type tmp=*(type*)ap;\
			       ap += sizeof(type);\
			       tmp;})	
#define uva_end(ap)	(ap = NULL)

extern void uart_init(void);
extern void uputchar(int c);
extern int  ugetchar(void);
extern char *ugets(char *buf);
extern void uputs(char *buf);
extern void xtoa(u32 num, char *buf);
extern void itoa(u32 num, char *buf);
extern int  uprintf(const char *fmt, ...);

#endif
