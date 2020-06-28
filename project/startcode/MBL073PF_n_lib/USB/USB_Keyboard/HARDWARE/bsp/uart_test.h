#ifndef __USRT_TEST_H_
#define __USRT_TEST_H_
#include "sys.h" 

void          UartInit(USART_TypeDef* USARTx);
void          uart_send(USART_TypeDef* USARTx,char c);
unsigned int  Uart1RxTest(USART_TypeDef* USARTx);
void          outbyte (char);
unsigned char inbyte(USART_TypeDef* USARTx);
#endif
