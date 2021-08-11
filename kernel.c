#include "drivers/display.h"
#include "drivers/keyboard.h"
#include "isr.h"
#include <stdint.h>
//#include "idt.h"

void kernel_main() {
    clear_screen();
    print_string("Installing ISRs...\n");
    isr_install();
    print_string("ISRs installed.\n");

    print_string("Activating Interrupts...\n");
    __asm__ __volatile__("sti");
    print_string("Interrupts activated.\n");
    
    print_string("Initialising keyboard...\n");
    init_keyboard();
    print_string("Keyboard initialised.\n");
    print_string("\nWelcome to my (TechieHelper's) operating system!\nUse the help command for help.\n>");
}
