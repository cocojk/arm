#include "../include/vh_cpu_hal.h"

.extern VPOS_kernel_main
.extern vk_undef_handler
.extern vh_hwi_classifier
.extern vk_swi_classifier
.extern vk_pabort_handler
.extern vk_dabort_handler
.extern vk_fiq_handler
.extern vk_not_used_handler
.extern vk_irq_test

.extern vk_sched_save_tcb_ptr

.global vh_VPOS_STARTUP

.global vk_save_swi_mode_stack_ptr		
.global vk_save_swi_current_tcb_bottom
.global vk_save_irq_mode_stack_ptr	
.global vk_save_irq_current_tcb_bottom
.global vk_save_pabort_current_tcb_bottom

.global vh_restore_thread_ctx
.global vh_save_thread_ctx
.global vh_save_ctx_bottom

.equ vh_USERMODE,   0x10
.equ vh_FIQMODE,    0x11
.equ vh_IRQMODE,    0x12
.equ vh_SVCMODE,    0x13
.equ vh_ABORTMODE,  0x17
.equ vh_UNDEFMODE,  0x1b
.equ vh_MODEMASK,   0x1f
.equ vh_NOINT,      0xc0  
.equ vh_INT,		0x00	

.equ vh_userstack,  0x21200000
.equ vh_svcstack,   0X21400000
.equ vh_irqstack,   0x21600000
.equ vh_abortstack, 0x21800000
.equ vh_undefstack, 0x21a00000
.equ vh_fiqstack,   0x21c00000

.equ vh_vector_base, 		0x20008044// relocated vector table base address
.equ vh_VICBASE,		0xe4000000

.text
vh_VPOS_STARTUP:
	/* Camouflaged code for imitating linux
	   Linux has a header that includes 8 nop operation, branch code, magic number, binaray file start offset, and file size(end offset */
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	b 	vh_VPOS_reset
	magicn:	.long 0x016f2818	// Linux magic number
	startn:	.long 0x00000000	// start address(offset) is 0
	endn:	.long 0x0000d8fc	// end address(offset) is file size(byte)
	/* Camouflaged code end */
	
	nop
	nop
	nop
	nop
vh_vector_start:
		b       vh_VPOS_reset                           
        b       vk_undef
        b       vh_software_interrupt   
        b       vh_pabort
        b       vk_dabort
        b       vk_not_used_handler             
        b       vh_irq                  
        b       vk_fiq_handler
vh_VPOS_reset:
	// variable initialization
	mov	r0, #0x00
	str	r0, vk_save_swi_mode_stack_ptr
	str	r0, vk_save_swi_current_tcb_bottom
	str	r0, vk_save_irq_mode_stack_ptr
	str	r0, vk_save_irq_current_tcb_bottom

	// Mask interrupt and fast interrupt
	mrs	r0, cpsr		
	orr	r0, r0, #0xc0
	msr	cpsr, r0
	
	// Invalidate all instruction caches to point of unification. Also flushes branch target cache.
	mov	r0, #0x00
	mcr     p15, 0, r0, c7, c5, 0   

	// Control Register Setting
	mrc	p15, 0, r0, c1, c0, 0 	// Read control register 
	bic	r0, r0, #0x01		// MMU disabled
	bic	r0, r0, #0x04		// D-Cache disabled
	bic	r0, r0, #0x1000		// I-Cache disabled
	bic	r0, r0, #0x2000		// Normal exception vectors, base address 0x0000000
	orr	r0, r0, #0x02		// Alignment fault checking enabled
	orr	r0, r0, #0x800		// Branch prediction enabled 
	mcr 	p15, 0, r0, c1, c0, 0	// write control register
	
	// change vector table base address (0x20008044)
	ldr	r0, =vh_vector_base
	mcr	p15, 0, r0, c12, c0, 0

	// stack pointer setting
	mrs r0,cpsr
	
	bic r0,r0,#vh_MODEMASK|vh_NOINT
   	orr r1,r0,#vh_UNDEFMODE|vh_NOINT
   	msr cpsr_cxsf,r1                
   	ldr sp,=vh_undefstack
    
   	bic r0,r0,#vh_MODEMASK|vh_NOINT 
	orr r1,r0,#vh_ABORTMODE|vh_NOINT
    msr cpsr_cxsf,r1               
    ldr sp,=vh_abortstack
	
   	bic r0,r0,#vh_MODEMASK|vh_NOINT
   	orr r1,r0,#vh_IRQMODE|vh_NOINT
   	msr cpsr_cxsf,r1              
   	ldr sp,=vh_irqstack

	bic r0,r0,#vh_MODEMASK|vh_NOINT
   	orr r1,r0,#vh_FIQMODE|vh_NOINT
   	msr cpsr_cxsf,r1             
   	ldr sp,=vh_fiqstack

	bic r0,r0,#vh_MODEMASK|vh_NOINT
    orr r1,r0,#vh_SVCMODE|vh_NOINT
    msr cpsr_cxsf,r1            
  	ldr sp,=vh_svcstack	

	// user mode sp 
	bic r0,r0,#vh_MODEMASK|vh_NOINT
	orr r1,r0,#vh_USERMODE|vh_INT
	msr cpsr_cxsf,r1 
	ldr sp,=vh_userstack
	
	b VPOS_kernel_main

