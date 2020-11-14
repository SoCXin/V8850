/*********************************Copyright (c)*********************************
  *                              jmqiu@icwiser.com
  ******************************************************************************
  * 文件名称：uart.c
  * 描    述：串口通信模块
  * 创 建 者: Eric Qiu
  * 创建日期: 2015-05-11
  * 修 改 者:
  * 修改日期: 2015-05-11
  * 版    本: v1.0.0
  ******************************************************************************
  * attention
  *
  ******************************************************************************
  */

/*Includes --------------------------------------------------------------------*/
#include "HAL_conf.h"

/* 类型定义 typedef-----------------------------------------------------------*/
/* 预定义字符     ------------------------------------------------------------*/
/* 宏定义        -------------------------------------------------------------*/

/*******************************************************************************
* 函数名称: Uart_Init()
* 功能描述: 串口初始化
* 输入参数: void
* 返回参数: 无
********************************************************************************/
void Uart1_Init(unsigned long bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    UART_InitTypeDef UART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_UART1, ENABLE);	
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);  
    
    
    NVIC_InitStructure.NVIC_IRQChannel = UART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 3;		
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
    NVIC_Init(&NVIC_InitStructure);	
    
    
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_1);
    
    UART_InitStructure.UART_BaudRate = bound;
    UART_InitStructure.UART_WordLength = UART_WordLength_8b;
    UART_InitStructure.UART_StopBits = UART_StopBits_1;
    UART_InitStructure.UART_Parity = UART_Parity_No;
    UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
    UART_InitStructure.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;	
    
    UART_Init(UART1, &UART_InitStructure); 
    UART_ITConfig(UART1, UART_IT_RXIEN, ENABLE);
    UART_Cmd(UART1, ENABLE);                    
    
    //UART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//
    GPIO_Init(GPIOA, &GPIO_InitStructure);//
    
    //UART1_RX	  GPIOA
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//
    GPIO_Init(GPIOA, &GPIO_InitStructure);// 
}

/*******************************************************************************
* 函数名称: Uart_Put_Char()
* 功能描述: 通过UART发送一个字符
* 输入参数: void
* 返回参数: 无
********************************************************************************/
void Uart1_Put_Char(unsigned char c)
{
    while(!UART_GetFlagStatus(UART1, UART_FLAG_TXEMPTY));
        UART_SendData(UART1, (unsigned short)c);
}

/*******************************************************************************
* 函数名称:  Uart_Put_string
* 功能描述: 通过UART发送字符串
* 输入参数: void
* 返回参数: 无
********************************************************************************/
void Uart1_Put_string(unsigned char *s)
{
    while(*s != '\0')
        Uart1_Put_Char(*(s++));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
* 函数名称: USART1_IRQHandler()
* 功能描述: 串口1中断处理函数
* 输入参数: void
* 返回参数: 无
* 说    明：可以随时用 USART_ITConfig(USART1, USART_IT_TXE, DISABLE);来关闭中断响应。
********************************************************************************/
void USART1_IRQHandler(void)
{
    unsigned char uCh;

    if(UART_GetITStatus(UART1, UART_IT_RXIEN)  != RESET)  //
    {
        UART_ClearITPendingBit(UART1,UART_IT_RXIEN);
        uCh =UART_ReceiveData(UART1);	//
        Uart1_Put_Char(uCh+1);
    } 
}


