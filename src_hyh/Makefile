.PHONY:	clean
#######

TARGET		:= arm
BIN		:= $(TARGET).bin

ST_OBJS		:= start.o

OBJS		:= main.o 
OBJS		+= shell.o 
OBJS		+= ui.o 
OBJS		+= schdule.o 
OBJS		+= sd_to_mem.o 

OBJS		+= common.o
OBJS		+= lcd.o
OBJS		+= teris.o #lcd-app
OBJS		+= alpha.o #lcd-app
OBJS		+= pic20.o #lcd-app
OBJS		+= rotator.o #lcd-app
OBJS		+= myppt.o #lcd-app

#lcd base
OBJS		+= backlight.o
OBJS		+= pwm.o

OBJS		+= rtc_irq.o

#irq
OBJS		+= irq.o
OBJS		+= isr.o
OBJS		+= mmu.o

#i2c
OBJS		+= tp.o
OBJS		+= iic.o

OBJS		+= uart.o
OBJS		+= cmd.o
OBJS		+= shell_info.o

#OBJS		+= led.o
OBJS		+= buzzer.o
OBJS		+= key.o
#OS2....LCD...DISPLAY
#OBJS		+= main2.o

CROSS_COMPILE	:= arm-linux-

CC		:= $(CROSS_COMPILE)gcc
AS		:= $(CROSS_COMPILE)as
OBJCPOY		:= $(CROSS_COMPILE)objcopy
LD		:= $(CROSS_COMPILE)ld
NM		:= $(CROSS_COMPILE)nm
OBJDUMP		:= $(CROSS_COMPILE)objdump

CFLAGS		:= -Wall -fno-builtin -Iinclude

all:$(TARGET)
	$(OBJCPOY) -O binary $< $(BIN)
	$(NM) $(TARGET) > $(TARGET).map
	$(OBJDUMP) -dS $(TARGET) > $(TARGET).asm
#	$(CC)  -E main.c -o main.i -Iinclude
	cp $(BIN)  ../
	
$(TARGET):  $(ST_OBJS) $(OBJS)
	$(LD) $^  -T ld.lds  -o $@
%.o: %.c
	$(CC) -c $<  $(CFLAGS) -o $@ 
%.o: %.s
	$(AS) $<  -o $@ 
%.o: %.S
	$(AS) $<  -o $@ 


clean:
	rm -rf *.o $(TARGET)* *.i 
	rm ../$(BIN)


