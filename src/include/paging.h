// paging.h -- Defines the interface for and structures relating to paging.
//             Written for JamesM's kernel development tutorials.

#ifndef PAGING_H
#define PAGING_H

#include "common.h"
#include "isr.h"
#include "stdio.h"
#include "kmalloc.h"

#define DO_MAKE 1
#define PAGE_TABLE_SIZE 1024

#define READ_ONLY 0
#define READ_WRITE 1
#define SUPER 0
#define USER 1

typedef struct page
{
    uint32_t present    : 1;   // Page present in memory
    uint32_t rw         : 1;   // Read-only if clear, readwrite if set
    uint32_t user       : 1;   // Supervisor level only if clear
    uint32_t accessed   : 1;   // Has the page been accessed since last refresh?
    uint32_t dirty      : 1;   // Has the page been written to since last refresh?
    uint32_t unused     : 7;   // Amalgamation of unused and reserved bits
    uint32_t frame      : 20;  // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table
{
    page_t pages[PAGE_TABLE_SIZE];
} page_table_t;

typedef struct page_directory
{
    /**
       Array of pointers to pagetables.
    **/
    page_table_t *tables[PAGE_TABLE_SIZE];
    /**
       Array of pointers to the pagetables above, but gives their *physical*
       location, for loading into the CR3 register.
    **/
    uint32_t tablesPhysical[PAGE_TABLE_SIZE];

    /**
       The physical address of tablesPhysical. This comes into play
       when we get our kernel heap allocated and the directory
       may be in a different location in virtual memory.
    **/
    uint32_t physicalAddr;
} page_directory_t;

/**
   Sets up the environment, page directories etc and
   enables paging.
**/
void initialise_paging();

/**
   Causes the specified page directory to be loaded into the
   CR3 register.
**/
void switch_page_directory(page_directory_t *new);

void alloc_frame(page_t *page, bool is_kernel, bool is_writeable);
void free_frame(page_t *page);

/**o
   Retrieves a pointer to the page required.
   If make == 1, if the page-table in which this page should
   reside isn't created, create it!
**/
page_t *get_page(uint32_t address, bool do_make, page_directory_t *dir);

/**
   Handler for page faults.
**/
void page_fault(registers_t regs);


page_directory_t *clone_directory(page_directory_t *src);


#endif
