// Testing utilities for memory
// I will try to compile it first, then figure out some ways to get output from kernel, shit

#include <test/memory.h>

extern int32_t allocated_frames;

void show_allocated_frames(){
	printf("Allocated/All frames: %d/4096\n", allocated_frames);
}