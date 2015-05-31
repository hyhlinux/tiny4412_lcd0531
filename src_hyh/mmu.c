#include <mmu.h>
#include <common.h>

static void section_map(u32 *ttb, u32 va_start, u32 va_end, u32 pa)
{
	while(va_start < va_end){
		create_descriptor(ttb, va_start, pa);
		va_start += 0x100000;
		pa	 += 0x100000;
	}
}

static void init_ttb(u32 *ttb)
{
	section_map(ttb, 0x0, 0x08000000, 0x0);
	section_map(ttb, 0x08000000, 0x14000000, 0x08000000);
	section_map(ttb, 0x40000000, 0x80000000, 0x40000000);
}

static void mmu_enable(u32 *ttb)
{
	__asm__	__volatile__(
		
		"mvn r0, #0\n\t"
		"mcr p15, 0, r0, c3, c0, 0\n\t" //内存的访问的权限最大

		"mcr p15, 0, %[ttb], c2, c0, 0\n\t"//将转换表的基地址写进C2

		"mrc p15, 0, r0, c1, c0, 0\n\t"
		"orr r0,#0x1\n\t"		//enable mmu
		"orr r0,r0,#(0x1 << 13)\n\t"	//set high exception vector address
		"mcr p15, 0, r0, c1, c0, 0\n\t"

		:
		:[ttb]"r"(ttb)
		:"r0"			
	);
}

void create_vector_add(u32 *ttb)
{
	init_ttb(ttb);

	mmu_enable(ttb);	

	create_descriptor(ttb, VECTOR_BASE_VA, VECTOR_BASE_PA);


	mymemcpy((char *)VECTOR_BASE_VA, (char *)vec_start,vec_end-vec_start+1);
}
