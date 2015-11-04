#include <exports.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include "globals.h"

uint32_t global_data;
unsigned *uboot_r8;		/* uboot jump table addr */
unsigned *kernel_ret_addr;	/* kernel return addr from usr */
unsigned long TIME_ELAPSED = 0; /* keep track of time elapsed of the system */


int kmain(int argc, char** argv, uint32_t table)
{
	unsigned *swi_install_addr;
	unsigned *irq_install_addr;
	unsigned swi_saved_inst[2];
	unsigned irq_saved_inst[2];

	app_startup(); /* bss is valid after this point */
	global_data = table;

	// install SWI and IRQ handler
	swi_install_addr = install_handler(SWI_VECTOR_ADDR, swi_saved_inst);
	irq_install_addr = install_handler(IRQ_VECTOR_ADDR, irq_saved_inst);

	printf("did i make it here?\n");
	// setup IRQ space
	irq_setup();

	printf("what about here?\n");
	// setup interrupts
	interrupt_setup();

	printf("and heeeer???\n");
	// setup timer
	timer_setup();

	printf("user app\n");
	// setup user space and call the user app
	call_user(argc, argv);

	printf("EXITED user app\n");	
	while(1);

	// restore the SWI handler
	*swi_install_addr = swi_saved_inst[0];
	*(swi_install_addr + 1) = swi_saved_inst[1];

	// restore the IRQ handler
	*irq_install_addr = irq_saved_inst[0];
	*(irq_install_addr + 1) = irq_saved_inst[1];

	return 0;
}
