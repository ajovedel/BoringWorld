#include <exports.h>
#include "syscalls.h"
#include <arm/timer.h>
#include <arm/reg.h>
#include <arm/psr.h>
#include "globals.h"

void c_irq_handler(){
//	printf("I AM IN C_IRQ_HANDLER!!\n");

	// check if timer interrupt has ocurred
	if(reg_read(OSTMR_OSSR_ADDR) && OSTMR_OSSR_M0){
	
//		printf("Timer interrupt has occured\n");

		// the OSMR0 registers has to be reloaded with OSCR + 32500 (OSCR + 10ms)
		reg_write(OSTMR_OSMR_ADDR(0), (reg_read(OSTMR_OSCR_ADDR) + 3250000));

		// the OSSR[0] register has to be reset (acknowledged)
		reg_set(OSTMR_OSSR_ADDR, OSTMR_OSSR_M0);

		TIME_ELAPSED += 10;

		printf("TIME_ELAPSED: %lu", TIME_ELAPSED);
	}
	
	// if another type of interrupt has ocurred, we ignore it
	else
		printf("idk why im here\n");

}
