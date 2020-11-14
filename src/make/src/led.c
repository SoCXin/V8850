#include "led.h"

/********************************************************************************************************
**o‘那yD??⊿ ㏒oLED_Init(void)                        
**1|?邦?豕那? ㏒oLED3?那??‘
**那?豕?2?那y ㏒o?T
**那?3?2?那y ㏒o?T
********************************************************************************************************/
void LED_Init(void)
{
    
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB, ENABLE);  //?a??GPIOA,GPIOB那㊣?車
    
    
//    GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_15;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    LED1_ON();
    LED2_OFF();
//    LED3_ON();
//    LED4_ON();
}

