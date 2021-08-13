#include "command.h"
#include "cstd.h"
#include "drivers/display.h"
#include "type.h"
#include "ports.h"

void gameoflife() {
    unsigned char *pixel = (unsigned char *)VIDEO_ADDRESS; 
    for (int i = 0; i < 1000; i++) {
        *(pixel + i) = 0xff;
    }
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
