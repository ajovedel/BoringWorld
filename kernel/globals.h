/*
 * global variables and constants
 */

#define SWI_VECTOR_ADDR (unsigned *) 0x08
#define IRQ_VECTOR_ADDR (unsigned *) 0x18
#define OS_CLK_SPEED (unsigned long) 3250000
#define TIME_RES_MS (unsigned long) 10
#define TIME_RES_CYCLES (unsigned long) (OS_CLK_SPEED * (0.001 * TIME_RES_MS))

void *swi_handler();
void *irq_handler();
unsigned *install_handler(unsigned *vector_addr, unsigned *saved_inst,
                               unsigned handler_addr);
void call_user(int argc, char *argv[]);
void irq_setup();
void timer_setup();
void interrupt_setup();

extern volatile unsigned long TIME_UNITS_ELAPSED;
