/* install the handler using the specified vector address
 * The replaced instructions are returned so the caller can
 * restore the instructions
 */

#include <exports.h>
#include "globals.h"

unsigned *install_handler(unsigned *vector_addr, unsigned *saved_inst){

	unsigned offset_positive = 0;
	unsigned *handler_addr;

	// verify if vector address contains the instructions
	// "ldr  pc, [pc, #imm12]"
	if((*vector_addr & 0xFF7FF000) != 0xE51ff000)
		printf("0x0badc0de\n");

	// identify if the vector offset to the jump table is positive or negative
	// U = 0 (negative offset), U = 1 (positive offset)	
	if(*vector_addr & 0x00800000)
		offset_positive = 1;

	// calculate the address of the handler
	if(offset_positive == 1)
		handler_addr = (unsigned *) *((unsigned *)((unsigned)vector_addr + \
			((*vector_addr & 0x00000FFF) + 0x08)));
	else
		handler_addr = (unsigned *) *((unsigned *)((unsigned)vector_addr + \
			((*vector_addr & 0x00000FFF) - 0x08)));	 

	// Save the first two instructions that we are going to be modyfing
	// in the SWI handler	
	saved_inst[0] = *handler_addr;
	saved_inst[1] = *(handler_addr + 1);

	// install "ldr pc, [pc, #-4]
	*handler_addr = 0xE51FF004;

	// install address of swi or irq handler
	if(vector_addr == SWI_VECTOR_ADDR)
		*(handler_addr + 1) = (unsigned) swi_handler;

	else if(vector_addr == IRQ_VECTOR_ADDR)
		*(handler_addr + 1) = (unsigned) irq_handler;

	return handler_addr;
}

