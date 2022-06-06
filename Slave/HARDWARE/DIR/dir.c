#include "dir.h"
#include "delay.h"


//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//ʹ��ʱ��		    
//LED IO��ʼ��
void DIR_Init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;
 	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12;				       //PC13 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					         //�����趨������ʼ��GPIOPC13
	GPIO_SetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12);						             //PC13�����
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				       //PC13 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					         //�����趨������ʼ��GPIOPC13
	GPIO_SetBits(GPIOA,GPIO_Pin_4);						             //PC13�����
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				       //PC13 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					         //�����趨������ʼ��GPIOPC13
	GPIO_SetBits(GPIOC,GPIO_Pin_15);						             //PC13�����
}
 

/*********************************END FILE********************************************/	
