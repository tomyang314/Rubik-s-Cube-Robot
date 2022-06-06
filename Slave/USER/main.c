#include "sys.h"
#include "pwm.h"
#include "delay.h"
#include "esp8266.h"
#include "usart3.h"
#include "oled.h"
#include "moter.h"
#include <string.h>


int main(void)
{	
	delay_init();	    	 			//ÑÓÊ±º¯Êı³õÊ¼»¯	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 			//ÉèÖÃNVICÖĞ¶Ï·Ö×é2:2Î»ÇÀÕ¼ÓÅÏÈ¼¶£¬2Î»ÏìÓ¦ÓÅÏÈ¼¶
	usart3_init(115200);	 				//´®¿Ú³õÊ¼»¯Îª115200
	OLED_Init();
	OLED_ColorTurn(0);//0Õı³£ÏÔÊ¾£¬1 ·´É«ÏÔÊ¾
  OLED_DisplayTurn(0);//0Õı³£ÏÔÊ¾ 1 ÆÁÄ»·­×ªÏÔÊ¾¯	
  Moter_Init(599, 99);
	 
	esp8266_start_trans();							//esp8266½øĞĞ³õÊ¼»¯
	esp8266_send_data("Success!",50);
	OLED_ShowString(0, 16, "hello world!", 16, 1);
	OLED_Refresh();		//¸üĞÂÏÔÊ¾µ½OLED 
	delay_ms(1000);
	while(1)
	{	
		#if 1
		if(USART3_RX_STA&0X8000)//½ÓÊÕµ½ÆÚ´ıµÄÓ¦´ğ½á¹û
			{
				u8 i;
				for(i=0;i<(strlen((const char*)USART3_RX_BUF))/2;i++){
					if(USART3_RX_BUF[i*2] == 'F' && USART3_RX_BUF[i*2+1] == ' '){
						front(667,1);
					}else if(USART3_RX_BUF[i*2] == 'F' && USART3_RX_BUF[i*2+1] == '\''){
						front(667,0);
					}else if(USART3_RX_BUF[i*2] == 'F' && USART3_RX_BUF[i*2+1] == '2'){
						front(1333,0);
						
					}else if(USART3_RX_BUF[i*2] == 'B' && USART3_RX_BUF[i*2+1] == ' '){
						back(667,1);
					}else if(USART3_RX_BUF[i*2] == 'B' && USART3_RX_BUF[i*2+1] == '\''){
						back(667,0);
					}else if(USART3_RX_BUF[i*2] == 'B' && USART3_RX_BUF[i*2+1] == '2'){
						back(1333,0);
						
					}else if(USART3_RX_BUF[i*2] == 'U' && USART3_RX_BUF[i*2+1] == ' '){
						up(667,1);
					}else if(USART3_RX_BUF[i*2] == 'U' && USART3_RX_BUF[i*2+1] == '\''){
						up(667,0);
					}else if(USART3_RX_BUF[i*2] == 'U' && USART3_RX_BUF[i*2+1] == '2'){
						up(1333,0);
						
					}else if(USART3_RX_BUF[i*2] == 'D' && USART3_RX_BUF[i*2+1] == ' '){
						down(667,1);
					}else if(USART3_RX_BUF[i*2] == 'D' && USART3_RX_BUF[i*2+1] == '\''){
						down(667,0);
					}else if(USART3_RX_BUF[i*2] == 'D' && USART3_RX_BUF[i*2+1] == '2'){
						down(1333,0);
						
					}else if(USART3_RX_BUF[i*2] == 'L' && USART3_RX_BUF[i*2+1] == ' '){
						left(667,1);
					}else if(USART3_RX_BUF[i*2] == 'L' && USART3_RX_BUF[i*2+1] == '\''){
						left(667,0);
					}else if(USART3_RX_BUF[i*2] == 'L' && USART3_RX_BUF[i*2+1] == '2'){
						left(1333,0);
						
					}else if(USART3_RX_BUF[i*2] == 'R' && USART3_RX_BUF[i*2+1] == ' '){
						right(667,1);
					}else if(USART3_RX_BUF[i*2] == 'R' && USART3_RX_BUF[i*2+1] == '\''){
						right(667,0);
					}else if(USART3_RX_BUF[i*2] == 'R' && USART3_RX_BUF[i*2+1] == '2'){
						right(1333,0);
					}
				}
				OLED_Clear();
				OLED_ShowString(0, 16, "Game Over!", 16, 1);
				OLED_Refresh();		//¸üĞÂÏÔÊ¾µ½OLED 
				
				esp8266_send_data("End...",50);
				esp8266_quit_trans();
				
				USART3_RX_STA=0;
			} 
		delay_ms(10);
			
		#endif
	}		 
}

/*
		#if 0
		if(USART3_RX_STA&0X8000)//½ÓÊÕµ½ÆÚ´ıµÄÓ¦´ğ½á¹û
			{
				if(esp8266_check_cmd("end")){
					esp8266_send_data("End...",50);
					esp8266_quit_trans();
				}else if(esp8266_check_cmd("1")){
					DIR1 = 1;
					TIM_SetCompare1(TIM2,300);			
					delay_ms(667);
					TIM_SetCompare1(TIM2,0);
					delay_ms(500);
					DIR1 = 0;
					TIM_SetCompare1(TIM2,300);
					delay_ms(667);
					TIM_SetCompare1(TIM2,0);
					delay_ms(500);
				}else if(esp8266_check_cmd("2")){
					DIR2 = 1;
					TIM_SetCompare4(TIM2,300);			
					delay_ms(667);
					TIM_SetCompare4(TIM2,0);
					delay_ms(500);
					DIR2 = 0;
					TIM_SetCompare4(TIM2,300);
					delay_ms(667);
					TIM_SetCompare4(TIM2,0);
					delay_ms(500);
				}else if(esp8266_check_cmd("3")){
					DIR3 = 1;
					TIM_SetCompare2(TIM3,300);			
					delay_ms(667);
					TIM_SetCompare2(TIM3,0);
					delay_ms(500);
					DIR3 = 0;
					TIM_SetCompare2(TIM3,300);
					delay_ms(667);
					TIM_SetCompare2(TIM3,0);
					delay_ms(500);
				}else if(esp8266_check_cmd("4")){
					DIR4 = 1;
					TIM_SetCompare3(TIM3,300);			
					delay_ms(667);
					TIM_SetCompare3(TIM3,0);
					delay_ms(500);
					DIR4 = 0;
					TIM_SetCompare3(TIM3,300);
					delay_ms(667);
					TIM_SetCompare3(TIM3,0);
					delay_ms(500);
				}else if(esp8266_check_cmd("5")){
					DIR5 = 1;
					TIM_SetCompare3(TIM4,300);			
					delay_ms(667);
					TIM_SetCompare3(TIM4,0);
					delay_ms(500);
					DIR5 = 0;
					TIM_SetCompare3(TIM4,300);
					delay_ms(667);
					TIM_SetCompare3(TIM4,0);
					delay_ms(500);
				}else if(esp8266_check_cmd("6")){
					DIR6 = 1;
					TIM_SetCompare4(TIM4,300);			
					delay_ms(667);
					TIM_SetCompare4(TIM4,0);
					delay_ms(500);
					DIR6 = 0;
					TIM_SetCompare4(TIM4,300);
					delay_ms(667);
					TIM_SetCompare4(TIM4,0);
					delay_ms(500);
				}
				esp8266_send_data(USART3_RX_BUF,50);
				USART3_RX_STA=0;
			} 
		delay_ms(10);
		
		#endif
	*/	












