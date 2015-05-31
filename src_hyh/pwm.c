#include <pwm.h>
#include <common.h>

void timer1_init(int cycle)
{
	//100M / 16  = 6250000 HZ
	TCFG0 &= ~0xff;
	TCFG0 |= 15;
	
	TCFG1 &= ~(0xf << 4);

	TCNTB1 = 0x28a;
	TCMPB0 = 0x1e8480;

	TCON &= ~(0xf << 8);
	TCON |= (1 << 11) | (1 << 9) | (1 << 8);
	TCON &= ~(1 << 9);

	TINT_CSTAT |= 1 << 1;
}

void stop_timer1(void)
{
	TCON &= ~(0xf << 8);
}

