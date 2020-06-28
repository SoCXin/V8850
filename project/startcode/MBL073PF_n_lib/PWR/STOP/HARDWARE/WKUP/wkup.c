#include "wkup.h"
#include "led.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//开发板
//待机唤醒 代码	   
//////////////////////////////////////////////////////////////////////////////////

void Sys_Stop(void)
{  
    PWR_EnterSTOPMode(0, PWR_STOPEntry_WFI);
    
}
//////////////////////////////////////////////////////////////////////////////////	 
//将HSI作为系统时钟  
//////////////////////////////////////////////////////////////////////////////////
void HSI_SYSCLK(void)
{
    RCC_HSICmd(ENABLE);
    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY)==RESET);
    RCC->CFGR &=~ 0xf;
    while((RCC->CFGR&0xf) != 0x0);
}	

/********************************************************************************************************
**函数信息 ：EXTI0_IRQHandler(void)                         
**功能描述 ：外部中断0，进入后清除中断标志位
**输入参数 ：无
**输出参数 ：无
********************************************************************************************************/
void EXTI0_1_IRQHandler(void)
{ 		    		    				     		    
    EXTI_ClearITPendingBit(EXTI_Line0); // 清除LINE10上的中断标志位		  
} 

/********************************************************************************************************
**函数信息 ：WKUP_Init(void)                         
**功能描述 ：外部中断唤醒待机初始化
**输入参数 ：无
**输出参数 ：无
********************************************************************************************************/
void WKUP_Init(void)
{	
    GPIO_InitTypeDef GPIO_InitStructure;  		  
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_SYSCFG, ENABLE);//使能GPIOA和复用功能时钟
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//PA.0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//下拉输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化IO
    //使用外部中断方式
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,  EXTI_PinSource0);
    
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;	//设置按键所有的外部线路
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//设外外部中断模式:EXTI线路为中断请求
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//上升沿触发EXTI_Trigger_Falling;//
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);//初始化外部中断
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_1_IRQn;//使能按键所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPriority = 2;//先占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
    
    PWR_WakeUpPinCmd(ENABLE); 
}

