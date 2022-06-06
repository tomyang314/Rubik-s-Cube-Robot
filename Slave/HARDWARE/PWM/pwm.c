#include "pwm.h"

//TIM4 PWM²¿·Ö³õÊ¼»
//PWMÊä³ö³õÊ¼»¯
//arr:×Ô¶¯ÖØ×°ÔØÖµ        psc:Ê±ÖÓÔ¤·ÖÆµÊı


/******************************************************************************
* Ä£¿éÃèÊö
* ÏîÄ¿´úºÅ»òÃû³Æ £º  8Â·PWMÊä³ö
* ´´½¨ÈÕÆÚ       £º  2022/05/14
* ´´½¨ÈË         £º  Ö¾³Ç
* Ä£¿é¹¦ÄÜ       £º  
* ĞŞ¸ÄÈÕÆÚ       £º
* ²Î¿¼ÎÄµµ       £º  ¾«Í¨STM32F4¿âº¯Êı°æ
* ÏîÄ¿ÔËĞĞÆ½Ì¨   £º  STM32F103C8T6
* ÆäËü           £º  PWMµÄÒ»°ã²½Öè
										 ÊµÀıÒªÇó£ºTIM4À´²úÉúPWMÊä³ö,²¢Ê¹ÄÜTIM4µÄÍ¨µÀ1¡¢2¡¢3¡¢4,Öğ¸öÖØÓ³Éäµ½PB6\PB7\PB8\PB9,²úÉúPWMÀ´¿ØÖÆ¶æ»ú

											1¡¢Ê¹ÄÜ¶¨Ê±Æ÷ºÍÏà¹ØIOÊ±ÖÓ£¬µ÷ÓÃº¯Êı:RCC_APB1PeriphClockCmd();RCC_APB2PeriphClockCmd();
											2¡¢³õÊ¼»¯IOÎª¸´ÓÃ¹¦ÄÜÊä³ö£¬µ÷ÓÃº¯Êı:GPIO_Init();ÕâÀïÎÒÃÇ°ÑPB6\PB7\PB8\PB9ÓÃ×÷¶¨Ê±Æ÷µÄPWMÊä³öÒı½Å,ÒªÖØÓ³ÉäÅäÖÃ¼´GPIO_Mode_AF_PP;
											   ¸´ÓÃÍÆÍìÊä³ö£»ËùÒÔĞèÒª¿ªÆôAFIOÊ±ÖÓ¡£
												 
											3¡¢³õÊ¼»¯¶¨Ê±Æ÷£¬µ÷ÓÃº¯Êı:TIM_TimeBaseInit();
											4¡¢³õÊ¼»¯Êä³ö±È½Ï²ÎÊı£¬µ÷ÓÃº¯Êı:TIM_OCInitStructure();
											5¡¢Ê¹ÄÜÔ¤×°ÔØ¼Ä´æÆ÷£¬µ÷ÓÃº¯Êı:TIM_OC1PreloadConfig();
											6¡¢Ê¹ÄÜ¶¨Ê±Æ÷£¬µ÷ÓÃº¯Êı:TIM_Cmd();											
											7¡¢ÉèÖÃ¶æ»ú³õÊ¼½Ç¶È£¬µ÷ÓÃº¯Êı£ºTIM_SetCompare1(TIM4,1945);
															
»ù´¡ÖªÊ¶´¢±¸£º
TIM1_ETR     PA12            
TIM1_CH1     PA8            TIM2_CH1_ETR PA0            TIM3_CH1     PA6            TIM4_CH1     PB6 
TIM1_CH2     PA9            TIM2_CH2     PA1            TIM3_CH2     PA7            TIM4_CH2     PB7
TIM1_CH3     PA10           TIM2_CH3     PA2            TIM3_CH3     PB0            TIM4_CH3     PB8 
TIM1_CH4     PA11           TIM2_CH4     PA3            TIM3_CH4     PB1            TIM4_CH4     PB9  

*/

