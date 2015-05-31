#include <common.h>
#include <iic.h>
#include <irq.h>

void iic1_init(int addr)
{
	iic1_gpio_init();
		
	I2CADD = addr; //Flowcharts of Operations in Each Mode 1

	I2CCON = (1<<7)|(1<<6)|(1<<5); //196KHz
	
	I2CSTAT = 1 << 4; //Flowcharts of Operations in Each Mode 3
}

void iic1_gpio_init(void)
{
	GPD1CON &= ~(0xff << 8);
	GPD1CON |= 0x22 << 8;
}

void resume_iic_scl(void)
{
	I2CCON &= ~(1<<4);
}

int wait_until_iic_irq(void)
{
	int i;

	#define MAX_WAIT  0x3fff

	for (i = 0; i < MAX_WAIT; i++)
	{	
		if (I2CCON & (1<<4))	
			return 0;
	}
	return -1;
}

void i2c_delay(int val)
{
        val *= 66; 

        while (val--)
                ;   
}

int read_data(char *data, int len)
{
	int i, ret = -1;

	I2CDS = (DEV_ADDR<<1)|1; //master rx
	I2CSTAT = 0xb0;
	resume_iic_scl();
	if (wait_until_iic_irq() < 0)
		goto END;

	if (I2CSTAT & 1)
	{
		ret = -2;  //no ack
		goto END;
	}
	
	for (i = 0; i < len; i++)
	{
		resume_iic_scl();
		if (wait_until_iic_irq() < 0)
			goto END;
		
		data[i] = I2CDS;
	}		
	ret = i;

END:
	I2CSTAT = 0x90; // stop signal
	resume_iic_scl();
	i2c_delay(1000);
	
	return ret;
}
