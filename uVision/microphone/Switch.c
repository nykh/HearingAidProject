
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
extern uint8_t play;
extern uint8_t i,j,k;
extern uint32_t counter1; 	//the counter to count different frequency
extern uint32_t counter2;
extern uint8_t random;

uint8_t unitvalue, pointvalue;
uint8_t unitdigit, pointdigit;

void Switch_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x00000002; 	//(a)activate clock for Port B
	GPIO_PORTB_DIR_R &= ~0x4E;    		//(b)make PB1-3 and 6 in
	GPIO_PORTB_AFSEL_R &= ~0x4E;			//(c)disable alternative
	GPIO_PORTB_AMSEL_R &= ~0x4E;			//diable analog in PB1-3 and 6
	GPIO_PORTB_DEN_R |= 0x4E;					//enable digital I/O in PB1-3 and 6
	GPIO_PORTB_PCTL_R &= ~0x0F00FFF0;	//configure PB1-3 and 6 as GPIO
	GPIO_PORTB_PUR_R |= 0x4E;					//weak pull-up on PB1-3 and 6
	GPIO_PORTB_IS_R &= ~0x4E;					//edge mode
	GPIO_PORTB_IBE_R &= ~0x4E;				//NOT both edge mode
	GPIO_PORTB_IEV_R &= ~0x4E;				//falling edge because we use pull-up
	GPIO_PORTB_ICR_R = 0x4E;					//acknowledge af first
	GPIO_PORTB_IM_R |= 0x4E;					//set IME to arm interrupt
	NVIC_PRI0_R = (NVIC_PRI0_R &= 0xFFFF1FFF)|0x00002000;//set priority 1,Should higher than systick(Priority 2)
	NVIC_EN0_R = 0x00000002;					//enable interrupt 1 which is portB
}



void GPIOPortB_Handler(void){
	//****the switch handler**** PB1: button1, play/pause
	                           //PB2: button2, rewind	  
	                           //PB3: button3, change speed
														 //PB6: button4, change random model
  	
	if(GPIO_PORTB_RIS_R&0x02){//****button1 pressed
		  GPIO_PORTB_ICR_R = 0x02;// acknowledge
		  play^=1; /*stop or play*/
			if(play==1){
				ST7735_DrawChar(4, 30, 'p', ST7735_Color565(255, 128, 128), 0, 1);
				ST7735_DrawChar(10, 30, 'l', ST7735_Color565(255, 128, 128), 0, 1);	
				ST7735_DrawChar(16, 30, 'a', ST7735_Color565(255, 128, 128), 0, 1);
				ST7735_DrawChar(22, 30, 'y', ST7735_Color565(255, 128, 128), 0, 1);
				ST7735_DrawChar(28, 30, ' ', ST7735_Color565(255, 128, 128), 0, 1);				
			}else{
				ST7735_DrawChar(4, 30, 'p', ST7735_Color565(255, 128, 128), 0, 1);
				ST7735_DrawChar(10, 30, 'a', ST7735_Color565(255, 128, 128), 0, 1);	
				ST7735_DrawChar(16, 30, 'u', ST7735_Color565(255, 128, 128), 0, 1);
				ST7735_DrawChar(22, 30, 's', ST7735_Color565(255, 128, 128), 0, 1);
				ST7735_DrawChar(28, 30, 'e', ST7735_Color565(255, 128, 128), 0, 1);			
			}
	}
  if(GPIO_PORTB_RIS_R&0x04){//***button2 pressed, rewind
	    GPIO_PORTB_ICR_R = 0x04;// acknowledge
	    //if(play) play=0; /* stop music first if it is playing */
			ST7735_DrawChar(4, 30, 'p', ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(10, 30, 'l', ST7735_Color565(255, 128, 128), 0, 1);	
			ST7735_DrawChar(16, 30, 'a', ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(22, 30, 'y', ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(28, 30, ' ', ST7735_Color565(255, 128, 128), 0, 1);		
			play=1;
	    i=0;/* set the note index to 0, the beginning of the song*/
	    j=0;
	    counter1=0;/*clear counters */
	    counter2=0;
	}

  if(GPIO_PORTB_RIS_R&0x08){//***button3 pressed, change sth, undefined
      GPIO_PORTB_ICR_R = 0x08;// acknowledge
			if(k>=15){
				k = 5;
			}else{
				k++;
			}
			unitvalue = k/10;
			pointvalue = k-unitvalue*10;
			unitdigit = '0' + unitvalue;
			pointdigit = '0' + pointvalue;	
			ST7735_DrawChar(58, 10, unitdigit, ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(70, 10, pointdigit, ST7735_Color565(255, 128, 128), 0, 1);		
  }
  if(GPIO_PORTB_RIS_R&0x40){//***button4 and PB6 pressed, change sth, undefined
		GPIO_PORTB_ICR_R = 0x40;// acknowledge	PB6
		random ^= 1;
		if(random==1){
			ST7735_DrawChar(4, 70, 'R', ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(10, 70, 'a', ST7735_Color565(255, 128, 128), 0, 1);		
			ST7735_DrawChar(16, 70, 'n', ST7735_Color565(255, 128, 128), 0, 1);	
			ST7735_DrawChar(22, 70, 'd', ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(28, 70, 'o', ST7735_Color565(255, 128, 128), 0, 1);	
			ST7735_DrawChar(34, 70, 'm', ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(40, 70, '!', ST7735_Color565(255, 128, 128), 0, 1);	
			ST7735_DrawChar(46, 70, '!', ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(52, 70, '!', ST7735_Color565(255, 128, 128), 0, 1);	
		}else{//Doremi
			ST7735_DrawChar(4, 70, 'D', ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(10, 70, 'o', ST7735_Color565(255, 128, 128), 0, 1);		
			ST7735_DrawChar(16, 70, 'r', ST7735_Color565(255, 128, 128), 0, 1);	
			ST7735_DrawChar(22, 70, 'e', ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(28, 70, 'm', ST7735_Color565(255, 128, 128), 0, 1);	
			ST7735_DrawChar(34, 70, 'i', ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(40, 70, '~', ST7735_Color565(255, 128, 128), 0, 1);	
			ST7735_DrawChar(46, 70, '~', ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(52, 70, '~', ST7735_Color565(255, 128, 128), 0, 1);	
		}
	}
}


