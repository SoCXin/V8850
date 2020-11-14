/******************************************************************************************
* Copyright (C), 2018, Shanghai ICWiser communication technology Co., Ltd
* 文件名:  system_MM32L073.h
* 作  者:  Eric Qiu <jmqiu@icwiser.com>
* 版  本:  V1.00
* 日  期:  2018/09/19
* 描  述:  MM32L073系列芯片初始化文件
* 备  注:  适用于MM32L073系列芯片
*          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
*******************************************************************************************/
#ifndef __SYSTEM_MM32L073_H__
#define __SYSTEM_MM32L073_H__

#include <stdint.h>
#include "MM32L0xx.h"


extern const uint32_t SystemCoreClock;
void SystemInit(void);

#endif
