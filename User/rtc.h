#ifndef _rtc_H
#define _rtc_H

#include "stm32f10x.h"
#include "SysTick.h"
#include "system.h"
#include "usart.h"

extern u8 time[6];			//外部变量，存放时间

void rtc_init(void);
void RTC_NVIC_Config(void);
void time_connect(u8 *time);

#endif
