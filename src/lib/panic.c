/*
 *       Filename:  panic.c
 *       Author:  Hurley (LiuHuan), James
 */

#include  "panic.h"

static elf_t kernel_elf;

void init_debug()
{
    // 从 GRUB 提供的信息中获取到内核符号表和代码地址信息
    kernel_elf = elf_from_multiboot(glb_mboot_ptr);
}

void print_cur_status() {
    static int round = 0;
    uint16_t reg1, reg2, reg3, reg4;

    asm volatile (  "mov %%cs, %0;"
            "mov %%ds, %1;"
            "mov %%es, %2;"
            "mov %%ss, %3;"
            : "=m"(reg1), "=m"(reg2), "=m"(reg3), "=m"(reg4));

    // 打印当前的运行级别
    printf("%d: @ring %d\n", round, reg1 & 0x3);
    printf("%d:  cs = %x\n", round, reg1);
    printf("%d:  ds = %x\n", round, reg2);
    printf("%d:  es = %x\n", round, reg3);
    printf("%d:  ss = %x\n", round, reg4);
    ++round;
}

static void print_stack_trace()
{
    uint32_t *ebp, *eip;

    asm volatile ("mov %%ebp, %0" : "=r" (ebp));
    while (ebp) {
        eip = ebp + 1;
        printf("   [0x%x] %s\n", *eip, elf_lookup_symbol(*eip, &kernel_elf));
        ebp = (uint32_t*)*ebp;
    }
}

void panic(const char *message, const char *file, uint32_t line)
{
    // We encountered a massive problem and have to stop.
    asm volatile("cli"); // Disable interrupts.

    printf("PANIC(%s) at %s : %d \n", message, file, line);
    print_stack_trace();
    // Halt by going into an infinite loop.
    for(;;);
}

void panic_assert(const char *file, uint32_t line, const char *desc)
{
    // An assertion failed, and we have to panic.
    asm volatile("cli"); // Disable interrupts.

    printf("ASSERTION-FAILED(%s) at %s: %d\n", desc, file, line);
    // Halt by going into an infinite loop.
    for(;;);
}
