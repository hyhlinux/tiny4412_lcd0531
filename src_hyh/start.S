
.text
.align 2
.globl _start

_start:
	ldr pc,reset_  @0x0
	ldr pc,unde_   @0x4
	ldr pc,svc_    @0x8	
	nop	
	nop	
	nop	
	ldr pc,irq_	@0x18
reset_:
	.word reset
unde_:
	.word unde
svc_:
	.word svc
irq_:
	.word irq
reset:
	mov ip, sp
	push {fp, ip, lr, pc}
	sub fp, ip, #4

	mrs r0,cpsr
	bic r0,r0,#0x1f
	orr r0,r0,#0x12
	msr cpsr, r0

	mov sp,#0x60000000

	mrs r0,cpsr
	bic r0,r0,#0x1f
	orr r0,r0,#0x13
	msr cpsr, r0
	
	bl clr_bss
	bl main
@	bl app_start 

	sub sp, fp, #12
	ldm sp, {fp, sp, pc}

irq:
	stmfd sp!,{r0-r12,lr}
	mov lr,pc
	ldr pc,=do_irq
	ldmfd sp!,{r0-r12,lr}
	subs pc,lr,#4
unde:
svc:
end:

.global vec_start
.global vec_end

vec_start:
	.word _start
vec_end:
	.word end

.global start_bss_add
.global end_bss_add

start_bss_add:
	.word _start_bss_add
end_bss_add:
	.word _end_bss_add

clr_bss:
	ldr r0,start_bss_add
	ldr r1,end_bss_add

	mov r2,#0
	for_clr:
		strb r2,[r0],#1
		cmp r0,r1
		blt for_clr

	mov pc,lr
