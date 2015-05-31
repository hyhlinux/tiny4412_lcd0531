#include <buzzer.h>

void buzzer_init(void)
{
	GPD0CON &= ~(0xf);	
	GPD0CON |= 0x1;
}
void buzzer_on(void)
{
	GPD0DAT |= 0X1;
}
void buzzer_off(void)
{
	GPD0DAT &= ~0X1;
}