.global	vt_read_sp
vt_read_sp:	
	mov	r0,sp
	mov	pc, lr

.global vt_read
vt_read:
	mrs 	r0, cpsr
	mov	pc, lr

vk_undef:
	str	lr, vk_error_addr
        b       vk_undef_handler       

vk_dabort:
	str	lr, vk_error_addr
        b       vk_dabort_handler

.global vh_svc_int_enable
vh_svc_int_enable:
	mrs	r0, cpsr_all
	bic	r0, r0, #0x80
	msr	cpsr_all, r0
	bx	lr




vh_software_interrupt:
vh_entering_swi:
	str	sp, vk_save_swi_mode_stack_ptr
	stmfd	sp, {r14}^
	sub	sp, sp, #4
	stmfd	sp, {r13}^
	sub	sp, sp, #4
	stmfd	sp!, {r0-r12}
	
	mrs	r0, spsr_all
	stmfd	sp!, {r0, lr}
	mrs	r0, cpsr_all
	orr	r0, r0, #0x80
	msr	cpsr_all, r0

	str	sp, vk_save_swi_current_tcb_bottom
	ldr	r0, [sp, #8]
	bl	vk_swi_classifier

vh_leaving_swi:
	ldmfd	sp!, {r0, lr}
	msr	spsr_all, r0
	ldmfd	sp!, {r0-r12}
	ldmfd	sp, {r13}^
	add	sp, sp, #4
	ldmfd	sp, {r14}^
	add	sp, sp, #4
	movs	pc, lr

vh_irq:
	// lr - 4 를 해줘야 올바른 복귀 주소가 된다. pipeline 때문에 ??
	sub		lr,lr,#4
	
	// context 저장전 sp를 (초기 irq_sp)를 vk_save_irq_mode_stack_ptr가 가리키는 메모리에 저장 
	str 	sp,vk_save_irq_mode_stack_ptr
	
	// ^ 표시는 user(system) mode의 레지스터를 의미하며, Rn 레지스터의 write back 미지원
	// 따라서 sp 감소하는 instruction 필요 
	stmfd	sp,{r14}^
	sub		sp,sp,#4
	// 위와 동일 (register list 사용가능하므로 해당 4줄 코드는 2줄로 해결 가능)
	stmfd	sp,{r13}^
	sub		sp,sp,#4

	// r12 ~ r0 순으로 irq_sp에다가 context save 
	stmfd	sp!,{r0-r12}

	mrs		r0,spsr_all
	
	// lr , r0 를 irq_sp에 context save 
	stmfd	sp!,{r0,lr}

	// context 저장 후 sp를 vk_save_irq_current_tcb_bottom가 가리키는 메몰리에 저장 
	str		sp,vk_save_irq_current_tcb_bottom

	// 0xe4000000 VIC0IRQSTATUS의 값을 읽은 후 하나라도 interrupt가 존재하면, vh_irq_VIC0 실행 
	ldr		r0,=0xe4000000
	ldr		r1,[r0]
	cmp		r1,#0x0	
	bne		vh_irq_VIC0
	
	// 0xe4100000 VIC1IRQSTATUS의 값을 읽은 후 하나라도 interrupt가 존재하면, vh_irq_VIC1 실행 
	ldr		r0,=0xe4100000
	ldr		r1,[r0]
	cmp		r1,#0x0	
	bne		vh_irq_VIC1

vh_irq_VIC0:
	ldr		r0,=0xe4000f00;
	ldr 	r1,[r0]
	mov		r14,pc
	mov 	pc,r1 

	// interrupt service routine 이후 
	msr		cpsr_c,#vh_IRQMODE	|	0x80 

	// 0xe4100F00 clear (아무 값이나 write 해주면 clear 된다.)
	ldr		r14,=0xe4000F00
	str		r14,[r14] 

	// context load 
	ldmfd	sp!,{r0,lr}
	msr		spsr_cxsf,r0
	ldmfd	sp!,{r0-r12}
	ldmfd	sp,{r13}^
	add		sp,sp,#4
	ldmfd	sp,{r14}^
	add		sp,sp,#4
	movs	pc,lr	



vh_irq_VIC1:
	// VIC1ADDRESS 0xe4100f00에 저장된 interrupt routine으로 이동, 
	// r14 (lr)에 pc값 저장 (아마 해당 위치에서 다음다음 instruction 값을 가짐) 
	// pc에 interrupt routine 주소값 저장 
	ldr		r0,=0xe4100F00
	ldr		r1,[r0]
	mov		r14,pc
	mov		pc,r1 

	// interrupt service routine 이후 
	msr		cpsr_c,#vh_IRQMODE	|	0x80 

	// 0xe4100F00 clear (아무 값이나 write 해주면 clear 된다.)
	ldr		r14,=0xe4100F00
	str		r14,[r14] 

	// context load 
	ldmfd	sp!,{r0,lr}
	msr		spsr_cxsf,r0
	ldmfd	sp!,{r0-r12}
	ldmfd	sp,{r13}^
	add		sp,sp,#4
	ldmfd	sp,{r14}^
	add		sp,sp,#4
	movs	pc,lr	

vh_pabort:	
    ldr 	sp,=vh_abortstack

	sub	lr, lr, #4
	str	sp, vk_save_pabort_stack_ptr
	stmfd	sp!, {r0-r14}^
	mrs	r0, spsr_all
	stmfd	sp!, {r0, lr}
	str	sp, vk_save_pabort_current_tcb_bottom
	
	bl	vk_pabort_handler

vh_leaving_pabort:
	ldmfd	sp!, {r0, lr}
	msr	spsr_all, r0
	ldmfd 	sp!, {r0-r12}^
	ldmfd	sp, {r13}^
	add	sp, #4
	ldmfd	sp!, {lr}^
	
	movs	pc, lr

vh_restore_thread_ctx:
	mov	sp, r0   				// sp <- tcb_bottom 

	/*	restore thread psr(r0) and thread address for restart(lr) */
	ldmfd	sp!, {r0, lr}
	msr	spsr_all, r0				// set spsr (current thread psr)

	/* 	restore current thread context.
		we cannot multiple load r13 in Cortex-A9.*/
	ldmfd	sp!, {r0-r12}	
	ldmfd 	sp, {r13}^
	add	sp, #4		
	ldmfd	sp!, {lr}^
	
	ldr	sp, vk_save_swi_mode_stack_ptr
	movs	pc, lr


.global vr_save_thread_ctx
vr_save_thread_ctx:
	ldr	r2, vk_save_pabort_current_tcb_bottom
	b	vh_save_ctx_bottom

.global vh_change_ctx
vh_change_ctx:
	mov	r2, r0
	ldr	r0, vk_save_swi_current_tcb_bottom
	b	vh_save_ctx_bottom

// this function copy data from r2 to r0
vh_save_thread_ctx:
	/*	Check mode */
	mrs	r1, cpsr_all
	bic	r1, r1, #0xfffffff0
	mov	r2, #0x2		// IRQ mode /// modifying
	cmps	r1, r2

	ldreq	r2, vk_save_irq_current_tcb_bottom
	//ldrne	r2, vk_save_swi_current_tcb_bottom
	ldrne	r1, =vk_sched_save_tcb_ptr
	ldrne	r2, [r1]
	
	b	vh_save_ctx_bottom

vh_save_ctx_bottom:
	.rept	17 					// copy context from SVC stack to USER stack
	ldr	r1, [r2], #4
	str	r1, [r0], #4
	.endr
	mov	pc, lr					// return to caller


vk_save_swi_mode_stack_ptr:	
				.long 0
vk_save_swi_current_tcb_bottom:
				.long 0
vk_save_irq_mode_stack_ptr:	
				.long 0
vk_save_irq_current_tcb_bottom:
				.long 0
vk_save_pabort_stack_ptr:	
				.long 0
vk_save_pabort_current_tcb_bottom:
				.long 0

.global vk_error_addr
vk_error_addr:
				.long 0
