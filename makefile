# $@ = target file
# $< = first dependency
# $^ = all dependencies

CC = /mnt/c/users/olive/Desktop/coding/os2/osb/opt/cross/bin/i686-elf-gcc
LD = /mnt/c/users/olive/Desktop/coding/os2/osb/opt/cross/bin/i686-elf-ld

FILES = kernel-entry.o \
kernel.o \
drivers/display.o \
drivers/keyboard.o \
ports.o \
util.o \
idt.o \
irq.o \
isr.o \
isr-handler.o \

#CC = gcc
#LD = ld

# First rule is the one executed when no parameters are fed to the Makefile
all: os-image.bin

kernel.bin: $(FILES)
	$(LD) -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel-entry.o: kernel-entry.asm
	nasm $< -felf -o $@

isr-handler.o: isr-handler.asm
	nasm $< -felf -o $@

.c.o:
	$(CC) -m32 -ffreestanding -c $< -o $@

mbr.bin: mbr.asm
	nasm $< -fbin -o $@

os-image.bin: mbr.bin kernel.bin
	cat $^ > $@

clean:
	$(RM) *.bin *.o *.dis *.lock
