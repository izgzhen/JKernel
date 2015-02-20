// Testing utilities for memory
// I will try to compile it first, then figure out some ways to get output from kernel, shit

#include <testing/memory.h>

extern int32_t allocated_frames;

void show_allocated_frames(){
	printf("Allocated/All frames: %d/4096\n", allocated_frames);
}

void show_directory(page_directory_t dir){
	int table_idx, page_idx, assigned;
	page_table_t tb;
	for(table_idx = 0;table_idx < TABLES_AMOUNT; table_idx++){
		assigned = 0;
		if (dir->tables[table_idx] != NULL){
			assigned++;
			tb = dir->tables[table_idx];

			for(page_idx = 0; i < PAGES_AMOUNT; i++)
				show_page_info(tb[page_idx]);

			printf("Assigned/All page tables: %d/1024 of page table %d\n", assigned, table_idx);
		}
	}
}


void show_page_info(page_table_t p){
	printf("None\n");
}