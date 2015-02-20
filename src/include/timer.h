// timer.h -- Defines the interface for all PIT-related functions.
//            Written for JamesM's kernel development tutorials.

#ifndef TIMER_H
#define TIMER_H

#include "common.h"
#include "isr.h"
#include "monitor.h"
#include "task.h"
#include "stdio.h"

void init_timer(uint32_t frequency);

#endif
