// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2011

///////////////////////////////////////////////////////////////////////
// Filename: StartUp.c
//
// Synopsis: Placeholder for code run after DSP_Init()
//
///////////////////////////////////////////////////////////////////////

#include "DSP_Config.h"
#include "amplitude_selection.h"

static double result[132];

void StartUp()
{
	amplitude_selection(result);
}