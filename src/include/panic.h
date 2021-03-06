#ifndef PANIC_H
#define PANIC_H

#include <stdio.h>
#include <elf.h>
#include <multiboot.h>

#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

void init_debug();
void print_cur_status();

void panic(const char *message, const char *file, uint32_t line);
void panic_assert(const char *file, uint32_t line, const char *desc);

#endif
