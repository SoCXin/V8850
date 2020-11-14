#include <stdarg.h>
#include <string.h>

#include "uart.h"
#include "misc.h"

static unsigned char		fac_us;
static unsigned short		fac_ms;

unsigned short crc16r(unsigned char *ptr, unsigned char length)
{
	unsigned char i;
	unsigned short crc;

	crc = 0;
	while(length--!=0)
	{
		for(i=0x01; i!=0; i <<= 1)
		{
			if((crc&0x0001)!=0)
			{
				crc >>= 1;
				crc ^= 0x8408;
			}
			else
				crc >>= 1;

			if((*ptr&i)!=0)
				crc ^= 0x8408;
		}
		ptr++;
	}

	return crc;
}

unsigned char bccCheck(unsigned char *dat, unsigned char length)
{
    unsigned char       bcc, l;

    bcc = 0;
    if(length)
    {
        l = length;
        while(l)
        {
            bcc ^= dat[length - l];
            l--;
        }
    }

    return bcc;
}

char* itoa(unsigned int i)
{
	static char a[20];

	char *b = a + sizeof(a) - 1;
	unsigned int   sign = (i < 0);

	if(sign)
		i = -i;
	*b = 0;
	do {
		*--b = '0' + (i % 10);
		i /= 10;
	} while (i);

	if(sign)
		*--b = '-';

	return b;
}

void xitoa(long val, int radix, int len)
{
	unsigned char c, r, sgn = 0, pad = ' ';
	unsigned char s[20], i = 0;
	unsigned long v;


	if (radix < 0) {
		radix = -radix;
		if (val < 0) {
			val = -val;
			sgn = '-';
		}
	}
	v = val;
	r = radix;
	if (len < 0) {
		len = -len;
		pad = '0';
	}
	if (len > 20) return;
	do {
		c = (unsigned char)(v % r);
		if (c >= 10) c += 7;
		c += '0';
		s[i++] = c;
		v /= r;
	} while (v);
	if (sgn) s[i++] = sgn;
	while (i < len)
		s[i++] = pad;
	do
		Uart1_Put_Char(s[--i]);
	while (i);
}

void xitoab(unsigned char *buf, long val, int radix, int len)
{
	unsigned char c, r, sgn = 0, pad = ' ';
	unsigned char s[20], i = 0;
	unsigned long v;

	if (radix < 0) {
		radix = -radix;
		if (val < 0) {
			val = -val;
			sgn = '-';
		}
	}
	v = val;
	r = radix;
	if (len < 0) {
		len = -len;
		pad = '0';
	}
	if (len > 20) return;
	do {
		c = (unsigned char)(v % r);
		if (c >= 10) c += 7;
		c += '0';
		s[i++] = c;
		v /= r;
	} while (v);
	if (sgn) s[i++] = sgn;
	while (i < len)
		s[i++] = pad;
	do
		*buf++ = s[--i];
	while (i);
}

void qprintf(const char* str, ...)
{
	va_list arp;
	int d, r, w, s, l;


	va_start(arp, str);

	while ((d = *str++) != 0) {
		if (d != '%') {
			Uart1_Put_Char(d); continue;
		}
		d = *str++; w = r = s = l = 0;
		if (d == '0') {
			d = *str++; s = 1;
		}
		while ((d >= '0')&&(d <= '9')) {
			w += w * 10 + (d - '0');
			d = *str++;
		}
		if (s) w = -w;
		if (d == 'l') {
			l = 1;
			d = *str++;
		}
		if (!d) break;
		if (d == 's') {
			Uart1_Put_string((unsigned char *)va_arg(arp, char*));
			continue;
		}
		if (d == 'c') {
			Uart1_Put_Char((char)va_arg(arp, int));
			continue;
		}
		if (d == 'u') r = 10;
		if (d == 'd') r = -10;
		if (d == 'X') r = 16;
		if (d == 'x') r = 16;
		if (d == 'b') r = 2;
		if (!r) break;
		if (l) {
			xitoa((long)va_arg(arp, long), r, w);
		} else {
			if (r > 0)
				xitoa((unsigned long)va_arg(arp, int), r, w);
			else
				xitoa((long)va_arg(arp, int), r, w);
		}
	}
	va_end(arp);
}

