#include "command.h"
#include "cstd.h"
#include "drivers/display.h"

void gameoflife() {
    // unsigned char *pixel = (unsigned char *)0xa0000;    
    // for (int i = 0; i < 1000; i++) {
    //     *(pixel + i) = 128;
    // }
}

void execute(char buffer[]) {
    if (strcmp(buffer, "game-of-life") == 0) {
        gameoflife();
    } else {
        print_string("Unknown command: ");
        print_string(buffer);
    }
    clear(buffer);
    print_string("\n>");
}
