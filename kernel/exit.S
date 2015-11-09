@ file exit.S

@ brief exits back to the kernel
@ author Alejandro Jove (ajovedel)
@ author Vishnu Gorantla (vishnupg)


	.file "exit.S"
	.text

#include <asm.h>

FUNC(exit)
	@ Add 8 to make up for the 4 bytes we did not add in swi_handler 
  @ and 4 bytes that are used by C_SWI_handler
	ADD 	sp, sp, #8	
	LDMFD	sp!, {r1-r12, lr}

	LDR		r5, =kernel_ret_addr	@retrieve and go to kernel return address
	LDR		pc, [r5]

