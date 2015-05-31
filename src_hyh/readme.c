
minicom sd 启动uboot
--------------------------step1
hyh@hyh-Lenovo-V470c:/tools/uboot/uboot_tiny4412/arch/arm/cpu/armv7$ grep "Checking Boot Mode " -nr ./
hyh@hyh-Lenovo-V470c:/tools/uboot/uboot_tiny4412/arch/arm/cpu/armv7$ cd ..
hyh@hyh-Lenovo-V470c:/tools/uboot/uboot_tiny4412/arch/arm/cpu$ cd ..
hyh@hyh-Lenovo-V470c:/tools/uboot/uboot_tiny4412/arch/arm$ cd ..
hyh@hyh-Lenovo-V470c:/tools/uboot/uboot_tiny4412/arch$ cd ..
hyh@hyh-Lenovo-V470c:/tools/uboot/uboot_tiny4412$ cd ..
hyh@hyh-Lenovo-V470c:/tools/uboot$ grep "Checking Boot Mode " -nr ./
./uboot_tiny4412/board/samsung/smdk5210/smdk5210.c:100:	printf("\nChecking Boot Mode ...");
./uboot_tiny4412/board/samsung/tiny4412/tiny4412.c:163:	printf("\n\nChecking Boot Mode ...");
匹配到二进制文件 ./uboot_tiny4412/board/samsung/tiny4412/libtiny4412.o
匹配到二进制文件 ./uboot_tiny4412/board/samsung/tiny4412/tiny4412.o
./uboot_tiny4412/board/samsung/smdk4212/smdk4212.c:149:	printf("\n\nChecking Boot Mode ...");
匹配到二进制文件 ./uboot_tiny4412/sd_fuse/tiny4412/uboot_sd_bs/u-boot.bin
匹配到二进制文件 ./uboot_tiny4412/u-boot
匹配到二进制文件 ./uboot_tiny4412/u-boot.bin
hyh@hyh-Lenovo-V470c:/tools/uboot$ vim ./uboot_tiny4412/board/samsung/tiny4412/tiny4412.c +163
	用内练汇编修改。ldr pc,=0x50008000
	74 int board_init(void) ----> 在某处被调用

------------------------step2
hyh@hyh-Lenovo-V470c:/tools/uboot/uboot_tiny4412$ cd ..
hyh@hyh-Lenovo-V470c:/tools/uboot$ grep "Hit any key to stop autoboot" -nr ./

匹配到二进制文件 ./uboot_tiny4412/common/main.o
./uboot_tiny4412/common/main.c:221:	printf("Hit any key to stop autoboot: %2d ", bootdelay);
匹配到二进制文件 ./uboot_tiny4412/sd_fuse/tiny4412/uboot_sd_bs/u-boot.bin
匹配到二进制文件 ./uboot_tiny4412/u-boot
匹配到二进制文件 ./uboot_tiny4412/u-boot.bin
hyh@hyh-Lenovo-V470c:/tools/uboot$ vim uboot_tiny4412/common/main.c +221
hyh@hyh-Lenovo-V470c:/tools/uboot$ 

 220 #else
 221         printf("Hit any key to stop autoboot: %2d ", bootdelay);
 222         //pc
 223 #endif
	修改此处测试.
---------------------------------------

