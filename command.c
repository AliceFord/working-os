#include "command.h"
#include "cstd.h"
#include "drivers/display.h"

void gameoflife() {
    Entry16();
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
