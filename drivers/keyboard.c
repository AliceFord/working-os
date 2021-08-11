#include "keyboard.h"
#include "display.h"
#include "../isr.h"
#include "../irq.h"
#include "../ports.h"

#include <stdint.h>

int commandLength = 0;

const static char *keyNames[] = {
    "Error", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "BACKSPACE", "TAB",
    "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "ENTER", "LCTRL", "a", "s",
    "d", "f", "g", "h", "j", "k", "l", ";", "'", "`", "LSHIFT", "#", "z", "x", "c", "v",
    "b", "n", "m", ",", ".", "/", "RSHIFT", "PRTSCN?", "LALT", " ", "CAPSLOCK", "F1", "F2", "F3", "F4",
    "F5", "F6", "F7", "F8", "F9", "F10", "NUMLOCK", "SCROLLLOCK", "Keypad-7", "Keypad-8", "Keypad-9", "Keypad--", "Keypad-4", "Keypad-5", "Keypad-6", "Keypad-+", "Keypad-1",
    "Keypad-2", "Keypad-3", "Keypad-0", "Keypad-.", "Alt-SysRQ", "IDK", "IDK", "F11", "F12"
};

const static char *shiftKeyNames[] = {
    "Error", "ESC", "!", "\"", "£", "$", "%", "^", "&", "*", "(", ")", "_", "+", "BACKSPACE", "TAB",
    "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", "ENTER", "LCTRL", "A", "S",
    "D", "F", "G", "H", "J", "K", "L", ":", "@", "~", "LSHIFT", "|", "Z", "X", "C", "V",
    "B", "N", "M", "<", ">", "?", "RSHIFT", "KEYPAD-*", "LALT", " ", "CAPSLOCK", "F1", "F2", "F3", "F4",
    "F5", "F6", "F7", "F8", "F9", "F10", "NUMLOCK", "SCROLLLOCK", "HOME", "UP", "PGUP", "Keypad--", "LEFT", "Keypad-5", "RIGHT", "Keypad-+", "END",
    "DOWN", "PGDOWN", "INSERT", "DELETE", "Alt-SysRQ", "IDK", "IDK", "F11", "F12"
};

void print_letter(uint8_t scancode) {
    if (scancode < 0x5a) { // Keydown
        switch (scancode) {
        case 0x0e: // Backspace
            backspace();
            break;
        
        case 0x1c: // Enter
            break;
        
        case 0x2a:
        case 0x36: // Shift
            shift++;
            break;
        
        default:
            if (shift > 0) {
                print_string((char *)shiftKeyNames[scancode]);
            } else {
                print_string((char *)keyNames[scancode]);
            }
            commandLength++;
            break;
        }
    } else if (scancode >= 0x80 && scancode < 0xd5) { // Keyup
        switch (scancode) {
        case 0xaa:
        case 0xb6:
            shift--;
            break;
        default:
            break;
        }
    }
}

static void keyboard_callback(registers_t *regs) {
    uint8_t scancode = in(0x60);
    print_letter(scancode);
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}
