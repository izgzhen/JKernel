#ifndef __MEM_TEST__
#define __MEM_TEST__

#include <paging.h>
#include <stdio.h>

#define TABLES_AMOUNT 1024
#define PAGES_AMOUNT 1024

void show_allocated_frames();
void show_directory(page_directory_t);
void show_page_info(page_table_t);

#endif