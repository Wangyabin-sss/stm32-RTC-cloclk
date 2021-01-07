#include "LED.h"

void light_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;  //ָʾ��IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(GPIOC,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	PCout(13)=0;
}

void LEDnember_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;  //��ʾ����IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(GPIOA,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_0 | GPIO_Pin_15 | GPIO_Pin_1;  //����IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(GPIOB,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;  //����������IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;	 //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(GPIOB,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	
}

//������⣬pb9���Ʒ��Ӹ�λ��pb10���Ʒ���ʮλ��pb11����Сʱ
void anjianjiance()
{
	u8 pb9,pb10,pb11;
	if(PBin(9)==1)
	{
		while(PBin(9))
		{pb9=1;}
	}
	if(PBin(10)==1)
	{
		while(PBin(10))
		{pb10=1;}
	}
	if(PBin(11)==1)
	{
		while(PBin(11))
		{pb11=1;}
	}
	
	count_anjian(&pb9,&pb10,&pb11);
	
}

void count_anjian(u8 *pb9,u8 *pb10,u8 *pb11)
{
	if(*pb9==1)
	{
		time[2]+=1;
		*pb9=0;
		if(time[2]==10)
		{
			time[2]=0;
		}
	}
	if(*pb10==1)
	{
		time[3]+=1;
		*pb10=0;
		if(time[3]==6)
		{
			time[3]=0;
		}
	}
	if(*pb11==1)
	{
		time[4]+=1;
		*pb11=0;
		if(time[4]==4&&time[5]==2)
		{
			time[4]=0;
			time[5]=0;
		}
		if(time[4]==10)
		{
			time[4]=0;
			time[5]+=1;
		}
	}
		
}





