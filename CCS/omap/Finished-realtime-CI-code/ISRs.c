// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2011

///////////////////////////////////////////////////////////////////////
// Filename: ISRs.c
//
// Synopsis: Interrupt service routines for OMAP-L138 EDMA 
//
// Modified April 2013 to "flip" the incoming samples properly -- chgw
//
///////////////////////////////////////////////////////////////////////

#include "DSP_Config.h" 
#include "math.h"
#include "frames.h"  
#include "ISRs.h"
#include "Decoder.h"
#include "Amplitude_selection.h"
#include "Filters.h"
#include "DSP_Config.h"

// frame buffer declarations
#define BUFFER_COUNT		1024   // buffer length in McASP samples (L+R)
#define BUFFER_LENGTH   	BUFFER_COUNT*2 // two Int16 read from McASP each time  
#define NUM_BUFFERS     	3     // don't change this! 

#pragma DATA_SECTION (buffer, "CE0"); // allocate buffers in SDRAM 
Int16 buffer[NUM_BUFFERS][BUFFER_LENGTH];
// there are 3 buffers in use at all times, one being filled from the McBSP,
// one being operated on, and one being emptied to the McBSP
// ready_index --> buffer ready for processing
volatile Int16 buffer_ready = 0, over_run = 0, ready_index = 0;

// values used for EDMA channel initialization
#define EDMA_CONFIG_RX_OPTION				0x00100000	// TCINTEN, event 0
#ifdef DSPBOARDTYPE_TI_OMAPL138_LCDK
#define EDMA_CONFIG_RX_SRC_ADDR				((Uint32)(&(McASP0_Base->rbuf[14])))
#else
#define EDMA_CONFIG_RX_SRC_ADDR				((Uint32)(&(McASP0_Base->rbuf[12])))
#endif
#define EDMA_CONFIG_RX_SRC_DEST_B_INDEX		((4 << 16) + 0)	// src_b_index = 0, dest_b_index = 4
#define EDMA_CONFIG_RX_A_B_COUNT			((BUFFER_COUNT << 16) + 4)	// 4-byte transfers
#define EDMA_CONFIG_TX_OPTION				0x00101000	// TCINTEN, event 1
#ifdef DSPBOARDTYPE_TI_OMAPL138_LCDK
#define EDMA_CONFIG_TX_DEST_ADDR			((Uint32)(&(McASP0_Base->xbuf[13])))
#else
#define EDMA_CONFIG_TX_DEST_ADDR			((Uint32)(&(McASP0_Base->xbuf[11])))
#endif
#define EDMA_CONFIG_TX_SRC_DEST_B_INDEX		((0 << 16) + 4)	// src_b_index = 4, dest_b_index = 0
#define EDMA_CONFIG_TX_A_B_COUNT			EDMA_CONFIG_RX_A_B_COUNT
#define EDMA_CONFIG_EVENT_MASK				3	// using events 0 (rx) and 1 (tx)
#define EDMA_CONFIG_INTERRUPT_MASK			1	// interrupt on rx reload only

