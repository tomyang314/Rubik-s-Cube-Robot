#ifndef __LED_H
#define __LED_H	 

#include "sys.h"


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
#define DIR1 PCout(15)	// PC13
#define DIR2 PAout(4)	// PC13
#define DIR3 PBout(1)	// PC13
#define DIR4 PBout(12)	// PC13
#define DIR5 PBout(5)	// PC13
#define DIR6 PBout(4)	// PC13

void DIR_Init(void);//��ʼ��

#endif
