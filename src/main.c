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
#include <test/memory.h>

extern uint32_t placement_address;
uint32_t initial_esp;
extern multiboot_header_t *mboot_ptr;

void serial_com(){
    s_write("Serial ports...\n");
    printf("From serial:\n");
    while(TRUE)
      printf("%c",read_serial());
}

void showFS(){
  asm volatile("cli");
  int i = 0;
  struct dirent *node = 0;
  while ( (node = readdir_fs(fs_root, i)) != 0)
    {
      monitor_write("Found file ");
      monitor_write(node->name);
      fs_node_t *fsnode = finddir_fs(fs_root, node->name);

      if ((fsnode->flags&0x7) == FS_DIRECTORY)
	monitor_write("\n\t(directory)\n");
      else
        	{
        	  monitor_write("\n\t contents: \"");
        	  char buf[256];
        	  uint32_t sz = read_fs(fsnode, 0, 256, buf);
        	  int j;
        	  for (j = 0; j < sz; j++)
        	    monitor_put(buf[j]);

        	  monitor_write("\"\n");
        	}
      i++;
    }
   asm volatile("sti");
}  

int k_main(multiboot_header_t *ptr, uint32_t initial_stack)
{
    mboot_ptr = ptr;
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

    printf("Initialize serial ports..\n");
    init_serial();
    
    show_allocated_frames();

    // Initialise the initial ramdisk, and set it as the filesystem root.
    fs_root = initialise_initrd(initrd_location);

     // Create a new process in a new address space which is a clone of this.
    /*    int ret = fork();

    monitor_write("fork() returned ");
    monitor_write_hex(ret);
    monitor_write(", and getpid() returned ");
    monitor_write_hex(getpid());
    */
    showFS();

    printf("Switching to user mode...\n");
    switch_to_user_mode();
    
    syscall_monitor_write("Hello, user world!\n");

    return 0;
}
