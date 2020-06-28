#include "delay.h"
#include "sys.h"
#include "uart.h"
#include "adc.h"
#include "led.h"

/********************************************************************************************************
**函数信息 ：main(void)
**功能描述 ：
**输入参数 ：
**输出参数 ：
**    备注 ：
********************************************************************************************************/
int main(void)
{
    u16 ADCVAL;
    float fValue;
    delay_init();
    LED_Init();
    uart_initwBaudRate(115200);	 //串口初始化为115200
    
    /*配置为内部1.2V参考电压*/
    ADC1_SingleChannel( ADC_Channel_11);
    while(1)
    {
        ADCVAL=Get_Adc_Average(ADC_Channel_11,5);
        fValue = ((float)ADCVAL/4095)*3.3;
        printf("内部参考电压=%fV\r\n",fValue);
        delay_ms(1000);  
    }
    
}
