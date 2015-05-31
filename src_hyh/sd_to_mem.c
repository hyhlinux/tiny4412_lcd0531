#include <common.h>
#include <sd_to_mem.h>
#include <lcd.h>


/********************************************************
copy_sd_mmc_to_mem(49, 1024*3, 0x43e00000);
	
arg		: 
	49	: 第几个分区	
	size	: size
	dst	: 目的地址.
---------------------------------------
1扇区	= 512B
	1024 个扇区	= 1024 * 512 字节
			= 512 K
			= 0.5 M
---------------------------------------
	1.5M		= 1024 * 3
			= 0.5M * 3	
----------------------------------------
	30M		= 1024 * 3 * 20 
************************************************************/
void sd_to_mem(void)
{
	int (*copy_sd_mmc_to_mem)(int , int , int ) = (void *)(*(unsigned int *)(0x02020030));
//	ui
        copy_sd_mmc_to_mem(1000, 1024*3, 0x62000000);
//	alpha1 / 2
        copy_sd_mmc_to_mem(4072, 1024*3, 0x63000000);
        copy_sd_mmc_to_mem(7144, 1024*3, 0x64000000);
//	rotator
//	copy_sd_mmc_to_mem(10216, 1024*3, 0x65000000);
//	pic20
        copy_sd_mmc_to_mem(13288, 1024*3*20, 0x70000000);
//	pic20_r90
       copy_sd_mmc_to_mem(74728,  1024*3*20, 0x72000000);
//	ppt_pic15
        copy_sd_mmc_to_mem(136168, 1024*3*15, 0x74000000);
	printf("\nsd_to_mem copy is ok\n");

//	write_string("sd_to_mem copy is ok\n", 200,200);
}

