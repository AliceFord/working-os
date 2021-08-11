#include "isr.h"
#include "drivers/display.h"
#include "idt.h"
#include "ports.h"
#include "cstd.h"

void isr_handler(registers_t *r) {
    char buffers[16][9];
    uint32toa(r->ds, buffers[0]);
    uint32toa(r->edi, buffers[1]);
    uint32toa(r->esi, buffers[2]);
    uint32toa(r->ebp, buffers[3]);
    uint32toa(r->esp, buffers[4]);
    uint32toa(r->ebx, buffers[5]);
    uint32toa(r->edx, buffers[6]);
    uint32toa(r->ecx, buffers[7]);
    uint32toa(r->eax, buffers[8]);
    uint32toa(r->int_no, buffers[9]);
    uint32toa(r->err_code, buffers[10]);
    uint32toa(r->eip, buffers[11]);
    uint32toa(r->cs, buffers[12]);
    uint32toa(r->eflags, buffers[13]);
    uint32toa(r->useresp, buffers[14]);
    uint32toa(r->ss, buffers[15]);
    print_string("\n\n----ERROR!----\nMessage: ");
    print_string(exception_messages[r->int_no]);
    print_string("\nDS: ");
    print_string(buffers[0]);
    print_string("\nEDI: ");
    print_string(buffers[1]);
    print_string(" ESI: ");
    print_string(buffers[2]);
    print_string(" EBP: ");
    print_string(buffers[3]);
    print_string(" ESP: ");
    print_string(buffers[4]);
    print_string("\nEAX: ");
    print_string(buffers[8]);
    print_string(" EBX: ");
    print_string(buffers[5]);
    print_string(" ECX: ");
    print_string(buffers[7]);
    print_string(" EDX: ");
    print_string(buffers[6]);
    print_string("\nINT_NO: ");
    print_string(buffers[9]);
    print_string("\nError Code: ");
    print_string(buffers[10]);
    print_string("\nEIP: ");
    print_string(buffers[11]);
    print_string(" CS: ");
    print_string(buffers[12]);
    print_string(" EFLAGS: ");
    print_string(buffers[13]);
    print_string(" USERESP: ");
    print_string(buffers[14]);
    print_string(" SS: ");
    print_string(buffers[15]);
    print_string("\n");
    __asm__("hlt");
}

void isr_install() {
    set_idt_gate(0, (uint32_t)isr0);
    set_idt_gate(1, (uint32_t)isr1);
    set_idt_gate(2, (uint32_t)isr2);
    set_idt_gate(3, (uint32_t)isr3);
    set_idt_gate(4, (uint32_t)isr4);
    set_idt_gate(5, (uint32_t)isr5);
    set_idt_gate(6, (uint32_t)isr6);
    set_idt_gate(7, (uint32_t)isr7);
    set_idt_gate(8, (uint32_t)isr8);
    set_idt_gate(9, (uint32_t)isr9);
    set_idt_gate(10, (uint32_t)isr10);
    set_idt_gate(11, (uint32_t)isr11);
    set_idt_gate(12, (uint32_t)isr12);
    set_idt_gate(13, (uint32_t)isr13);
    set_idt_gate(14, (uint32_t)isr14);
    set_idt_gate(15, (uint32_t)isr15);
    set_idt_gate(16, (uint32_t)isr16);
    set_idt_gate(17, (uint32_t)isr17);
    set_idt_gate(18, (uint32_t)isr18);
    set_idt_gate(19, (uint32_t)isr19);
    set_idt_gate(20, (uint32_t)isr20);
    set_idt_gate(21, (uint32_t)isr21);
    set_idt_gate(22, (uint32_t)isr22);
    set_idt_gate(23, (uint32_t)isr23);
    set_idt_gate(24, (uint32_t)isr24);
    set_idt_gate(25, (uint32_t)isr25);
    set_idt_gate(26, (uint32_t)isr26);
    set_idt_gate(27, (uint32_t)isr27);
    set_idt_gate(28, (uint32_t)isr28);
    set_idt_gate(29, (uint32_t)isr29);
    set_idt_gate(30, (uint32_t)isr30);
    set_idt_gate(31, (uint32_t)isr31);

    // ICW1
    out(0x20, 0x11);
    out(0xa0, 0x11);

    // ICW2
    out(0x21, 0x20);
    out(0xa1, 0x28);

    // ICW3
    out(0x21, 0x04);
    out(0xa1, 0x02);

    // ICW4
    out(0x21, 0x01);
    out(0xa1, 0x01);

    // OCW1
    out(0x21, 0x0);
    out(0xa1, 0x0);

    set_idt_gate(32, (uint32_t)irq0);
    set_idt_gate(33, (uint32_t)irq1);
    set_idt_gate(34, (uint32_t)irq2);
    set_idt_gate(35, (uint32_t)irq3);
    set_idt_gate(36, (uint32_t)irq4);
    set_idt_gate(37, (uint32_t)irq5);
    set_idt_gate(38, (uint32_t)irq6);
    set_idt_gate(39, (uint32_t)irq7);
    set_idt_gate(40, (uint32_t)irq8);
    set_idt_gate(41, (uint32_t)irq9);
    set_idt_gate(42, (uint32_t)irq10);
    set_idt_gate(43, (uint32_t)irq11);
    set_idt_gate(44, (uint32_t)irq12);
    set_idt_gate(45, (uint32_t)irq13);
    set_idt_gate(46, (uint32_t)irq14);
    set_idt_gate(47, (uint32_t)irq15);

    load_idt();
}
