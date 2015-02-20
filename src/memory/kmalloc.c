#include <kheap.h>
#include <paging.h>



extern page_directory_t *kernel_directory;  // Defined in paging.c
extern heap_t *kheap;   // Defined in heap.c
extern uint32_t end;  // Defined in linker's script
uint32_t placement_address = (uint32_t)&end;

#define ALIGNED     0x1
#define CLEARBIT    0x2

uint32_t kmalloc_int(uint32_t sz, int flags, uint32_t *phys)
{
    void *addr = NULL;

    if (kheap != NULL)
    {
        addr = alloc(sz, flags & ALIGNED, kheap);
        if (phys != NULL)
        {
            page_t *page =  get_page((uint32_t)addr, 0, kernel_directory);
            *phys = page->frame * 0x1000 + ((uint32_t)addr & 0xFFF);
        }
        // return (uint32_t)addr;
    }
    else
    {
        if ((flags & ALIGNED) && (placement_address & 0xFFFFF000) )
        {
            // Align the placement address;
            placement_address &= 0xFFFFF000;
            placement_address += 0x1000;
        }
        if (phys)
        {
            *phys = placement_address;
        }

        addr = (void *)placement_address;
        placement_address += sz;

    }

    if(flags & CLEARBIT)
        memset(addr, 0, sz);

    return (uint32_t)addr;
}

void kfree(void *p)
{
    free(p, kheap);
}

uint32_t kmalloc_a(uint32_t sz)
{
    return kmalloc_int(sz, ALIGNED, 0);
}

uint32_t kmalloc_ac(uint32_t sz)    // Clear bit
{
    return kmalloc_int(sz, ALIGNED | CLEARBIT, 0);
}


uint32_t kmalloc_p(uint32_t sz, uint32_t *phys)
{
    return kmalloc_int(sz, 0, phys);
}

uint32_t kmalloc_pc(uint32_t sz, uint32_t *phys)
{
    return kmalloc_int(sz, CLEARBIT, phys);
}

uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys)
{
    return kmalloc_int(sz, ALIGNED, phys);
}

uint32_t kmalloc_apc(uint32_t sz, uint32_t *phys)
{
    return kmalloc_int(sz, ALIGNED | CLEARBIT, phys);
}

uint32_t kmalloc(uint32_t sz)
{
    return kmalloc_int(sz, 0, 0);
}

uint32_t kmalloc_c(uint32_t sz)
{
    return kmalloc_int(sz, CLEARBIT, 0);
}
