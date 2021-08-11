#include "../type.h"
#include "../ports.h"
#include "../util.h"
#include "keyboard.h"
#include "display.h"

extern int commandLength;

void set_cursor(int offset) {
    offset /= 2;
    out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    out(VGA_DATA_REGISTER, (unsigned char) (offset >> 8));
    out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    out(VGA_DATA_REGISTER, (unsigned char) (offset & 0xff));
}

int get_cursor() {
    out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    int offset = in(VGA_DATA_REGISTER) << 8;
    out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    offset += in(VGA_DATA_REGISTER);
    return offset * 2;
}

int get_row_from_offset(int offset) {
    return offset / (2 * MAX_COLS);
}

int get_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

int move_offset_to_new_line(int offset) {
    return get_offset(0, get_row_from_offset(offset) + 1);
}

int scroll_ln(int offset) {
    memcpy(
            (char *) (get_offset(0, 1) + VIDEO_ADDRESS),
            (char *) (get_offset(0, 0) + VIDEO_ADDRESS),
            MAX_COLS * (MAX_ROWS - 1) * 2
    );

    for (int col = 0; col < MAX_COLS; col++) {
        set_char_at_video_memory(' ', get_offset(col, MAX_ROWS - 1));
    }
    
    return offset - 2 * MAX_COLS;
}

void set_char_at_video_memory(char character, int offset) {
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    vidmem[offset] = character;
    vidmem[offset + 1] = WHITE_ON_BLACK;
}

void print_string(char *string) {
    int i = 0;
    int offset = get_cursor();
    while (string[i] != 0) {
        if (offset >= MAX_ROWS * MAX_COLS * 2) {
            offset = scroll_ln(offset);
        }
        switch (string[i])
        {
        case '\n':
            offset = move_offset_to_new_line(offset);
            break;
        
        default:
            set_char_at_video_memory(string[i], offset);
            offset += 2;
            break;
        }
        i++;
    }
    set_cursor(offset);
}

void clear_screen() {
    for (int i = 0; i < MAX_COLS * MAX_ROWS; i++) {
        set_char_at_video_memory(' ', i * 2);
    }
    set_cursor(get_offset(0, 0));
}

void backspace() {
    if (commandLength > 0) {
        int offset = get_cursor();
        offset -= 2;
        set_char_at_video_memory(' ', offset);
        set_cursor(offset);
        commandLength--;
    }
}