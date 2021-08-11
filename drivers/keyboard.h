#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../isr.h"
#include "../irq.h"
#include "../ports.h"

#include <stdbool.h>

extern int commandlength;

static bool capslock = false;
static unsigned char shift = 0; // Two shifts

void print_letter(uint8_t scancode);
static void keyboard_callback(registers_t *regs);
void init_keyboard();

#endif
