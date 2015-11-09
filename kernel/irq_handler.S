@ file irq_handler.S
@ brief Assembler stub for calling up the C IRQ handler

@ author Alexandre Jove (ajovedel)
@ author Vishnu Gorantla (vishnupg)

	.file "irq_handler.S"
	.text
	.extern c_irq_handler

#include <asm.h>

FUNC(irq_handler)

	STMFD	sp!, {r0-r12, lr}		@store users GP registers and lr in IRQ stack
	
	LDR	r5, =uboot_r8			@restore uboot address
	LDR	r8, [r5]

	BL	c_irq_handler			@Call C_SWI_Handler and pass the SWI number

	LDMFD	sp!, {r0-r12, lr}		@restore users GP registers an lr_svc
	
	SUB	lr, lr, #4			@return back to calle program and restore cpsr
	MOVS	pc, lr




