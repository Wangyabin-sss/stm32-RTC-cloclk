#include "rtc.h"

u8 time[6]={0,0,0,0,0,0};

void rtc_init()
{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//使能PWR和BKP外设时钟  
		PWR_BackupAccessCmd(ENABLE);		//使能后备寄存器访问
		BKP_DeInit();	                //复位备份区域 
		RCC_LSEConfig(RCC_LSE_ON);		//设置外部低速晶振(LSE),使用外设低速晶振
		delay_ms(100);
		if(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
		{
			RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		//设置RTC时钟(RTCCLK),选择LSE作为RTC时钟    
			RCC_RTCCLKCmd(ENABLE);	//使能RTC时钟  
			RTC_WaitForSynchro();		//等待RTC寄存器同步  
			RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成
			RTC_ITConfig(RTC_IT_SEC , ENABLE);		//使能RTC秒中断
			RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成
			RTC_SetPrescaler(32767); //设置RTC预分频的值
			RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成
		}
		else
		{
			printf("error");
		}
		
		RTC_NVIC_Config();
}


//rtc中断设置，最高优先级
void RTC_NVIC_Config(void)
{	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;		//RTC全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//先占优先级1位,从优先级3位
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	//先占优先级0位,从优先级4位
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//使能该通道中断
	NVIC_Init(&NVIC_InitStructure);		//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}

//中断服务函数
void RTC_IRQHandler(void)
{		 
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)//秒钟中断
	{		
		time[0]+=1;        //秒数加一
		time_connect(time);
		PCout(13)=!PCout(13);//指示灯
		RTC_ClearITPendingBit(RTC_IT_SEC);		//清秒中断
	}		
	RTC_WaitForLastTask();
}

//时间计算
void time_connect(u8 *time)
{
	if(time[0]==10)
	{
		time[1]+=1;
		if(time[0]==10&&time[1]==6)
		{
			time[2]+=1;
			if(time[2]==10)
			{
				time[3]+=1;
				if(time[2]==10&&time[3]==6)
				{
					time[4]+=1;
					if(time[4]==10)
					{
						time[5]+=1;
						time[4]=0;
					}
					if(time[4]==4&&time[5]==2)
					{
						time[4]=0;
						time[5]=0;
					}
					time[3]=0;
				}
				time[2]=0;
			}
			time[1]=0;
		}
		time[0]=0;
	}
	
}




