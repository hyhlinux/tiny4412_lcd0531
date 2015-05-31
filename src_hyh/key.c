#include <key.h>


void key_init(void)
{
	GPX3CON  &=  ~(0xffff << 2); //input
}
int key_read(void)
{
	return ((GPX3DAT>>2)&0XF);
}
int key_id(void) 
{
	int value = key_read();
	int ret = -1;
	switch(value) {
	case 0xe:
		ret = 4;
		while(key_read() == 0xe) { }
		printf("key id ..%d..value is %#x\n",ret, value);
		break;
	case 0xd:
		ret = 3;
		while(key_read() == 0xd) { }
		printf("key id ..%d..value is %#x\n",ret, value);
		break;
	case 0xb:
		ret = 2;
		while(key_read() == 0xb) { }
		printf("key id ..%d..value is %#x\n",ret, value);
		break;
	case 0x7:
		ret = 1;
		while(key_read() == 0x7) { }
		printf("key id ..%d..value is %#x\n",ret, value);
		break;
	default:
		printf("no key donw value is %#x\n",value);
		break;
	}

	return ret;
}

