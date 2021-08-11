#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../isr.h"
#include "../irq.h"
#include "../ports.h"
#include "../cstd.h"

#include <stdbool.h>

extern int commandlength;

static bool capslock = false;
static unsigned char shift = 0; // Two shifts

static char keyBuffer[256];

static void keyboard_callback(registers_t *regs);
void init_keyboard();

#endif
