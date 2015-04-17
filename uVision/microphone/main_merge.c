#include <stdint.h>
#include "PLL.h"
#include "SysTickInts.h"
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "ADCT0ATrigger.h"
#include "switch.h"
#include "DAC.h"

#define PF2     (*((volatile uint32_t *)0x40025010))	

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode


int main(void){
	
	uint8_t kvalue;
	uint8_t hundredvalue;	
	uint8_t tenvalue;
	uint8_t unitvalue;
	uint8_t kdigit;
	uint8_t hundreddigit;
	uint8_t tendigit;
	uint8_t unitdigit;
	uint32_t adc_normal;
	uint16_t differ;
	uint16_t temp;
	uint16_t tempkvalue;
	uint16_t temphundredvalue;
	uint16_t temptenvalue;
	uint16_t tempunitvalue;
	uint8_t tempkdigit;
	uint8_t temphundreddigit;
	uint8_t temptendigit;
	uint8_t tempunitdigit;
	uint8_t xvalue = 0;
	uint8_t yvalue1 = 0;
	
	PLL_Init();                 // bus clock at 80 MHz	
	ST7735_InitR(INITR_REDTAB);	//initialize the screen
	ADC0_InitTimer0ATriggerSeq3PD3(5000000);	//*****ADC channel 4, 10Hz sampling
	DAC_Init(0);                // initialize with command: Vout = Vref
	PF2 = 0x04;

	//add from nick
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL |SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	Time_Init();
	//UART_Init();
	XBEE_Init();
	XBEE_configure(0x69, 0x79);
	//add from nick

	EnableInterrupts();

	while(1){
		if(ADCflag){
			ADCflag=0;
			kvalue =  ADCvalue/1000;
			hundredvalue = (ADCvalue - kvalue*1000)/100;	
			tenvalue = (ADCvalue - kvalue*1000 - hundredvalue*100)/10;
			unitvalue = ADCvalue - kvalue*1000 - hundredvalue*100 - tenvalue*10;

			//add from nick
			//UART_OutString("Instring: ");
			//UART_InString(buf, BUFFER_SIZE);
			//UART_NewLine(); 
			XBEE_OutString(ADCvalue);
			//add from nick

			kdigit = '0' +  kvalue;
			hundreddigit = '0' +  hundredvalue;
			tendigit = '0' + tenvalue;
			unitdigit = '0' + unitvalue;
			
			ST7735_DrawChar(10, 10, kdigit, ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(17, 10, hundreddigit, ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(24, 10, tendigit, ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(34, 10, unitdigit, ST7735_Color565(255, 128, 128), 0, 1);
			
			adc_normal = ADCvalue*1000;
			differ = adc_normal/1638;
			temp = 4000 - differ;
			tempkvalue = temp/1000;
			temphundredvalue = (temp - tempkvalue*1000)/100;
			temptenvalue = (temp - tempkvalue*1000 - temphundredvalue*100)/10;
			tempunitvalue = temp - tempkvalue*1000 - temphundredvalue*100 - temptenvalue*10;
		
			tempkdigit = '0' + tempkvalue;
			temphundreddigit = '0' + temphundredvalue;
			temptendigit = '0' + temptenvalue;
			tempunitdigit = '0' + tempunitvalue;
			
			ST7735_DrawChar(10, 30, tempkdigit, ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(17, 30, temphundreddigit, ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(24, 30, '.', ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(31, 30, temptendigit, ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(38, 30, tempunitdigit, ST7735_Color565(255, 128, 128), 0, 1);
			ST7735_DrawChar(45, 30, 'C', ST7735_Color565(255, 128, 128), 0, 1);
			
			
			if(xvalue < 127){
				yvalue1 = 150-(temp/100);
				//yvalue2 = 150-Desirespeed;
				ST7735_FillRect(xvalue, 90, 1, 70, ST7735_Color565(0, 0, 0));					
				ST7735_DrawPixel(xvalue, yvalue1, ST7735_Color565(255, 128, 128));
				//ST7735_DrawPixel(xvalue, yvalue2, ST7735_Color565(255, 255, 255));
				xvalue++;
			}else{
				xvalue = 0;
				yvalue1 = 150-(temp/100);
				//yvalue2 = 150-Desirespeed;
				ST7735_FillRect(xvalue, 90, 1, 70, ST7735_Color565(0, 0, 0));					
				ST7735_DrawPixel(xvalue, yvalue1, ST7735_Color565(255, 128, 128));
				//ST7735_DrawPixel(xvalue, yvalue2, ST7735_Color565(255, 255, 255));					
			}
		}
	}
}



