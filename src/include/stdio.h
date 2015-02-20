// monitor.h -- Defines the interface for monitor.h

#ifndef STDIO_H
#define STDIO_H

#include <common.h>
#include <monitor.h>
#include <stdarg.h>

int32_t vprintf(const char *format, va_list ap);

int32_t printf(const char *format, ...);

// Output a null-terminated ASCII string to the monitor.
void monitor_write(const char *);

// Output a hex value to the monitor.
void monitor_write_hex(uint32_t n);

// Output a decimal value to the monitor.
void monitor_write_dec(uint32_t n);

#endif // STDIO_H
