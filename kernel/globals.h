/*
 * global variables and constants
 */

#define SWI_VECTOR_ADDR (unsigned *) 0x08
#define IRQ_VECTOR_ADDR (unsigned *) 0x18
#define TIMER_RES 10

void *swi_handler();
void *irq_handler();
unsigned *install_handler(unsigned *vector_addr, unsigned *saved_inst);
void call_user(int argc, char *argv[]);
void irq_setup();
void timer_setup();
void interrupt_setup();

extern unsigned long TIME_ELAPSED;
