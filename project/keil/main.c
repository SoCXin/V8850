#include "delay.h"
#include "key.h"
#include "led.h"
#include "uart.h"
#include "can.h"

CanTxMsg CAN_TX_Config ={TX_CANID,CAN_ID_STD,CAN_DATA_FRAME,8,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
CanPeliRxMsg CanPeliRxMsgStructure;

u8 user_can_mode = 0;

int main(void)    
{
	int keycnt = 0;
	delay_init(); 
	delay_ms(3000);
	LED_Init();		
	KEY_Init();
	uart_initwBaudRate(115200);
	printf("CAN (500k) demo with mask id is 0x172,0x236!\r\n");
	CANM_Init();
	//只可接收验收代码寄存器中的两个CAN_ID的帧
	CAN_Config(CAN_500K,StandardFrame_DoubleFilter,0x172,0x236,0xff,0xff);		
	
	while(1)
  {
	 if(KEY4 == 0)
	 {
		 delay_ms(30);
		 while(KEY4 == 0); 	
		keycnt++;
		if(keycnt%2)
		{
				LED2_ON();
				LED4_OFF();
				user_can_mode = 1; // r
		}
		else
		{
				LED2_OFF();
				LED4_ON();
				user_can_mode = 0; // s
		}	 	
	 }
	 
	  if(user_can_mode)
	  {
			Send_CANFrame(&CAN_TX_Config);		//发送一帧CAN数据
			printf("CAN send data OK!\r\n");	//串口打印
			delay_ms(300);
	  }
	  else
	  {  
			if(flag)																	
			{
			  flag = 0;
			  LED4_TOGGLE();
			  printf("CANID:0x%x Data:",CanPeliRxMsgStructure.ID);	//串口打印
			  for(int i = 0; i < 8; i++)															
			  {
				printf("%02x ",CanPeliRxMsgStructure.Data[i]);		//打印CAN报文内容
			  }
			  printf("\r\n");								   //换行
			}
	  } 
  }
  
   
}



