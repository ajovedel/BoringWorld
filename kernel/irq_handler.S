@Handle IRQs

	.file "irq_handler.S"
	.text
	.extern c_irq_handler

#include <asm.h>

FUNC(irq_handler)

	STMFD	sp!, {r0-r12, lr}		@store users GP registers and lr_svc in kernel stack

	LDR	r5, =uboot_r8			@restore uboot address
	LDR	r8, [r5]

	BL	c_irq_handler			@Call C_SWI_Handler and pass the SWI number

	ADD 	sp, sp, #4			@add 4 bytes because we do not restore r0
	LDMFD	sp!, {r1-r12, lr}		@restore users GP registers an lr_svc

	SUBS	pc, lr, #4			@restore cpsr from spsr_irq and pc from lr_irq




