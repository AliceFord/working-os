#include "irq.h"
#include "ports.h"
#include "drivers/display.h"

void register_interrupt_handler(int num, isr_t callback) {
    interrupt_handlers[num] = callback;
}

void irq_handler(registers_t *r) {
    if (interrupt_handlers[r->int_no] != 0) {
        isr_t handler = interrupt_handlers[r->int_no];
        handler(r);
    }

    out(0x20, 0x20);
    if (r->int_no < 40) {
        out(0xa0, 0x20);
    }
}
