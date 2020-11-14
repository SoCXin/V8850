#define PRIORITY_USART1         0x00
#define PRIORITY_CAN            0x01
#define PRIORITY_EXTI           0x02
#define PRIORITY_TIM2           0x03

#define GW_ADDRESS     				 0x00

#define LED_G_OFF				GPIO_ResetBits(GPIOB, GPIO_Pin_9);
#define LED_G_ON		  	GPIO_SetBits(GPIOB, GPIO_Pin_9);
#define LED_G_BLINK			GPIO_WriteBit(GPIOB, GPIO_Pin_9, (BitAction)((1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_9))));

#define LED_R_OFF				GPIO_ResetBits(GPIOB, GPIO_Pin_8);
#define LED_R_ON		  	GPIO_SetBits(GPIOB, GPIO_Pin_8);
#define LED_R_BLINK			GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)((1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_8))));

void versionSend(void);

