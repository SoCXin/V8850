/**
  ******************************************************************************
  * @file    uart_test.c  
  * @brief   配置串口功能
  *          
  ******************************************************************************
  */
#include "uart_test.h"
/********************************************************************************************************
**函数信息 ：UartInit(USART_TypeDef* USARTx)                      
**功能描述 ：初始化串口
**输入参数 ：USART_TypeDef* USARTx ，选择USART1、USART2、USART3
**输出参数 ：无
********************************************************************************************************/

void UartInit(USART_TypeDef* USARTx)
{
	USART_InitTypeDef       USART_InitStructure;  
	GPIO_InitTypeDef  GPIO_InitStructure;   
	
if(USARTx==USART1)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;                                                          //uart1_tx  pa9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                                     // 推免复用输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;                                                         //uart1_rx  pa10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                                                       //上拉输入   
	GPIO_Init(GPIOA, &GPIO_InitStructure);
			
}	
 
if(USARTx==USART2)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;                                                         //uart1_tx  pa2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                                    // 推免复用输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;                                                         //uart1_rx  pa3
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                                                      //上拉输入   
	GPIO_Init(GPIOA, &GPIO_InitStructure);
			
}	

if(USARTx==USART3)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;                                                        //uart3_tx  pc10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                                    // 推免复用输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;                                                        //uart3_rx  pc11
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                                                      //上拉输入   
	GPIO_Init(GPIOC, &GPIO_InitStructure);
			
}	
		
	USART_InitStructure.USART_BaudRate =  115200;                                                          //115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 	
	USART_Init(USARTx, &USART_InitStructure);

	/*UART 模块使能*/
	USART_Cmd(USARTx, ENABLE);  

	/*清除中断标志*/
	USART_ClearITPendingBit(USART1, 0xff); 
	USART_ClearITPendingBit(USART2, 0xff); 
}

/********************************************************************************************************
**函数信息 ：uart_send(USART_TypeDef* USARTx,char c)                    
**功能描述 ：串口发送字节
**输入参数 ：USART_TypeDef* USARTx ，选择USART1、USART2、USART3
**输入参数 ：char c ,串口发送的字节
**输出参数 ：无
********************************************************************************************************/

void uart_send(USART_TypeDef* USARTx,char c)
{
	USART_SendData(USARTx,(uint16_t)c);  
	
	while(1)
	{
		if(USART_GetITStatus(USARTx, USART_IT_TXIEN))
	
		{
			 USART_ClearITPendingBit(USARTx, USART_IT_TXIEN);
			 break;
		}
		
	}
}

/********************************************************************************************************
**函数信息 ：unsigned char inbyte(USART_TypeDef* USARTx)                
**功能描述 ：串口接收函数
**输入参数 ：USART_TypeDef* USARTx ，选择USART1、USART2、USART3
**输出参数 ：unsigned char 串口接收返回的字节
********************************************************************************************************/

unsigned char inbyte(USART_TypeDef* USARTx)
{
	unsigned char temp;

	while(1)
	{
		if(USART_GetITStatus(USARTx, USART_IT_RXIEN))
		{
			 /*清除接收中断位*/
			USART_ClearITPendingBit(USARTx, USART_IT_RXIEN); 
			break;
		}	
	}
	temp = (uint8_t)USART_ReceiveData(USARTx); 
	return temp;
}


/********************************************************************************************************
**函数信息 ：void Uart1RxTest(USART_TypeDef* USARTx)               
**功能描述 ：串口接收函数测试
**输入参数 ：USART_TypeDef* USARTx ，选择USART1、USART2、USART3
**输出参数 ：无
********************************************************************************************************/

unsigned int Uart1RxTest(USART_TypeDef* USARTx)
{
	unsigned char temp;
	temp = inbyte(USARTx);
	return temp;	
}


/********************************************************************************************************
**函数信息 ：void outbyte(char c)               
**功能描述 ：串口发送函数测试，通过电脑超级终端或者串口软件打印出来
**输入参数 ：char c 串口发送的字节
**输出参数 ：无
********************************************************************************************************/

void outbyte(char c)
{
	/* 如果调用USART2、USART3,更换该函数的第一个参数即可 */
	uart_send(USART1,c); 
}



