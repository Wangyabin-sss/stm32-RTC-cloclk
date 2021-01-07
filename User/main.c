#include "stm32f10x.h" 
#include "SysTick.h"
#include "usart.h"
#include "system.h"
#include "LED.h"
#include "rtc.h"
/*数码管为共阳极数码管*/
//引脚初始化在LED.c文件
//数码管阳极引脚
#define led1 PBout(6)
#define led2 PBout(5)
#define led3 PBout(7)
#define led4 PBout(0)
#define led5 PBout(15)
#define led6 PBout(1)
//数码管显示引脚
#define a PAout(1)
#define b PAout(2)
#define c PAout(3)
#define d PAout(4)
#define e PAout(5)
#define f PAout(6)
#define g PAout(7)



void ledlight(int m)
{
	switch(m)
	{
		case 0:
			led1=1;led2=0;led3=0;led4=0;led5=0;led6=0;
		break;
		case 1:
			led1=0;led2=1;led3=0;led4=0;led5=0;led6=0;
		break;
		case 2:
			led1=0;led2=0;led3=1;led4=0;led5=0;led6=0;
		break;
		case 3:
			led1=0;led2=0;led3=0;led4=1;led5=0;led6=0;
		break;
		case 4:
			led1=0;led2=0;led3=0;led4=0;led5=1;led6=0;
		break;
		case 5:
			led1=0;led2=0;led3=0;led4=0;led5=0;led6=1;
		break;
			
	}
}

void nember(int n)
{
	switch(n)
	{
		case 0:
			a=0;b=0;c=0;d=0;e=0;f=0;g=1;
		break;
		case 1:
			a=1;b=0;c=0;d=1;e=1;f=1;g=1;
		break;
		case 2:
			a=0;b=0;c=1;d=0;e=0;f=1;g=0;
		break;
		case 3:
			a=0;b=0;c=0;d=0;e=1;f=1;g=0;
		break;
		case 4:
			a=1;b=0;c=0;d=1;e=1;f=0;g=0;
		break;
		case 5:
			a=0;b=1;c=0;d=0;e=1;f=0;g=0;
		break;
		case 6:
			a=0;b=1;c=0;d=0;e=0;f=0;g=0;
		break;
		case 7:
			a=0;b=0;c=0;d=1;e=1;f=1;g=1;
		break;
		case 8:
			a=0;b=0;c=0;d=0;e=0;f=0;g=0;
		break;
		case 9:
			a=0;b=0;c=0;d=0;e=1;f=0;g=0;
		break;
		default:
			a=1;b=1;c=1;d=1;e=1;f=1;g=1;
		break;
	}
}



int main()
{
	int i;
	SystemInit();
	SysTick_Init(72);
	USART1_Init(115200);
	delay_ms(10);
	light_init();
	delay_ms(5);
  LEDnember_init();
	delay_ms(10);
	rtc_init();
	delay_ms(10);


  while(1)
	{
//		PCout(13)=0;
		for(i=0;i<6;i++)
		{
			ledlight(i);
			nember(time[i]);
			delay_ms(3);
		}
		
		anjianjiance();    //按键检测
		

	}
}


