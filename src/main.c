// main.c -- Defines the C-code kernel entry point, calls initialisation routines.

#include <monitor.h>
#include <descriptor_tables.h>
#include <timer.h>
#include <paging.h>
#include <multiboot.h>
#include <fs.h>
#include <initrd.h>
#include <task.h>
#include <syscall.h>
#include <serial.h>

extern uint32_t placement_address;
uint32_t initial_esp;

int k_main(struct multiboot *mboot_ptr, uint32_t initial_stack)
{
    initial_esp = initial_stack;
    monitor_clear();

    printf("Initialize ISR and segmentation ...\n");
    init_descriptor_tables();

    printf("Initialize PIT...\n");
    asm volatile("sti");
    init_timer(50);

    printf("Locating ramdisk ...\n");
    // Find the location of our initial ramdisk.
    ASSERT(mboot_ptr->mods_count > 0);
    uint32_t initrd_location = *((uint32_t*)mboot_ptr->mods_addr);
    uint32_t initrd_end = *(uint32_t*)(mboot_ptr->mods_addr+4);
    placement_address = initrd_end;

    printf("Initialize paging...\n");
    initialise_paging();

    printf("Initialize processes...\n");
    initialise_tasking();

    printf("Initialize ramdisk...\n");
    fs_root = initialise_initrd(initrd_location);

    printf("Initialize system call...\n");
    initialise_syscalls();

    printf("Initialize serial ports...\n");
    init_serial();
    write_serial('a');

    printf("Switching to user mode...\n");
    switch_to_user_mode();

    syscall_monitor_write("Hello, user world!\n");

    return 0;
}
