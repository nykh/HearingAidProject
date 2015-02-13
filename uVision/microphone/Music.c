#include <stdint.h>
#include <math.h>
#include "PLL.h"
#include "SysTickInts.h"
#include "Music.h"
#include "DAC.h"
#include "tm4c123gh6pm.h"

#define PF2     (*((volatile uint32_t *)0x40025010))	
	
uint8_t play=0;////flag to indicate if we want to play a song or not
uint8_t i,j=0;
uint8_t k = 10;
uint8_t random = 0;
uint32_t counter1 = 0;	//the counter to count different frequency
uint32_t counter2 = 0;
uint32_t desirevalue;

uint8_t randomindex = 0;;

typedef struct Note{
	uint16_t freq; 
	uint8_t duration;/* I change duration into a variable , not array, if want to change tempo, we can do x*duration */
}Note;



	
Note Doremi[64] ={{262,3},{294,1},{330,3},{262,1},{330,2},{262,2},{330,4},  /* the complete Doremi song */
{294,3},{330,1},{349,1},{349,1},{330,1},{294,1},{349,8},
{330,3},{349,1},{392,3},{330,1},{392,2},{330,2},{392,4},
{349,3},{392,1},{440,1},{440,1},{392,1},{349,1},{440,8},
{392,3},{262,1},{294,1},{330,1},{349,1},{392,1},{440,8},
{440,3},{294,1},{330,1},{349,1},{392,1},{440,1},{494,8},
{494,3},{330,1},{349,1},{392,1},{440,1},{494,1},{523,7},
{494,1},{440,1},{440,2},{349,2},{494,2},{392,2},{523,8},
{262,1},{294,1},{330,1},{349,1},{392,1},{440,1},{494,1},{523,8}	
};

Note All13[13] = {{523,1},{494,1},{466,1},{440,1},{415,1},{392,1},
{370,1},{349,1},{330,1},{311,1},{294,1},{277,1},{262,1}};

uint16_t Wave[64] = {1024,1122,1219,1314,1407,1495,1580,1658,1731,1797,1855,
  1906,1948,1981,2005,2019,2024,2019,2005,1981,1948,1906,
  1855,1797,1731,1658,1580,1495,1407,1314,1219,1122,1024,
  926,829,734,641,553,468,390,317,251,193,142,
  100,67,43,29,24,29,43,67,100,142,193,
  251,317,390,468,553,641,734,829,926};

uint16_t Wave2[64] = {512,562,597,661,708,753,796,836,874,907,938,963,985,  /* Wave is too loud, so i create a new wave2*/
	1002,1014,1022,1024,1022,1014,1002,985,963,938,907,874,836,796,753,708,
	        661,597,562,512,462,427,363,316,271,228,188,150,117,86,61,39,
	22,10,2,0,2,10,22,39,61,86,117,150,188,228,271,316,363,427,462
};
	
	
	/*
	void Music_Play( uint8_t song){

    if(play){
		  i=i+1;
			DAC_Out(wave[i&0x1F]);
		}

}
*/

void Change_value(uint32_t nextvalue){
	
}


// Interrupt service routine
void SysTick_Handler(void){//counts1 = 500000-----1s---for the hands
//unit 1 is seconds--f=500000
	
	
	if(random==0){//not random mode
		desirevalue = 500000/(Doremi[i&0x3F].freq*64);//the formulat to calculate direvalue			
	}else{//random mode
		desirevalue = 500000/(All13[randomindex].freq*64);//the formulat to calculate direvalue		
	}
	if(play){
		if(random==0){
			//***change note    *(douraimi[i%8].duration[k%3])
			if(counter2>=10000*(Doremi[i%64].duration*k)){//k is the index of duration that can change
				i++;//i is the index of note in a song
				if(i>63)i=0;
				counter2 = 0;//counter2 is for change note in one song
				PF2 ^= 0x04;
			}	
			else{
				counter2++;
			}
			//***in one note
		
			if(counter1>=desirevalue){
				j++;//j is the index of the number in a note
				DAC_Out((Wave2[j&0x3F]));
				counter1 = 0;//counter1 is for change value in one note
			}
			else{		
				counter1++;
			}
		}else{//random mode
			//***change note    *(douraimi[i%8].duration[k%3])
			if(counter2>=10000*(All13[randomindex].duration*k)){//k is the index of duration that can change
				counter2 = 0;//counter2 is for change note in one song
				PF2 ^= 0x04;
				randomindex = rand()%13;
			}	
			else{
				counter2++;
			}
			//***in one note
			if(counter1>=desirevalue){
				j++;//j is the index of the number in a note
				DAC_Out((Wave2[j&0x3F]));
				counter1 = 0;//counter1 is for change value in one note
			}
			else{		
				counter1++;
			}
		}//random mode
	}
}


