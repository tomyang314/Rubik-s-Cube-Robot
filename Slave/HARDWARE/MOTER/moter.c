#include "moter.h"
#include "pwm.h"
#include "dir.h"
#include "delay.h"


void Moter_Init(u16 arr,u16 psc)
{
	delay_init();	    	 //延时函数初始化	  
	DIR_Init();		  	 
	TIM2_PWM_Init(599,99);
  TIM3_PWM_Init(599,99); 	 
	TIM4_PWM_Init(599,99);   //PWM频率=72000000/（599+1）/（99+1）=1200Hz

}

void front(u16 time,u8 mode)
{
	DIR1 = mode;
	TIM_SetCompare1(TIM2,300);			
	delay_ms(time);
	TIM_SetCompare1(TIM2,0);
}

void back(u16 time,u8 mode)
{
	DIR2 = mode;
	TIM_SetCompare4(TIM2,300);			
	delay_ms(time);
	TIM_SetCompare4(TIM2,0);
}

void up(u16 time,u8 mode)
{
	DIR3 = mode;
	TIM_SetCompare2(TIM3,300);			
	delay_ms(time);
	TIM_SetCompare2(TIM3,0);
}

void down(u16 time,u8 mode)
{
	DIR4 = mode;
	TIM_SetCompare3(TIM3,300);			
	delay_ms(time);
	TIM_SetCompare3(TIM3,0);
}

void left(u16 time,u8 mode)
{
	DIR5 = mode;
	TIM_SetCompare3(TIM4,300);			
	delay_ms(time);
	TIM_SetCompare3(TIM4,0);
}
void right(u16 time,u8 mode)
{
	DIR6 = mode;
	TIM_SetCompare4(TIM4,300);			
	delay_ms(time);
	TIM_SetCompare4(TIM4,0);
}

