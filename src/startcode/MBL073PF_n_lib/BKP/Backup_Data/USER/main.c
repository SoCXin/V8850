#include "delay.h"
#include "sys.h"
#include "led.h"
#include "bkp.h"

/********************************************************************************************************
**函数信息 ：main(void)                     
**功能描述 ：
**输入参数 ：无
**输出参数 ：无
********************************************************************************************************/
int main(void)    
{
    u8 flag=0;
    delay_init();
    LED_Init();
    flag = BKP_DATA();		 //往BKP写数据，如果成功则LED满闪，失败则快速闪烁
    
    if(flag==0)	
    {
        while(1)              //无限循环
        {
            LED1_TOGGLE();
            LED2_TOGGLE();
            LED3_TOGGLE();
            LED4_TOGGLE();
            delay_ms(1000);//BKP数据读写成功，慢闪
        }
    }
    else
    {
        while(1)              //无限循环
        {
            LED1_TOGGLE();
            LED2_TOGGLE();
            LED3_TOGGLE();
            LED4_TOGGLE();
            delay_ms(50);//BKP数据读写失败，快闪
        }
    }
}



