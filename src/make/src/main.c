#include "delay.h"
#include "sys.h"
#include "led.h"
#include "uart.h"

int main(void)
{
    u8 t=0;
    
    delay_init();	
    LED_Init();		  	 	   
		Uart1_Init(9600);
		
    while(1)
    {
	    LED1_TOGGLE();  
	    LED2_TOGGLE();
	    delay_ms(300);	
    }
}



