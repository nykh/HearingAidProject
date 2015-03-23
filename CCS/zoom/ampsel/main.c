// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2011
 
///////////////////////////////////////////////////////////////////////
// Filename: main.c
//
// Synopsis: Main program file for demonstration code
//
///////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>
#include "DSP_Config.h"
#include "amplitude_selection.h"

extern bool do_process;
extern uint8_t processing;
extern uint16_t signal[2][22000];

uint16_t result[132];

int main()
{    
	
	// initialize DSP board
  	DSP_Init();

	// call StartUp for application specific code
	// defined in each application directory
	StartUp();

	// main stalls here, interrupts drive operation 
  	while(1) { 
		while(!do_process);

		amplitude_selection(result, signal[processing]);
  	}   
}


