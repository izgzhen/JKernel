#ifndef STDARG_H
#define	STDARG_H
typedef	char *	va_list;

#define	__va_size(type) \
	(((sizeof(type) + sizeof(uint32_t) - 1) / sizeof(uint32_t)) * sizeof(uint32_t))

#define	va_start(ap, last) \
	((ap) = (va_list)&(last) + __va_size(last))

#define	va_arg(ap, type) \
	(*(type *)((ap) += __va_size(type), (ap) - __va_size(type)))

#if __ISO_C_VISIBLE >= 1999
#define	va_copy(dest, src) \
	((dest) = (src))
#endif

#define	va_end(ap)

#endif