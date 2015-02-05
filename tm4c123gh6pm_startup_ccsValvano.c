//*****************************************************************************
//
// Startup code for use with TI's Code Composer Studio.
//
// Copyright (c) 2011-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
//*****************************************************************************

#include <stdint.h>

//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
void Reset_Handler(void);
static void NMI_Handler(void);
static void HardFault_Handler(void);
static void MpuFault_Handler(void);
static void BusFault_Handler(void);
static void UsageFault_Handler(void);
static void IntDefaultHandler(void);

//Weak Function Deffinitions, can be written / declared in other files
extern void PendSV_Handler			  (void) __attribute__((weak));
extern void SysTick_Handler			  (void) __attribute__((weak));
extern void IntDefaultHandler		  (void) __attribute__((weak));
extern void GPIOPortA_Handler         (void) __attribute__((weak));
extern void GPIOPortB_Handler         (void) __attribute__((weak));
extern void GPIOPortC_Handler         (void) __attribute__((weak));
extern void GPIOPortD_Handler         (void) __attribute__((weak));
extern void GPIOPortE_Handler         (void) __attribute__((weak));
extern void UART0_Handler             (void) __attribute__((weak));
extern void UART1_Handler             (void) __attribute__((weak));
extern void SSI0_Handler              (void) __attribute__((weak));
extern void I2C0_Handler              (void) __attribute__((weak));
extern void PWMFault_Handler          (void) __attribute__((weak));
extern void PWM0_Handler              (void) __attribute__((weak));
extern void PWM1_Handler              (void) __attribute__((weak));
extern void PWM2_Handler              (void) __attribute__((weak));
extern void Quadrature0_Handler       (void) __attribute__((weak));
extern void ADC0_Handler              (void) __attribute__((weak));
extern void ADC1_Handler              (void) __attribute__((weak));
extern void ADC2_Handler              (void) __attribute__((weak));
extern void ADC3_Handler              (void) __attribute__((weak));
extern void WDT_Handler               (void) __attribute__((weak));
extern void Timer0A_Handler           (void) __attribute__((weak));
extern void Timer0B_Handler           (void) __attribute__((weak));
extern void Timer1A_Handler           (void) __attribute__((weak));
extern void Timer1B_Handler           (void) __attribute__((weak));
extern void Timer2A_Handler           (void) __attribute__((weak));
extern void Timer2B_Handler           (void) __attribute__((weak));
extern void Comp0_Handler             (void) __attribute__((weak));
extern void Comp1_Handler             (void) __attribute__((weak));
extern void Comp2_Handler             (void) __attribute__((weak));
extern void SysCtl_Handler            (void) __attribute__((weak));
extern void FlashCtl_Handler          (void) __attribute__((weak));
extern void GPIOPortF_Handler         (void) __attribute__((weak));
extern void GPIOPortG_Handler         (void) __attribute__((weak));
extern void GPIOPortH_Handler         (void) __attribute__((weak));
extern void UART2_Handler             (void) __attribute__((weak));
extern void SSI1_Handler              (void) __attribute__((weak));
extern void Timer3A_Handler           (void) __attribute__((weak));
extern void Timer3B_Handler           (void) __attribute__((weak));
extern void I2C1_Handler              (void) __attribute__((weak));
extern void Quadrature1_Handler       (void) __attribute__((weak));
extern void CAN0_Handler              (void) __attribute__((weak));
extern void CAN1_Handler              (void) __attribute__((weak));
extern void CAN2_Handler              (void) __attribute__((weak));
extern void Ethernet_Handler          (void) __attribute__((weak));
extern void Hibernate_Handler         (void) __attribute__((weak));
extern void USB0_Handler              (void) __attribute__((weak));
extern void PWM3_Handler              (void) __attribute__((weak));
extern void uDMA_Handler              (void) __attribute__((weak));
extern void uDMA_Error                (void) __attribute__((weak));

//*****************************************************************************
//
// External declaration for the reset handler that is to be called when the
// processor is started
//
//*****************************************************************************
extern void _c_int00(void);

//*****************************************************************************
//
// Linker variable that marks the top of the stack.
//
//*****************************************************************************
extern uint32_t __STACK_TOP;

//*****************************************************************************
//
// External declarations for the interrupt handlers used by the application.
//
//*****************************************************************************
// To be added by user

