#include "delay.h"
#include "sys.h"
#include "uart.h"
#include "uart_loop.h"
/********************************************************************************************************
**������Ϣ ��int main (void)                          
**�������� ��������ARMLED����
**������� ��
**������� ��
********************************************************************************************************/

int main(void)
{
    
    UartInit_Loop();  //UART1�ķ��ͣ�����ͨ������������ӡUART OK
    while(1)              //����ѭ��
    {
        Uart1RxTest(UART1);//UART1�Ľ��գ��ڴ��������������ַ�������ͨ����ӡ��֤���յ������Ƿ���ȷ
    }
}


