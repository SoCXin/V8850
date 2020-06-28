#include "delay.h"
#include "sys.h"
#include "uart.h"
#include "wkup.h"
#include "led.h"


int main(void)
{ 
    u8 i;
    u32 j;
    delay_init();
    LED_Init();		  		//初始化与LED连接的硬件接口
    
    for(i=0;i<5;i++)
    {
        LED1_TOGGLE();
        delay_ms(300);
    }
    LED1_OFF();
    WKUP_Init();			//初始化WK_UP按键，同时检测是否正常开机
    HSI_SYSCLK();//将HSI作为系统时钟
    Sys_Stop();//进入STOP模式
    
    while(1)
    {
        LED1_TOGGLE();
        LED2_TOGGLE();
        LED3_TOGGLE();
        LED4_TOGGLE();
        j = 30000;while(j--);
    }
}