//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000 or at the start of
// the program if located at a start address other than 0.
//
//*****************************************************************************

#pragma DATA_SECTION(g_pfnVectors, ".intvecs")
void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))((unsigned long)&__STACK_TOP),
                                            // The initial stack pointer
    Reset_Handler,                          // The reset handler
    NMI_Handler,                            // The NMI handler
    HardFault_Handler,                      // The hard fault handler
    MpuFault_Handler,	                    // The MPU fault handler
    BusFault_Handler,                       // The bus fault handler
    UsageFault_Handler,                     // The usage fault handler
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    SVC_Handler,          		            // SVCall handler
    DebugMon_Handler,                       // Debug monitor handler
    0,                                      // Reserved
    PendSV_Handler,                         // The PendSV handler
    SysTick_Handler,                        // The SysTick handler
    GPIOPortA_Handler,                      // GPIO Port A
    GPIOPortB_Handler,                      // GPIO Port B
    GPIOPortC_Handler,                      // GPIO Port C
    GPIOPortD_Handler,                      // GPIO Port D
    GPIOPortE_Handler,                      // GPIO Port E
    UART0_Handler,                    		// UART0 Rx and Tx
    UART1_Handler,                      	// UART1 Rx and Tx
    SSI0_Handler,                      		// SSI0 Rx and Tx
    I2C0_Handler,                      		// I2C0 Master and Slave
    PWMFault_Handler,                      	// PWM Fault
    PWM0_Handler,							// PWM Generator 0
    PWM1_Handler,                      		// PWM Generator 1
    PWM2_Handler,                      		// PWM Generator 2
    Quadrature0_Handler,                    // Quadrature Encoder 0
    ADC0_Handler,                      		// ADC Sequence 0
    ADC1_Handler,                      		// ADC Sequence 1
    ADC2_Handler,                      		// ADC Sequence 2
    ADC3_Handler,                      		// ADC Sequence 3
    WDT_Handler,                      		// Watchdog timer
    Timer0A_Handler,                      	// Timer 0 subtimer A
    Timer0B_Handler,                      	// Timer 0 subtimer B
    Timer1A_Handler,                      	// Timer 1 subtimer A
    Timer1B_Handler,                      	// Timer 1 subtimer B
    Timer2A_Handler,                      	// Timer 2 subtimer A
    Timer2B_Handler,                      	// Timer 2 subtimer B
    Comp0_Handler,                      	// Analog Comparator 0
    Comp1_Handler,                      	// Analog Comparator 1
    Comp2_Handler,                      	// Analog Comparator 2
    SysCtl_Handler,                      	// System Control (PLL, OSC, BO)
    FlashCtl_Handler,                      	// FLASH Control
    GPIOPortF_Handler,                      // GPIO Port F
    GPIOPortG_Handler,                      // GPIO Port G
    GPIOPortH_Handler,                      // GPIO Port H
    UART2_Handler,                      	// UART2 Rx and Tx
    SSI1_Handler,                      		// SSI1 Rx and Tx
    Timer3A_Handler,                      	// Timer 3 subtimer A
    Timer3B_Handler,                      	// Timer 3 subtimer B
    I2C1_Handler,                      		// I2C1 Master and Slave
    Quadrature1_Handler,                    // Quadrature Encoder 1
    CAN0_Handler,                      		// CAN0
    CAN1_Handler,                      		// CAN1
    CAN2_Handler,                      		// CAN2
    Ethernet_Handler,                      	// Ethernet
    Hibernate_Handler                       // Hibernate
	IntDefaultHandler,						// USB0
	IntDefaultHandler,						// PWM Generator 3
	IntDefaultHandler,						// uDMA Software Transfer
	IntDefaultHandler, 						// uDMA Error
	IntDefaultHandler,                      // ADC1 Sequence 0
    IntDefaultHandler,                      // ADC1 Sequence 1
    IntDefaultHandler,                      // ADC1 Sequence 2
    IntDefaultHandler,                      // ADC1 Sequence 3
    0,                                      // Reserved
    0,                                      // Reserved
    IntDefaultHandler,                      // GPIO Port J
    IntDefaultHandler,                      // GPIO Port K
    IntDefaultHandler,                      // GPIO Port L
    IntDefaultHandler,                      // SSI2 Rx and Tx
    IntDefaultHandler,                      // SSI3 Rx and Tx
    IntDefaultHandler,                      // UART3 Rx and Tx
    IntDefaultHandler,                      // UART4 Rx and Tx
    IntDefaultHandler,                      // UART5 Rx and Tx
    IntDefaultHandler,                      // UART6 Rx and Tx
    IntDefaultHandler,                      // UART7 Rx and Tx
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    IntDefaultHandler,                      // I2C2 Master and Slave
    IntDefaultHandler,                      // I2C3 Master and Slave
    IntDefaultHandler,                      // Timer 4 subtimer A
    IntDefaultHandler,                      // Timer 4 subtimer B
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    IntDefaultHandler,                      // Timer 5 subtimer A
    IntDefaultHandler,                      // Timer 5 subtimer B
    IntDefaultHandler,                      // Wide Timer 0 subtimer A
    IntDefaultHandler,                      // Wide Timer 0 subtimer B
    IntDefaultHandler,                      // Wide Timer 1 subtimer A
    IntDefaultHandler,                      // Wide Timer 1 subtimer B
    IntDefaultHandler,                      // Wide Timer 2 subtimer A
    IntDefaultHandler,                      // Wide Timer 2 subtimer B
    IntDefaultHandler,                      // Wide Timer 3 subtimer A
    IntDefaultHandler,                      // Wide Timer 3 subtimer B
    IntDefaultHandler,                      // Wide Timer 4 subtimer A
    IntDefaultHandler,                      // Wide Timer 4 subtimer B
    IntDefaultHandler,                      // Wide Timer 5 subtimer A
    IntDefaultHandler,                      // Wide Timer 5 subtimer B
    IntDefaultHandler,                      // FPU
    0,                                      // Reserved
    0,                                      // Reserved
    IntDefaultHandler,                      // I2C4 Master and Slave
    IntDefaultHandler,                      // I2C5 Master and Slave
    IntDefaultHandler,                      // GPIO Port M
    IntDefaultHandler,                      // GPIO Port N
    IntDefaultHandler,                      // Quadrature Encoder 2
    0,                                      // Reserved
    0,                                      // Reserved
    IntDefaultHandler,                      // GPIO Port P (Summary or P0)
    IntDefaultHandler,                      // GPIO Port P1
    IntDefaultHandler,                      // GPIO Port P2
    IntDefaultHandler,                      // GPIO Port P3
    IntDefaultHandler,                      // GPIO Port P4
    IntDefaultHandler,                      // GPIO Port P5
    IntDefaultHandler,                      // GPIO Port P6
    IntDefaultHandler,                      // GPIO Port P7
    IntDefaultHandler,                      // GPIO Port Q (Summary or Q0)
    IntDefaultHandler,                      // GPIO Port Q1
    IntDefaultHandler,                      // GPIO Port Q2
    IntDefaultHandler,                      // GPIO Port Q3
    IntDefaultHandler,                      // GPIO Port Q4
    IntDefaultHandler,                      // GPIO Port Q5
    IntDefaultHandler,                      // GPIO Port Q6
    IntDefaultHandler,                      // GPIO Port Q7
    IntDefaultHandler,                      // GPIO Port R
    IntDefaultHandler,                      // GPIO Port S
    IntDefaultHandler,                      // PWM 1 Generator 0
    IntDefaultHandler,                      // PWM 1 Generator 1
    IntDefaultHandler,                      // PWM 1 Generator 2
    IntDefaultHandler,                      // PWM 1 Generator 3
    IntDefaultHandler                       // PWM 1 Fault
};

