#include <uart.h>
#include <buzzer.h>

uart_t *uart0 = (void *)0x13800000;

void uart_init(void)
{
	/*将GPA0端口的0，1引脚设置为串口专用*/
	GPA0CON &= ~0xffff;
	GPA0CON |= 0x22;

	uart0->ULCONn = 0x3;  //8N1
	uart0->UCONn  = (0x1 << 0) | (0x1 << 2);//设置收发为查询方式
	uart0->UMCONn = 0; //禁用硬件流控功能

	/*
 	 *	DIV_VAL = UBRDIVn + UFRACVALn/16
 	 *	DIV_VAL = (SCLK_UART/(bps*16)) - 1
 	 *
 	 * 	设置串口通讯的波特率为115200
 	 * */
	uart0->UBRDIVn = 53;
	uart0->UFRACVALn = 4;
}

#define WAIT_REC while(!(uart0->UTRSTATn&0x1))
#define WAIT_TRM while(!(uart0->UTRSTATn&(0x1 << 1)))

void uputchar(int c)
{
	WAIT_TRM;

	uart0->UTXHn = c;

	if(c == '\n'){
		uputchar('\r');
	}
}

int ugetchar(void)
{
	int c;

	WAIT_REC;
	
	buzzer_on();

	c = uart0->URXHn;

	if(c == '\r'){
		c = '\n';
	}

	if(c == '\b'){
		uputchar('\b');
		uputchar(' ');
	}

	uputchar(c);

	return c;
}

char *ugets(char *buf)
{
	int tmp;
	char *tbuf = buf;

	while((tmp = ugetchar()) != '\n'){
		*buf++ = tmp;
	}

	*buf = '\0';
	return tbuf;
}

void uputs_(char *buf)
{
	while(*buf){
		uputchar(*buf++);
	}
}

void uputs(char *buf)
{
	uputs_(buf);
	uputchar('\n');
}
//ad --> "ad"
void xtoa(u32 num, char *buf)
{
	int i;

	if(num < 16){
		if(num > 9){
			buf[0] = num - 10 + 'a';
		}else{
			buf[0] = num + '0';
		}
		buf[1] = '\0';
		return;
	}

	xtoa(num/16, buf);

	for(i = 0; buf[i] != '\0'; i++){
		;
	}

	if(num%16 < 10){
		buf[i] = num%16 + '0';
	}else{
		buf[i] = num%16 - 10 + 'a';
	}

	buf[i+1] = '\0';
}

void itoa(u32 num, char *buf)
{
	int i;
	if(num < 10){
		buf[0] = num + '0';
		buf[1] = '\0';
		return;
	}

	itoa(num/10, buf);

	for(i = 0; buf[i] != '\0'; i++){
		;
	}

	buf[i] = num%10 + '0';
	buf[i+1] = '\0';
}

//%c,%d,%x,%s   uprintf("%d", 95273856);
int uprintf(const char *fmt, ...)
{
	uva_list ap;
	
	int num;
	char buf[32];

	uva_start(ap, fmt);

	while(*fmt){
		if(*fmt == '%'){
			fmt++;
			switch(*fmt){
				case 'c':
					uputchar(uva_arg(ap, int));
					break;
				case 'x':
					num = uva_arg(ap, int);
					xtoa(num, buf);
					uputs_(buf);
					break;
				case 's':
					uputs_(uva_arg(ap, char *));
					break;
				case 'd':
					num = uva_arg(ap, int);	
					if(num < 0){
						uputchar('-');
						num = 0 - num;
					}			
					itoa(num, buf);
					uputs_(buf);
					break;
				default:
					return -1;
			}
		}else{
			uputchar(*fmt);
		}
		fmt++;
	}

	uva_end(ap);	

	return 0;
}


