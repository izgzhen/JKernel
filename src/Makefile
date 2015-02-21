SOURCES=                			\
	 main.o              			\
	 lib/mem.o 					\
	 lib/io.o 					\
	 lib/string.o 					\
	 lib/monitor.o       			\
	 lib/stdio.o 	\
	 asm/boot.o\
	 asm/gdt.o\
	 asm/interrupt.o\
	asm/process.o\
	 platform/isr.o\
	 platform/descriptor_tables.o\
	process/timer.o\
	memory/paging.o\
	memory/kheap.o\
	memory/kmalloc.o\
	memory/ordered_array.o\
	lib/panic.o\
	fs/fs.o\
	fs/initrd.o\
	process/task.o\
	usr/syscall.o\
	test/memory.o\
	dev/serial.o\
	lib/elf.o

CFLAGS=-g -O0 -Wall -nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 -I./include
LDFLAGS=-T link.ld -m elf_i386
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm -f *.o lib/*.o asm/*.o memory/*.o fs/*.o process/*.o usr/*.o platform/*.o kernel.elf

link:
	ld $(LDFLAGS) -o kernel.elf $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