void qsprintf(unsigned char* ostr, const char* str, ...)
{
	va_list arp;
	int d, r, w, s, l;
	unsigned char buf[8], *ptr;

	va_start(arp, str);

	while ((d = *str++) != 0) {
		memset(buf, 0x00, sizeof(buf));
		if (d != '%') {
			*ostr++ = d;
			continue;
		}
		d = *str++; w = r = s = l = 0;
		if (d == '0') {
			d = *str++; s = 1;
		}
		while ((d >= '0')&&(d <= '9')) {
			w += w * 10 + (d - '0');
			d = *str++;
		}
		if (s) w = -w;
		if (d == 'l') {
			l = 1;
			d = *str++;
		}
		if (!d) break;
		if (d == 's') {
			ptr = (unsigned char *)va_arg(arp, char*);
			while(*ptr)
					*ostr++ = *ptr++;
			continue;
		}
		if (d == 'c') {
			*ostr++ = (char)va_arg(arp, int);
			continue;
		}
		if (d == 'u') r = 10;
		if (d == 'd') r = -10;
		if (d == 'X') r = 16;
		if (d == 'x') r = 16;
		if (d == 'b') r = 2;
		if (!r) break;
		if (l) {
			xitoab(buf, (long)va_arg(arp, long), r, w);
			ptr = (unsigned char *)&buf;
			while(*ptr)
				*ostr++ = *ptr++;
		} else {
			if (r > 0)
			{
				xitoab(buf, (unsigned long)va_arg(arp, int), r, w);
				ptr = (unsigned char *)&buf;
				while(*ptr)
					*ostr++ = *ptr++;
			} else {
				xitoab(buf, (long)va_arg(arp, int), r, w);
				ptr = (unsigned char *)&buf;
				while(*ptr)
					*ostr++ = *ptr++;
			}
		}
	}

	va_end(arp);
}

void SysTick_Init(unsigned char SYSCLK)
{
	SysTick->CTRL = 0xFFFFFFFB;
	
	fac_us = SYSCLK / 8;
	fac_ms = (unsigned short)fac_us * 1000;
}

void delay_ms(unsigned short ms)  
{  
	unsigned long			temp;
	
	SysTick->LOAD = (unsigned long)ms * fac_ms;
	SysTick->VAL = 0x00;
	SysTick->CTRL = 0x01;
	
	do {
		temp = SysTick->CTRL;	
	} while((temp & 0x01) && (!(temp & (1 << 16))));
	
	SysTick->CTRL = 0x00;
	SysTick->VAL = 0x00;
}  

void delay_us(unsigned short us)  
{  
	unsigned long			temp;
	
	SysTick->LOAD = (unsigned long)us * fac_us;
	SysTick->VAL = 0x00;
	SysTick->CTRL = 0x01;
	
	do {
		temp = SysTick->CTRL;	
	} while((temp & 0x01) && (!(temp & (1 << 16))));
	
	SysTick->CTRL = 0x00;
	SysTick->VAL = 0x00;
} 

#if 0
void delay_us(unsigned long delayTime)      // Base: 2uS, Step: 0.1uS
{
    unsigned long       nTime;

    nTime = 12 * delayTime;
    __asm__ __volatile__(
        ".syntax unified        \n\t"
        "       MOV r0, %0      \n\t"
        "1:     SUBS r0, #1     \n\t"
        "       BHI 1b          \n\t"
        :
        : "r" (nTime)
        : "cc");
}
#endif


unsigned int filter(unsigned int *value_buf)  
{  
	unsigned char			count, i, j;   
	unsigned int			sum = 0, temp = 0;
  
	for(j = 0; j < SAMPLETIMES - 1; j++)  
	{  
		for(i = 0; i < SAMPLETIMES - j; i++)  
		{  
			if(value_buf[i] > value_buf[i + 1])  
			{  
				temp = value_buf[i];  
				value_buf[i] = value_buf[i+1];   
				value_buf[i+1] = temp;  
			}  
		}  
	}  
	
	for(count = 1; count < SAMPLETIMES - 1; count++)  
		sum += value_buf[count];  

	return	(sum / (SAMPLETIMES - 2));  
}  





