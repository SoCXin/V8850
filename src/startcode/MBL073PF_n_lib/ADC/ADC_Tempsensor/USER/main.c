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
    float Temp;
    delay_init();
    LED_Init();
    uart_initwBaudRate(115200);	 //串口初始化为115200
    
    /*配置为内部温度传感器*/
    ADC1_SingleChannel( ADC_Channel_10);
    while(1)
    {
        ADCVAL=Get_Adc_Average(ADC_Channel_10,5);
        Temp=27.0+(ADCVAL-1800)/5.96;
        printf("内部温度=%.2f度\r\n",Temp);
        delay_ms(1000);  
    }
}
