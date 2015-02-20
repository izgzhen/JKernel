#ifndef KMALLOC_H
#define KMALLOC_H

#include "common.h"

uint32_t kmalloc_int(uint32_t sz, int flags, uint32_t *phys);
uint32_t kmalloc_a(uint32_t sz);
uint32_t kmalloc_ac(uint32_t sz);
uint32_t kmalloc_p(uint32_t sz, uint32_t *phys);
uint32_t kmalloc_pc(uint32_t sz, uint32_t *phys);
uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys);
uint32_t kmalloc_apc(uint32_t sz, uint32_t *phys);
uint32_t kmalloc(uint32_t sz);
uint32_t kmalloc_c(uint32_t sz);

void kfree(void *p);

#endif