/* add any global variables here */
float Input0[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input1[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input2[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input3[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input4[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input5[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input6[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input7[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input8[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input9[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input10[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input11[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input12[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input13[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input14[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input15[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input16[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input17[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input18[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input19[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input20[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Input21[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

float result_mean[6]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
int result_channel[6]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float outarray[100];
float thingout[16]= {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
int volume = 10;

void EDMA_Init()
////////////////////////////////////////////////////////////////////////
// Purpose:   Configure EDMA controller to perform all McASP servicing. 
//            EDMA is setup so buffer[2] is outbound to McASP, buffer[0] is 
//            available for processing, and buffer[1] is being loaded.
//            Both the EDMA transmit and receive events are set to automatically
//            reload upon completion, cycling through the 3 buffers. 
//            The EDMA completion interrupt occurs when a buffer has been filled
//            by the EDMA from the McASP.
//            The EDMA interrupt service routine updates the ready buffer index, 
//            and sets the buffer ready flag which is being polled by the main 
//            program loop
//
// Input:     None
//
// Returns:   Nothing
//
// Calls:     Nothing
//
// Notes:     None
///////////////////////////////////////////////////////////////////////
{
	EDMA_params* param;

	// McASP tx event params
	param = (EDMA_params*)EDMA3_0_PARAM(EDMA3_EVENT_MCASP0_TX);
	param->option = EDMA_CONFIG_TX_OPTION;
	param->source = (Uint32)(&buffer[2][0]);
	param->a_b_count = EDMA_CONFIG_TX_A_B_COUNT;
	param->dest = EDMA_CONFIG_TX_DEST_ADDR;
	param->src_dest_b_index = EDMA_CONFIG_TX_SRC_DEST_B_INDEX;
	param->link_reload = (BUFFER_COUNT << 16) + (EDMA3_0_PARAM(64) & 0xFFFF);
	param->c_count = 1;
	
	// set up first tx link param
	param = (EDMA_params*)EDMA3_0_PARAM(64);
	param->option = EDMA_CONFIG_TX_OPTION;
	param->source = (Uint32)(&buffer[0][0]);
	param->a_b_count = EDMA_CONFIG_TX_A_B_COUNT;
	param->dest = EDMA_CONFIG_TX_DEST_ADDR;
	param->src_dest_b_index = EDMA_CONFIG_TX_SRC_DEST_B_INDEX;
	param->link_reload = (BUFFER_COUNT << 16) + (EDMA3_0_PARAM(65) & 0xFFFF);
	param->c_count = 1;
	
	// set up second tx link param
	param = (EDMA_params*)EDMA3_0_PARAM(65);
	param->option = EDMA_CONFIG_TX_OPTION;
	param->source = (Uint32)(&buffer[1][0]);
	param->a_b_count = EDMA_CONFIG_TX_A_B_COUNT;
	param->dest = EDMA_CONFIG_TX_DEST_ADDR;
	param->src_dest_b_index = EDMA_CONFIG_TX_SRC_DEST_B_INDEX;
	param->link_reload = (BUFFER_COUNT << 16) + (EDMA3_0_PARAM(66) & 0xFFFF);
	param->c_count = 1;
	
	// set up third tx link param
	param = (EDMA_params*)EDMA3_0_PARAM(66);
	param->option = EDMA_CONFIG_TX_OPTION;
	param->source = (Uint32)(&buffer[2][0]);
	param->a_b_count = EDMA_CONFIG_TX_A_B_COUNT;
	param->dest = EDMA_CONFIG_TX_DEST_ADDR;
	param->src_dest_b_index = EDMA_CONFIG_TX_SRC_DEST_B_INDEX;
	param->link_reload = (BUFFER_COUNT << 16) + (EDMA3_0_PARAM(64) & 0xFFFF);
	param->c_count = 1;
	
	
	// McASP rx event params
	param = (EDMA_params*)(EDMA3_0_PARAM(EDMA3_EVENT_MCASP0_RX));
	param->option = EDMA_CONFIG_RX_OPTION;
	param->source = EDMA_CONFIG_RX_SRC_ADDR;
	param->a_b_count = EDMA_CONFIG_RX_A_B_COUNT;
	param->dest = (Uint32)(&buffer[1][0]);
	param->src_dest_b_index = EDMA_CONFIG_RX_SRC_DEST_B_INDEX;
	param->link_reload = (BUFFER_COUNT << 16) + (EDMA3_0_PARAM(67) & 0xFFFF);
	param->c_count = 1;
	
	// set up first rx link param
	param = (EDMA_params*)EDMA3_0_PARAM(67);
	param->option = EDMA_CONFIG_RX_OPTION;
	param->source = EDMA_CONFIG_RX_SRC_ADDR;
	param->a_b_count = EDMA_CONFIG_RX_A_B_COUNT;
	param->dest = (Uint32)(&buffer[2][0]);
	param->src_dest_b_index = EDMA_CONFIG_RX_SRC_DEST_B_INDEX;
	param->link_reload = (BUFFER_COUNT << 16) + (EDMA3_0_PARAM(68) & 0xFFFF);
	param->c_count = 1;
	
	// set up second rx link param
	param = (EDMA_params*)EDMA3_0_PARAM(68);
	param->option = EDMA_CONFIG_RX_OPTION;
	param->source = EDMA_CONFIG_RX_SRC_ADDR;
	param->a_b_count = EDMA_CONFIG_RX_A_B_COUNT;
	param->dest = (Uint32)(&buffer[0][0]);
	param->src_dest_b_index = EDMA_CONFIG_RX_SRC_DEST_B_INDEX;
	param->link_reload = (BUFFER_COUNT << 16) + (EDMA3_0_PARAM(69) & 0xFFFF);
	param->c_count = 1;
	
	// set up third rx link param
	param = (EDMA_params*)EDMA3_0_PARAM(69);
	param->option = EDMA_CONFIG_RX_OPTION;
	param->source = EDMA_CONFIG_RX_SRC_ADDR;
	param->a_b_count = EDMA_CONFIG_RX_A_B_COUNT;
	param->dest = (Uint32)(&buffer[1][0]);
	param->src_dest_b_index = EDMA_CONFIG_RX_SRC_DEST_B_INDEX;
	param->link_reload = (BUFFER_COUNT << 16) + (EDMA3_0_PARAM(67) & 0xFFFF);
	param->c_count = 1;
	
	// configure EDMA to start servicing events
	*(volatile Uint32 *)EDMA3_0_CC_ECR  = EDMA_CONFIG_EVENT_MASK;	// clear pending events
	*(volatile Uint32 *)EDMA3_0_CC_EESR = EDMA_CONFIG_EVENT_MASK;	// enable events 
	*(volatile Uint32 *)EDMA3_0_CC_DRAE1 = EDMA_CONFIG_EVENT_MASK;	// enable events for region 1
	*(volatile Uint32 *)EDMA3_0_CC_IESR = EDMA_CONFIG_INTERRUPT_MASK; 	// enable CPU interrupt
}

void ZeroBuffers() 
////////////////////////////////////////////////////////////////////////
// Purpose:   Sets all buffer locations to 0 
//
// Input:     None
//
// Returns:   Nothing
//
// Calls:     Nothing
//
// Notes:     None
///////////////////////////////////////////////////////////////////////
{
    Int32 i = BUFFER_COUNT * NUM_BUFFERS;
    Int32 *p = (Int32 *)buffer;

    while(i--)
        *p++ = 0;
}

void ProcessBuffer()
///////////////////////////////////////////////////////////////////////
// Purpose:   Processes the data in buffer[ready_index] and stores
//            the results back into the buffer 
//            Data is packed into the buffer, alternating right/left
//              Be careful of the order of packing
//
// Input:     None
//
// Returns:   Nothing
//
// Calls:     Nothing
//
// Notes:     None
///////////////////////////////////////////////////////////////////////
{   
    Int16 *pBuf = buffer[ready_index];

	static float Left[BUFFER_COUNT]={0}, Right[BUFFER_COUNT]={0};
    float *pL = Left, *pR = Right;
    Int32 i, j, k;
    float yLeft, yRight;

    for(i = 0;i < BUFFER_COUNT;i++) { // extract data to float buffers
    // order is important here: must go right first then left
       *pR++ = *pBuf++;
       *pL++ = *pBuf++;
    }

    // reinitialize pointer before FOR loop
    pBuf = buffer[ready_index];



    for(i = 0; i <64 ; i += 1) {
    	for(j = 0; j < 16; j += 1){
    		int location = (16 * i) + j;
    		float filterthis = (Left[location] + Right[location])/65536;
		filter(filterthis);
		Input0[j] = filteroutput1;
		Input1[j] = filteroutput2;
		Input2[j] = filteroutput3;
		Input3[j] = filteroutput4;
		Input4[j] = filteroutput5;
		Input5[j] = filteroutput6;
		Input6[j] = filteroutput7;
		Input7[j] = 0;//filteroutput8;
		Input8[j] = filteroutput9;
		Input9[j] = filteroutput10;
		Input10[j] = filteroutput11;
		Input11[j] = filteroutput12;
		Input12[j] = filteroutput13;
		Input13[j] = filteroutput14;
		Input14[j] = filteroutput15;
		Input15[j] = filteroutput16;
		Input16[j] = filteroutput17;
		Input17[j] = filteroutput18;
		Input18[j] = filteroutput19;
		Input19[j] = filteroutput20;
		Input20[j] = filteroutput21;
		Input21[j] = filteroutput22;



    	}
			amplitude_selection();
			decode_channels();

			for(k = 0; k < 16; k++){

			yLeft = (thingout[k]+1) * 65536;
			yRight = (thingout[k]+1) * 65536;

			*pBuf = (Int16) yRight;
			pBuf++;
			*pBuf = (Int16) yLeft;
			pBuf++;

		    // pack into buffer after bounding (must be right then left)
/*
		    *pBuf = _spint(yRight * 65536) >> 16;
		    pBuf++;
		    *pBuf = _spint(yLeft * 65536) >> 16;
		    pBuf++;
		    */
    }}




//////// end of FIR routine ///////////

  // reinitialize pointer
  pBuf = buffer[ready_index];




    buffer_ready = 0; // signal we are done
}

///////////////////////////////////////////////////////////////////////
// Purpose:   Access function for buffer ready flag 
//
// Input:     None
//
// Returns:   Non-zero when a buffer is ready for processing
//
// Calls:     Nothing
//
// Notes:     None
///////////////////////////////////////////////////////////////////////
int IsBufferReady()
{
	return buffer_ready;
}

///////////////////////////////////////////////////////////////////////
// Purpose:   Access function for buffer overrun flag 
//
// Input:     None
//
// Returns:   Non-zero if a buffer overrun has occurred
//
// Calls:     Nothing
//
// Notes:     None
///////////////////////////////////////////////////////////////////////
int IsOverRun()
{
	return over_run;
}
 
interrupt void EDMA_ISR()
///////////////////////////////////////////////////////////////////////
// Purpose:   EDMA interrupt service routine.  Invoked on every buffer 
//            completion 
//
// Input:     None
//
// Returns:   Nothing
//
// Calls:     Nothing
//
// Notes:     None
///////////////////////////////////////////////////////////////////////
{
	*(volatile Uint32 *)EDMA3_0_CC_ICR = EDMA_CONFIG_INTERRUPT_MASK; // clear interrupt
	if(++ready_index >= NUM_BUFFERS) // update buffer index
		ready_index = 0;
	if(buffer_ready == 1) // set a flag if buffer isn't processed in time 
		over_run = 1;
	buffer_ready = 1; // mark buffer as ready for processing

}