void TIM2_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;   					 				//³õÊ¼»¯TIM1ÉèÖÃARR,PSC¿ØÖÆÊä³öPWMµÄÖÜÆÚ
	TIM_OCInitTypeDef  TIM_OCInitStructure;                         //PWMÍ¨µÀÉèÖÃ
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);     			  //Ê¹ÄÜ¶¨Ê±Æ÷2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);      				//AFIO¸´ÓÃ¹¦ÄÜÊ±ÖÓÊ¹ÄÜ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  ,ENABLE);   				//GPIOAÊ¹ÄÜ
	
	
	//ÉèÖÃ¸ÃÒı½ÅÎª¸´ÓÃÊä³ö¹¦ÄÜ
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_3;	       //TIM2_CH1/CH4
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;                                     //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);                                               //³õÊ¼»¯GPIO
	
	
	//³õÊ¼»¯TIM1,ÉèÖÃTIM4µÄARRºÍPSC
	TIM_TimeBaseStruct.TIM_Period = arr;                   					 //ÉèÖÃ×Ô¶¯ÖØ×°ÔØÖÜÆÚÖµ   //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ	 
	TIM_TimeBaseStruct.TIM_Prescaler = psc;                					 //ÉèÖÃÔ¤·ÖÆµÖµ           //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ  ²»·ÖÆµ
	TIM_TimeBaseStruct.TIM_ClockDivision = 0;               				 //ÉèÖÃÊ±ÖÓ·Ö¸îTDTS = Tck_tim	
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;         //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStruct);                      //¸ù¾İÖ¸¶¨²ÎÊı³õÊ¼»¯TIMx  //¸ù¾İTIM_TimeBaseInitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»
	


	
	//³õÊ¼»¯³öÊä³ö±È½Ï²ÎÊı
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                  //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;      //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;          //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);                            //¸ù¾İTIMXµÄ²ÎÊıÉè¶¨³õÊ¼»¯ÍâÉè TIM2 ch1 ch4	
  TIM_OC4Init(TIM2,&TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);                   //Ê¹ÄÜÔ¤×°ÔØ¼Ä´æÆ÷
	TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM2, ENABLE);                                //Ê¹ÄÜTIMxÔÚARRÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷	
	
	TIM_CtrlPWMOutputs(TIM2,ENABLE);                                   //TIM1Êä³öÊ¹ÄÜ   ¸ß¼¶¶¨Ê±Æ÷¾ø¶ÔµÃ¼ÓÉÏÒòÎªÕâ¾ä»°ÎÒ¸ãÁËÒ»¸öÍíÉÏ£¬ºóÈË½äÖ®É÷Ö®
	
	TIM_Cmd(TIM2,ENABLE);                                              //Ê¹ÄÜTIM2

}

void TIM3_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;   					 				//³õÊ¼»¯TIM1ÉèÖÃARR,PSC¿ØÖÆÊä³öPWMµÄÖÜÆÚ
	TIM_OCInitTypeDef  TIM_OCInitStructure;                         //PWMÍ¨µÀÉèÖÃ
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);     			  //Ê¹ÄÜ¶¨Ê±Æ÷4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);      				//AFIO¸´ÓÃ¹¦ÄÜÊ±ÖÓÊ¹ÄÜ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB ,ENABLE);   				//GPIOA¡¢BÊ¹ÄÜ
	
	
	//ÉèÖÃ¸ÃÒı½ÅÎª¸´ÓÃÊä³ö¹¦ÄÜ
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;	       //TIM3_CH2
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;                                     //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);                                               //³õÊ¼»¯GPIO
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;	       //TIM3_CH3
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;                                     //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);                                               //³õÊ¼»¯GPIO
	
	
	//³õÊ¼»¯TIM1,ÉèÖÃTIM4µÄARRºÍPSC
	TIM_TimeBaseStruct.TIM_Period = arr;                   					 //ÉèÖÃ×Ô¶¯ÖØ×°ÔØÖÜÆÚÖµ   //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ	 
	TIM_TimeBaseStruct.TIM_Prescaler = psc;                					 //ÉèÖÃÔ¤·ÖÆµÖµ           //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ  ²»·ÖÆµ
	TIM_TimeBaseStruct.TIM_ClockDivision = 0;               				 //ÉèÖÃÊ±ÖÓ·Ö¸îTDTS = Tck_tim	
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;         //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStruct);                      //¸ù¾İÖ¸¶¨²ÎÊı³õÊ¼»¯TIMx  //¸ù¾İTIM_TimeBaseInitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»
	


	
	//³õÊ¼»¯³öÊä³ö±È½Ï²ÎÊı
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                  //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;      //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;          //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	
	//¸ù¾İTIMXµÄ²ÎÊıÉè¶¨³õÊ¼»¯ÍâÉè TIM1 ch1 ch2 ch3 ch4	
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
  TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	
	//Ê¹ÄÜÔ¤×°ÔØ¼Ä´æÆ÷
  TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM3, ENABLE);                                 //Ê¹ÄÜTIMxÔÚARRÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷	
	
	TIM_CtrlPWMOutputs(TIM3,ENABLE);//TIM1Êä³öÊ¹ÄÜ   ¸ß¼¶¶¨Ê±Æ÷¾ø¶ÔµÃ¼ÓÉÏÒòÎªÕâ¾ä»°ÎÒ¸ãÁËÒ»¸öÍíÉÏ£¬ºóÈË½äÖ®É÷Ö®
	
	TIM_Cmd(TIM3,ENABLE);     //Ê¹ÄÜTIM1

}

