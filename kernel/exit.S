@exits back to the kernel

	.file "exit.S"
	.text

#include <asm.h>

FUNC(exit)
	ADD 	sp, sp, #8			@we have to add 8 to make up for the 4 bytes we did not add in swi_handler and 4 bytes that are used by C_SWI_handler
	
	LDMFD	sp!, {r1-r12, lr}

	LDR		r5, =kernel_ret_addr	@retrieve and go to kernel return address
	LDR		pc, [r5]

