#ifndef IBM_VGA_H
#define IBM_VGA_H

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;
typedef unsigned long long int qword;

typedef struct
{
byte
gen_mis,
seq[5],
crt[25],
gct[9],
act[5];
}vgaregs_t;

void VGAWriteReg(byte set, byte index, byte value);
byte VGAReadReg(byte set, byte index);
void resetregs(vgaregs_t*regs);
void vgachangemode(vgaregs_t*regs);
void settextplane(void);
void setfontplane(void);
void VGASetPal(byte*pal,byte first,word num);
void VGAGetPal(byte*pal,byte first,word num);
void VGAGotoXY(byte x,byte y,byte w);
void VGAWhereXY(byte*x,byte*y,byte w);
void VGASetCursor(byte y,byte h);
void VGAGetCursor(byte*y,byte*h);
void VGACursor(byte e);
void VGASetFont(byte*fnt,byte ch,word first,word num);
void VGAGetFont(byte*fnt,byte ch,word first,word num);
void VGAWaitVBL(void);
byte VGAMode(byte m,word w,word h,byte o);


#endif
