#include "DSP_Config.h"

#include <stdio.h>
#include "amplitude_selection.h"



int main(void) {
	// initialize DSP board
  	DSP_Init();

	// call StartUp for application specific code
	// defined in each application directory
	StartUp();

	for(;;);
}
