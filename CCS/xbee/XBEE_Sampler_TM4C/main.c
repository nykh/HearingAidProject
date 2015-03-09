// main.c
// This program implements the XBee transmitter end

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "Time.h"
#include "XBEE.h"
#include "debug.h"

#include "ADCT0ATrigger.h"
#if screen
#include "ST7735.h"
#endif

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

#define NICK_STYLE   3
#define WEICE_STYLE  4
#define FRAME_STYLE  WEICE_STYLE

#if FRAME_STYLE == NICK_STYLE

typedef union frame_u {
	struct {
		char upper_four_bits;
		char odd_byte;
		char even_byte;
	} name;

	char array[3];
} frame;

typedef struct tuple_s {
	uint16_t odd;
	uint16_t even;
} tuple;

frame encode_frame(const uint16_t *odd, const uint16_t *even) {
	// magic: the TM4C architecture is Little endian and byte addressable
	// this allows to take the bytes of the sample without incurring shift
	register uint8_t *odd_seg = (uint8_t *) odd;
	register uint8_t *even_seg = (uint8_t *) even;

	frame f;
	f.name.odd_byte = *odd_seg;
	f.name.even_byte = *even_seg;
	f.name.upper_four_bits = (odd_seg[1] << 4) | even_seg[1];

	return f;
}

tuple decode_frame(frame f) {
	uint16_t upper_four_bits = f.name.upper_four_bits;
	tuple t;
	register uint8_t *odd_seg = (uint8_t *) &t.odd;
	register uint8_t *even_seg = (uint8_t *) &t.even;

	*odd_seg = f.name.odd_byte;
	*even_seg = f.name.even_byte;
	odd_seg[1] = upper_four_bits >> 4;
	even_seg[1] = upper_four_bits & 0xF;

	return t;
}

#else

typedef char *frame;

typedef struct tuple_s {
	uint16_t odd;
	uint16_t even;
} tuple;

// Theoretically this code would work for both little and big endian

void encode_frame(uint16_t odd, uint16_t even, frame f) {
	((uint16_t *) f)[0] = odd;
	((uint16_t *) f)[1] = even;
}

tuple decode_frame(char *f) {
	tuple t;
	t.odd = ((uint16_t *) f)[0];
	t.even = ((uint16_t *) f)[1];

	return t;
}

#endif

int main(void){

#if screen
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
#endif

	uint16_t first_Sample, second_Sample;

	// 50 MHz
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL
			     | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	Time_Init();
	_____debug_Init();
	XBEE_Init();

#if screen
	ST7735_InitR(INITR_REDTAB);	//initialize the screen
#endif

	ADC0_InitTimer0ATriggerSeq3PD3(14000);  //*****ADC channel 4, 1 kHz sampling
	_____debug_heartbeat(); // on

	EnableInterrupts();



	while(1){
#if FRAME_STYLE == NICK_STYLE
		frame f;
		ADC_Get(&first_Sample);
		ADC_Get(&second_Sample);

		f = encode_frame(&first_Sample, &second_Sample);
		XBEE_OutString(f.array);
#else
		uint16_t sample;

		ADC_Get(&sample);
		XBEE_OutChar((sample >> 4) & 0xFF);
#endif


#if screen
		if(ADCflag){

			kvalue =  ADCvalue/1000;
			hundredvalue = (ADCvalue - kvalue*1000)/100;
			tenvalue = (ADCvalue - kvalue*1000 - hundredvalue*100)/10;
			unitvalue = ADCvalue - kvalue*1000 - hundredvalue*100 - tenvalue*10;

			//add from nick

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
#endif
	}
}
