#ifndef __DELAY_H
#define __DELAY_H 			   

#include "MM32L0xx.h"
	
void delay_init(void);
void delay_ms(__IO uint32_t nTime);
void delay_us(__IO uint32_t nTime);

#endif





























