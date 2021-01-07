#include "rtc.h"

u8 time[6]={0,0,0,0,0,0};

void rtc_init()
{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//ʹ��PWR��BKP����ʱ��  
		PWR_BackupAccessCmd(ENABLE);		//ʹ�ܺ󱸼Ĵ�������
		BKP_DeInit();	                //��λ�������� 
		RCC_LSEConfig(RCC_LSE_ON);		//�����ⲿ���پ���(LSE),ʹ��������پ���
		delay_ms(100);
		if(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
		{
			RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		//����RTCʱ��(RTCCLK),ѡ��LSE��ΪRTCʱ��    
			RCC_RTCCLKCmd(ENABLE);	//ʹ��RTCʱ��  
			RTC_WaitForSynchro();		//�ȴ�RTC�Ĵ���ͬ��  
			RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
			RTC_ITConfig(RTC_IT_SEC , ENABLE);		//ʹ��RTC���ж�
			RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
			RTC_SetPrescaler(32767); //����RTCԤ��Ƶ��ֵ
			RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
		}
		else
		{
			printf("error");
		}
		
		RTC_NVIC_Config();
}


//rtc�ж����ã�������ȼ�
void RTC_NVIC_Config(void)
{	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;		//RTCȫ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ�1λ,�����ȼ�3λ
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	//��ռ���ȼ�0λ,�����ȼ�4λ
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//ʹ�ܸ�ͨ���ж�
	NVIC_Init(&NVIC_InitStructure);		//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}

//�жϷ�����
void RTC_IRQHandler(void)
{		 
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)//�����ж�
	{		
		time[0]+=1;        //������һ
		time_connect(time);
		PCout(13)=!PCout(13);//ָʾ��
		RTC_ClearITPendingBit(RTC_IT_SEC);		//�����ж�
	}		
	RTC_WaitForLastTask();
}

//ʱ�����
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




