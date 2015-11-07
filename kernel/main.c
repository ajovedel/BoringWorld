/** @file main.c
 *
 *  @brief This file contains the core functionality of our kernel
 *
 *  @author Alexandre Jove (ajovedel)
 *  @author Vishnu Gorantla (vishnupg)
 *  @bug No known bugs
 */

#include <exports.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>
#include "globals.h"

uint32_t global_data;

/* uboot jump table addr */
unsigned *uboot_r8;

/* kernel return addr from usr */
unsigned *kernel_ret_addr;

/* keep track of time elapsed of the system */
volatile unsigned long TIME_UNITS_ELAPSED = 0; 


/** @brief C entry point for the kernel
 *
 *  @param argc Number of arguments
 *  @param argv Command line args pointers
 *  @param table global Table 
 *  @return kernel return status
 */
int kmain(int argc, char** argv, uint32_t table)
{
	unsigned *swi_install_addr;
	unsigned *irq_install_addr;
	unsigned swi_saved_inst[2];
	unsigned irq_saved_inst[2];

	app_startup(); /* bss is valid after this point */
	global_data = table;

	// install SWI and IRQ handler
	swi_install_addr = install_handler(SWI_VECTOR_ADDR, swi_saved_inst,
                                      (unsigned) swi_handler);
	irq_install_addr = install_handler(IRQ_VECTOR_ADDR, irq_saved_inst,
                                      (unsigned) irq_handler);

	printf("did i make it here?\n");
//	printf("TIME_RES_CYCLES: " TIME_RES_CYCLES "\n");
	// setup IRQ space
	irq_setup();

	// setup interrupts
	interrupt_setup();

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
