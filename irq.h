#ifndef IRQ_H
#define IRQ_H

#include <stdint.h>

typedef struct {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

typedef void (*isr_t)(registers_t *);

isr_t interrupt_handlers[256];

void irq_handler(registers_t *r);
void register_interrupt_handler(int num, isr_t callback);

#endif
