#include <stdio.h>
#include <monitor.h>

int32_t vprintf(const char *fmt, va_list ap)
{
	const char *hex = "0123456789abcdef";
	char buf[11];
	char *s;
	unsigned u;
	int32_t ret = 0, i, c;

	while ((c = *fmt++)) {
		if (c == '%') {
			c = *fmt++;
			switch (c) {
			case 'c':
				monitor_put(va_arg(ap, int));
				ret++;
				continue;
			case 's':
				for (s = va_arg(ap, char *); *s; s++) {
					monitor_put(*s);
					ret++;
				}
				continue;
			case 'd':
				i = va_arg(ap, int);
				u = (i < 0 ? -i : i);
				s = buf;
				do {
					*s++ = '0' + u % 10U;
				} while (u /= 10U);
				if (i < 0)
					*s++ = '-';
				goto dumpbuf;
			case 'u':
				u = va_arg(ap, unsigned);
				s = buf;
				do {
					*s++ = '0' + u % 10U;
				} while (u /= 10U);
				goto dumpbuf;
			case 'x':
				u = va_arg(ap, unsigned);
				s = buf;
				do {
					*s++ = hex[u & 0xfu];
				} while (u >>= 4);
			dumpbuf:
				while (--s >= buf) {
					monitor_put(*s);
					ret++;
				}
				continue;
			}
		}
		monitor_put(c);
		ret++;
	}

	return (ret);
}


int32_t printf(const char *fmt,...)
{
	va_list ap;
	int32_t ret;

	va_start(ap, fmt);
	ret = vprintf(fmt, ap);
	va_end(ap);

	return (ret);
}

// Outputs a null-terminated ASCII string to the monitor.
void monitor_write(const char *c)
{
    int i = 0;
    while (c[i])
        monitor_put(c[i++]);
}

void monitor_write_hex(uint32_t n)
{
    int32_t tmp;

    monitor_write("0x");

    char noZeroes = 1;

    int i;
    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && noZeroes != 0)
        {
            continue;
        }
    
        if (tmp >= 0xA)
        {
            noZeroes = 0;
            monitor_put (tmp-0xA+'a' );
        }
        else
        {
            noZeroes = 0;
            monitor_put( tmp+'0' );
        }
    }
  
    tmp = n & 0xF;
    if (tmp >= 0xA)
    {
        monitor_put (tmp-0xA+'a');
    }
    else
    {
        monitor_put (tmp+'0');
    }

}

void monitor_write_dec(uint32_t n)
{

    if (n == 0)
    {
        monitor_put('0');
        return;
    }

    int32_t acc = n;
    char c[32];
    int i = 0;
    while (acc > 0)
    {
        c[i] = '0' + acc%10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0)
    {
        c2[i--] = c[j++];
    }
    monitor_write(c2);

}
