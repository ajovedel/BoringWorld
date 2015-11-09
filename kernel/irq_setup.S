@ file irq_setup.S
@ brief Sets up the IRQ handler stack
@
@ author: Alexandre Jove (ajevodel)
@ author: Vishnu Gorantla (vishnupg) 


	.file "irq_setup.S"
	.text
	.extern c_irq_handler

#include <asm.h>

FUNC(irq_setup)

	STMFD	sp!, {r3-r4}

	MRS	r3, cpsr		@ change to IRQ mode
	MOV	r4, r3			@ copy of kernel mode
	BIC	r3, #0x1F
	ORR	r3, #0xD2
	MSR	cpsr, r3

	MOV	sp, #0xA4000000		@ setup IRQ stack

	MSR	cpsr, r4		@enable IRQs, switch back to kernel mode and return
	LDMFD	sp!, {r3-r4}
	MOV	pc, lr


