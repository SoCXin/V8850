#include "can.h"
u8 flag = 0;
/********************************************************************************************************
**函数信息 ：void CANM_Init(void)
**功能描述 ：CAN初始化
**输入参数 ：None
**输出参数 ：None
**    备注 ：
********************************************************************************************************/
void CANM_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
#if 1
  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOB, ENABLE); 	
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8; //CAN RX PB8
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9; //CAN TX PB9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_4);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_4);
#else
  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE); 	
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11; //CAN RX PA11
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12; //CAN TX PA12
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_4);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_4);
#endif
}
/********************************************************************************************************
**函数信息 ：void CAN_Config(u32 CAN_Pre,CAN_Mode ID,u32 idCode1,u32 idCode2,u32 mask1,u32 mask2)
**功能描述 ：CAN配置
**输入参数 ：CAN_Pre:CAN通信速率
CAN_250K  CAN_500K
fMode:CAN通信模式
StandardFrame_SingleFilter=0:标准帧，单滤波器模式
StandardFrame_SingleFilter=1:扩展帧，单滤波器模式
ExtendedFrame_SingleFilter=2:标准帧，双滤波器模式
ExtendedFrame_DoubleFilter=3:扩展帧，双滤波器模式
idCode1：验收代码1
idCode2：验收代码2
mask1：验收代码屏蔽位1
mask2：验收代码屏蔽位2
**输出参数 ：None
**    备注 ：
********************************************************************************************************/
void CAN_Config(u32 CAN_Pre,CAN_Mode ID,u32 idCode1,u32 idCode2,u32 mask1,u32 mask2)
{
  CAN_Peli_InitTypeDef          CAN_Peli_InitStructure;
  RCC_ClocksTypeDef             RCC_Clocks;
  u32 idCodeTemp1,idMaskTemp1;
  u32 idCodeTemp2,idMaskTemp2;
  CAN_Peli_FilterInitTypeDef    CAN_Peli_FilterInitStructure;
  
  CAN_ResetMode_Cmd(CAN1,ENABLE);// 进入复位模式
  CAN_Mode_Cmd(CAN1, CAN_PELIMode);//CAN进入Peli模式
  
  RCC_GetClocksFreq(&RCC_Clocks);
  
  CAN_Peli_StructInit(&CAN_Peli_InitStructure);
  
  CAN_AutoCfg_BaudParam( &CAN_Peli_InitStructure, RCC_Clocks.PCLK1_Frequency, CAN_Pre);
  
  CAN_Peli_InitStructure.SAM = RESET;//采样点
  CAN_Peli_InitStructure.STM = DISABLE;//DISABLE;//自测模式
  CAN_Peli_InitStructure.LOM = DISABLE;//只听模式
  //	CAN_Peli_InitStructure.EWLR = 0x96;
  CAN_Peli_Init(&CAN_Peli_InitStructure);
  
  switch(ID)
  {
  case StandardFrame_SingleFilter:
    idCodeTemp1 = idCode1<<(3 + 18);
    idMaskTemp1 = mask1<<(3 + 18);
    CAN_Peli_FilterInitStructure.AFM = CAN_FilterMode_Singal;
    CAN_Peli_FilterInitStructure.CAN_FilterId0 = (idCodeTemp1>>24)&0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterId1 = (idCodeTemp1>>16)&0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterId2 = (idCodeTemp1>>8)&0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterId3 = (idCodeTemp1>>0)&0xff;
    
    CAN_Peli_FilterInitStructure.CAN_FilterMaskId0 = (idMaskTemp1>>24)&0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterMaskId1 = ((idMaskTemp1>>16)&0xff)|0x1f;
    CAN_Peli_FilterInitStructure.CAN_FilterMaskId2 = ((idMaskTemp1>>8)&0xff)|0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterMaskId3 = ((idMaskTemp1>>0)&0xff)|0xff;
    break;
  case ExtendedFrame_SingleFilter:
    idCodeTemp1 = idCode1<<3;
    idMaskTemp1 = mask1<<3;
    CAN_Peli_FilterInitStructure.AFM = CAN_FilterMode_Singal;
    CAN_Peli_FilterInitStructure.CAN_FilterId0 = (idCodeTemp1>>24)&0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterId1 = (idCodeTemp1>>16)&0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterId2 = (idCodeTemp1>>8)&0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterId3 = idCodeTemp1&0xff;
    
    CAN_Peli_FilterInitStructure.CAN_FilterMaskId0 = (idMaskTemp1>>24)&0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterMaskId1 = ((idMaskTemp1>>16)&0xff);
    CAN_Peli_FilterInitStructure.CAN_FilterMaskId2 = ((idMaskTemp1>>8)&0xff);
    CAN_Peli_FilterInitStructure.CAN_FilterMaskId3 = ((idMaskTemp1>>0)&0xff);
    break;        
  case StandardFrame_DoubleFilter:
    idCodeTemp1 = idCode1<<(3 + 18);
    idMaskTemp1 = mask1<<(3 + 18);
    idCodeTemp2 = idCode2<<(3 + 18);
    idMaskTemp2 = mask2<<(3 + 18);
    CAN_Peli_FilterInitStructure.AFM = CAN_FilterMode_Double;
    CAN_Peli_FilterInitStructure.CAN_FilterId0 = (idCodeTemp1>>24)&0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterId1 = (idCodeTemp1>>16)&0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterId2 = (idCodeTemp2>>24)&0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterId3 = (idCodeTemp2>>16)&0xff;
    
    CAN_Peli_FilterInitStructure.CAN_FilterMaskId0 = (idMaskTemp1>>24)&0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterMaskId1 = ((idMaskTemp1>>16)&0xff)|0x1f;
    CAN_Peli_FilterInitStructure.CAN_FilterMaskId2 = (idMaskTemp2>>24)&0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterMaskId3 = ((idMaskTemp2>>16)&0xff)|0x1f;
    break; 
  case ExtendedFrame_DoubleFilter:
    idCodeTemp1 = idCode1<<(3);
    idMaskTemp1 = mask1<<(3);
    idCodeTemp2 = idCode2<<(3);
    idMaskTemp2 = mask2<<(3);
    CAN_Peli_FilterInitStructure.AFM = CAN_FilterMode_Double;
    CAN_Peli_FilterInitStructure.CAN_FilterId0 = (idCodeTemp1>>24)&0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterId1 = (idCodeTemp1>>16)&0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterId2 = (idCodeTemp2>>24)&0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterId3 = (idCodeTemp2>>16)&0xff;
    
    CAN_Peli_FilterInitStructure.CAN_FilterMaskId0 = (idMaskTemp1>>24)&0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterMaskId1 = (idMaskTemp1>>16)&0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterMaskId2 = (idMaskTemp2>>24)&0xff;
    CAN_Peli_FilterInitStructure.CAN_FilterMaskId3 = (idMaskTemp2>>16)&0xff;
    break; 
  default:
    break;
  }
  CAN_Peli_FilterInit(&CAN_Peli_FilterInitStructure);
  CAN_ResetMode_Cmd(CAN1,DISABLE);//退出复位模式,进入工作模式
}

