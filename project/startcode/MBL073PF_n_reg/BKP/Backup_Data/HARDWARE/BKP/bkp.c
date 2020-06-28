#include "bkp.h"

/********************************************************************************************************
**函数信息 ：BKP_DATA(void)         
**功能描述 : BKP数据读写测试，判断写和读的数据是否一致
**输入参数 ：FirstBackupData
**输出参数 ：i
********************************************************************************************************/
u8 BKP_DATA(void)
{
    /* Enable PWR and BKP clock */
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    /* Enable write access to Backup domain */
    PWR->CR |= 0x100; 
    
    BKP->DR1=0x34;	
    
    if(BKP->DR1==0x34)
        return 0;
    else
        return 1;
}
