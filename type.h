#ifndef TYPE_H
#define TYPE_H

#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e

#define VIDEO_ADDRESS 0xa0000
#define MAX_ROWS 30 // 25
#define MAX_COLS 80 // 80
#define PIXEL_ROWS 480 // 480
#define PIXEL_COLS 640 // 640
#define WHITE_ON_BLACK 0x0f
#define BYTES_PER_COLOUR 3

#endif