void TIM4_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;   					 				//³õÊ¼»¯TIM4ÉèÖÃARR,PSC¿ØÖÆÊä³öPWMµÄÖÜÆÚ
	TIM_OCInitTypeDef  TIM_OCInitStructure;                         //PWMÍ¨µÀÉèÖÃ
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);     			  //Ê¹ÄÜ¶¨Ê±Æ÷4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);      				//AFIO¸´ÓÃ¹¦ÄÜÊ±ÖÓÊ¹ÄÜ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  ,ENABLE);   				//GPIOBÊ¹ÄÜ
	
	
	//ÉèÖÃ¸ÃÒı½ÅÎª¸´ÓÃÊä³ö¹¦ÄÜ
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;	       //²½½øµç»ú5ºÅ£¬6ºÅ
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;                                   //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);                                             //³õÊ¼»¯GPIO
	
	
	//³õÊ¼»¯TIM4,ÉèÖÃTIM4µÄARRºÍPSC
	TIM_TimeBaseStruct.TIM_Period = arr;                   					 //ÉèÖÃ×Ô¶¯ÖØ×°ÔØÖÜÆÚÖµ   //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ	 
	TIM_TimeBaseStruct.TIM_Prescaler = psc;                					 //ÉèÖÃÔ¤·ÖÆµÖµ           //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ  ²»·ÖÆµ
	TIM_TimeBaseStruct.TIM_ClockDivision = 0;               				 //ÉèÖÃÊ±ÖÓ·Ö¸îTDTS = Tck_tim	
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;         //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStruct);                      //¸ù¾İÖ¸¶¨²ÎÊı³õÊ¼»¯TIMx  //¸ù¾İTIM_TimeBaseInitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»
	
	
	
	
	//Êä³ö³õÊ¼»¯º¯Êı£¬Ñ¡ÔñËÄ¸öÍ¨µÀ£¬³õÊ¼»¯PWMÊä³öÄ£Ê½¡¢±È½ÏÊä³ö¼«ĞÔ¡¢ ±È½ÏÊä³öÊ¹ÄÜ¡¢ ±È½ÏÖµCCRxµÄÖµ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                  //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;      //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_Pulse = 0;                                 //ÉèÖÃ´ı×°Èë²¶»ñ±È½Ï¼Ä´æÆ÷µÄÂö³åÖµ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;          //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	
	//¸ù¾İTIMXµÄ²ÎÊıÉè¶¨³õÊ¼»¯ÍâÉè TIM4 ch3 ch4	
	TIM_OC3Init(TIM4,&TIM_OCInitStructure);
  TIM_OC4Init(TIM4,&TIM_OCInitStructure);

	
	//Ê¹ÄÜÔ¤×°ÔØ¼Ä´æÆ÷
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM4, ENABLE); //Ê¹ÄÜTIMxÔÚARRÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷	
	
	TIM_Cmd(TIM4,ENABLE);     //Ê¹ÄÜTIM4
	
	
	//²ÎÊıÉèÖÃº¯Êı
	//×÷ÓÃ£ºÔÚËÄ¸öÍ¨µÀÖĞÑ¡ÔñÒ»¸ö£¬ÉèÖÃ±È½ÏÖµ¡£Í¨³£ÔÚ³õÊ¼»¯º¯ÊıÖĞÒÑ¾­ÉèÖÃÁË±È½ÏÖµ£¬´Ëº¯ÊıÓÃÓÚ³ı³õÊ¼»¯Ö®ÍâµÄĞŞ¸Ä
	//TIM_SetCompare1(TIM4,1850);
	//TIM_SetCompare2(TIM4,1850);
	//TIM_SetCompare3(TIM4,1850);
	//TIM_SetCompare4(TIM4,1850);
	
	

}