/********************************************************************************************************
**函数信息 ：void Send_CANFrame(CanTxMsg* TxMessage)
**功能描述 ：CAN发送报文
**输入参数 ：CanTxMsg* TxMessage
**输出参数 ：None
**    备注 ：
********************************************************************************************************/
void Send_CANFrame(CanTxMsg* TxMessage)
{
  CanPeliTxMsg     CanPeliTxMsgStructure;
  uint32_t ID=0;
  u32 i;
  
  if(TxMessage->CANIDtype)  //扩展帧
  {
    ID=TxMessage->CANID <<3;
    
    CanPeliTxMsgStructure.FF   = 0x01; 
    CanPeliTxMsgStructure.IDLL = (ID >> 0)&0xff;
    CanPeliTxMsgStructure.IDLH = (ID >> 8)&0xff;
    CanPeliTxMsgStructure.IDHL = (ID >> 16)&0xff;
    CanPeliTxMsgStructure.IDHH = (ID >> 24)&0xff;
  }
  else											//标准帧
  {
    ID=TxMessage->CANID << 21;
    
    CanPeliTxMsgStructure.FF   = 0x00;
    CanPeliTxMsgStructure.IDHL = (ID >>16)&0xff;
    CanPeliTxMsgStructure.IDHH = (ID >>24)&0xff;
  }
  
  CanPeliTxMsgStructure.DLC  = TxMessage->DLC;
  CanPeliTxMsgStructure.RTR  = TxMessage->RTR;
  
  for(i = 0;i < 8; i ++ )
  {
    CanPeliTxMsgStructure.Data[i] = *(TxMessage->Data + i);
  }
  
  CAN_Peli_Transmit(&CanPeliTxMsgStructure);
}
/********************************************************************************************************
**函数信息 ：void CAN_IRQHandler(void)
**功能描述 ：CAN接收中断服务函数
**输入参数 ：None
**输出参数 ：None
**    备注 ：
********************************************************************************************************/
void CAN_IRQHandler(void)
{
  u32 CAN_IR_STA;
  
  CAN_IR_STA = CAN1_PELI->IR;
  if(CAN_IR_STA & CAN_IT_RI)
  {
    CAN_Peli_Receive(&CanPeliRxMsgStructure);//接收成功处理报文
    flag = 1;
  }
  if(CAN_IR_STA & CAN_IT_BEI)    //出错
  {
  }	
  if(CAN_IR_STA & CAN_IT_DOI  )  //接收缓冲器满
  {
    CAN1_PELI->CMR  |= 0x08;
    CAN1_PELI->CMR  |= 0x04;
  }
  if(CAN_IR_STA & CAN_IT_ALI  )  // 仲裁丢失
  {		
  }							
}