//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
//
//*****************************************************************************
void
Reset_Handler(void)
{
    //
    // Jump to the CCS C initialization routine.  This will enable the
    // floating-point unit as well, so that does not need to be done here.
    //
    __asm("    .global _c_int00\n"
          "    b.w     _c_int00");
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************
static void
NMI_Handler(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a fault
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void
HardFault_Handler(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void
IntDefaultHandler(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}


//******************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//******************************************************************************
static void MpuFault_Handler	(void){ while(1);}
static void BusFault_Handler	(void){ while(1);}
static void UsageFault_Handler 	(void){ while(1);}
static void SVC_Handler			(void){ while(1);}
static void DebugMon_Handler	(void){ while(1);}

//These Functions are all weakly defined, so the user can write over them in an external file
void PendSV_Handler		(void){ while(1);}
void SysTick_Handler	(void){ while(1);}
void IntDefaultHandler	(void){ while(1);}
void GPIOPortA_Handler	(void){ while(1);}
void GPIOPortB_Handler	(void){ while(1);}
void GPIOPortC_Handler	(void){ while(1);}
void GPIOPortD_Handler	(void){ while(1);}
void GPIOPortE_Handler	(void){ while(1);}
void UART0_Handler		(void){ while(1);}
void UART1_Handler		(void){ while(1);}
void SSI0_Handler		(void){ while(1);}
void I2C0_Handler		(void){ while(1);}
void PWMFault_Handler	(void){ while(1);}
void PWM0_Handler		(void){ while(1);}
void PWM1_Handler		(void){ while(1);}
void PWM2_Handler		(void){ while(1);}
void Quadrature0_Handler(void){ while(1);}
void ADC0_Handler		(void){ while(1);}
void ADC1_Handler		(void){ while(1);}
void ADC2_Handler		(void){ while(1);}
void ADC3_Handler		(void){ while(1);}
void WDT_Handler		(void){ while(1);}
void Timer0A_Handler	(void){ while(1);}
void Timer0B_Handler	(void){ while(1);}
void Timer1A_Handler	(void){ while(1);}
void Timer1B_Handler	(void){ while(1);}
void Timer2A_Handler	(void){ while(1);}
void Timer2B_Handler	(void){ while(1);}
void Comp0_Handler		(void){ while(1);}
void Comp1_Handler		(void){ while(1);}
void Comp2_Handler		(void){ while(1);}
void SysCtl_Handler		(void){ while(1);}
void FlashCtl_Handler	(void){ while(1);}
void GPIOPortF_Handler	(void){ while(1);}
void GPIOPortG_Handler	(void){ while(1);}
void GPIOPortH_Handler	(void){ while(1);}
void UART2_Handler		(void){ while(1);}
void SSI1_Handler		(void){ while(1);}
void Timer3A_Handler	(void){ while(1);}
void Timer3B_Handler	(void){ while(1);}
void I2C1_Handler		(void){ while(1);}
void Quadrature1_Handler(void){ while(1);}
void CAN0_Handler		(void){ while(1);}
void CAN1_Handler		(void){ while(1);}
void CAN2_Handler		(void){ while(1);}
void Ethernet_Handler	(void){ while(1);}
void Hibernate_Handler	(void){ while(1);}
void USB0_Handler		(void){ while(1);}
void PWM3_Handler		(void){ while(1);}
void uDMA_Handler		(void){ while(1);}
void uDMA_Error			(void){ while(1);}

//******************************************************************************
//
// Useful functions.
//
//******************************************************************************
extern void  DisableInterrupts(void) ;
extern void  EnableInterrupts(void) ;
extern void  StartCritical(void) ;
extern void  EndCritical(void);
extern void  WaitForInterrupt (void);

//*********** DisableInterrupts ***************
// disable interrupts
// inputs:  none
// outputs: none
void DisableInterrupts(void){
	__asm ("    CPSID  I\n"
		   "    BX     LR\n");
}

//*********** EnableInterrupts ***************
// emable interrupts
// inputs:  none
// outputs: none
void EnableInterrupts(void){
	__asm  ("    CPSIE  I\n"
			"    BX     LR\n");
}

//*********** StartCritical ************************
// make a copy of previous I bit, disable interrupts
// inputs:  none
// outputs: previous I bit
void StartCritical(void){
	__asm  ("    MRS    R0, PRIMASK  	; save old status \n"
			"    CPSID  I         	; mask all (except faults)\n"
			"    BX     LR\n");
}

//*********** EndCritical ************************
// using the copy of previous I bit, restore I bit to previous value
// inputs:  previous I bit
// outputs: none
void EndCritical(void){
	__asm  ("    MSR    PRIMASK, R0\n"
			"    BX     LR\n");
}

//*********** WaitForInterrupt ************************
// go to low power mode while waiting for the next interrupt
// inputs:  none
// outputs: none
void WaitForInterrupt(void){
	__asm  ("    WFI\n"
			"    BX     LR\n");
}

