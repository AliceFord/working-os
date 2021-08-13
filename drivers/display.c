#include "../type.h"
#include "../ports.h"
#include "../util.h"
#include "keyboard.h"
#include "display.h"
#include "../cstd.h"

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end) {
	out(0x3D4, 0x0A);
	out(0x3D5, (in(0x3D5) & 0xC0) | cursor_start);
 
	out(0x3D4, 0x0B);
	out(0x3D5, (in(0x3D5) & 0xE0) | cursor_end);
}

void set_cursor(int offset) {
    curOffset = offset;
    // out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    // out(VGA_DATA_REGISTER, (unsigned char) (offset >> 8));
    // out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    // out(VGA_DATA_REGISTER, (unsigned char) (offset & 0xff));
}

int get_cursor() {
    return curOffset;
    // out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    // int offset = in(VGA_DATA_REGISTER) << 8;
    // out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    // offset += in(VGA_DATA_REGISTER);
}

int get_row_from_offset(int offset) {
    return offset / MAX_COLS;
}

int get_offset(int col, int row) {
    return row * MAX_COLS + col;
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
    
    return offset - MAX_COLS;
}

void set_char_at_video_memory(unsigned char character, int offset) {
    unsigned char *vidmem = (unsigned char *)VIDEO_ADDRESS;
    // vidmem[offset] = character;
    // vidmem[offset + 1] = WHITE_ON_BLACK;

    // for (int i = 0; i < 640 * 3; i++) 
    //     *(vidmem + i) = 0xff;
    
    // for (int i = 0; i < 1280 * 3; i++) 
    //     *(vidmem + i + 1280 * 3 * 2) = 0xff;

    int row = offset / MAX_COLS;
    int col = offset % MAX_COLS;
    int pos;
    row *= 16;
    col *= 8;
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 8; j++) {
            pos = (row + i) * PIXEL_COLS + col + j;
            unsigned char charRow = defaultFont[character][i];
            if ((charRow >> (8 - j - 1)) & 0b1 == 0b1) {
                for (int bt = 0; bt < BYTES_PER_COLOUR; bt++)
                    vidmem[pos * BYTES_PER_COLOUR + bt] = 0xff;
            } else {
                for (int bt = 0; bt < BYTES_PER_COLOUR; bt++)
                    vidmem[pos * BYTES_PER_COLOUR + bt] = 0x0;
            }
        }
    }
    // for (int i = 0; i < 320; i++) 
    //     *(vidmem + i) = 0xaa;
}

void print_string(unsigned char *string) {
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
            offset++;
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

void backspace(char buffer[]) {
    int length = strlen(buffer);
    if (length > 0) {
        int offset = get_cursor();
        offset--;
        set_char_at_video_memory(' ', offset);
        set_cursor(offset);
        buffer[length - 1] = '\0';
    }
}
