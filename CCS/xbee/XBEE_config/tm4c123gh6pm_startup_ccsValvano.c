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

#define TARGET_IS_BLIZZARD_RA1

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
static void SVC_Handler(void);
static void DebugMon_Handler(void);

//Weak Function Deffinitions, can be written / declared in other files
extern void PendSV_Handler            (void) __attribute__((weak));
extern void SysTick_Handler           (void) __attribute__((weak));
extern void GPIOPortA_Handler         (void) __attribute__((weak));
extern void GPIOPortB_Handler         (void) __attribute__((weak));
extern void GPIOPortC_Handler         (void) __attribute__((weak));
extern void GPIOPortD_Handler         (void) __attribute__((weak));
extern void GPIOPortE_Handler         (void) __attribute__((weak));
extern void UART0_Handler             (void) __attribute__((weak));
extern void UART1_Handler             (void) __attribute__((weak));
extern void SSI0_Handler              (void) __attribute__((weak));
extern void I2C0_Handler              (void) __attribute__((weak));
extern void PWM0Fault_Handler         (void) __attribute__((weak));
extern void PWM0Gen0_Handler          (void) __attribute__((weak));
extern void PWM0Gen1_Handler          (void) __attribute__((weak));
extern void PWM0Gen2_Handler          (void) __attribute__((weak));
extern void Quadrature0_Handler       (void) __attribute__((weak));
extern void ADC0Seq0_Handler          (void) __attribute__((weak));
extern void ADC0Seq1_Handler          (void) __attribute__((weak));
extern void ADC0Seq2_Handler          (void) __attribute__((weak));
extern void ADC0Seq3_Handler          (void) __attribute__((weak));
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
extern void UART2_Handler             (void) __attribute__((weak));
extern void SSI1_Handler              (void) __attribute__((weak));
extern void Timer3A_Handler           (void) __attribute__((weak));
extern void Timer3B_Handler           (void) __attribute__((weak));
extern void I2C1_Handler              (void) __attribute__((weak));
extern void Quadrature1_Handler       (void) __attribute__((weak));
extern void CAN0_Handler              (void) __attribute__((weak));
extern void CAN1_Handler              (void) __attribute__((weak));
extern void Hibernate_Handler         (void) __attribute__((weak));
extern void USB0_Handler              (void) __attribute__((weak));
extern void PWM3_Handler              (void) __attribute__((weak));
extern void uDMA_Handler              (void) __attribute__((weak));
extern void uDMA_Error                (void) __attribute__((weak));
extern void ADC1Seq0_Handler          (void) __attribute__((weak));
extern void ADC1Seq1_Handler          (void) __attribute__((weak));
extern void ADC1Seq2_Handler          (void) __attribute__((weak));
extern void ADC1Seq3_Handler          (void) __attribute__((weak));
extern void SSI2_Handler              (void) __attribute__((weak));
extern void SSI3_Handler              (void) __attribute__((weak));
extern void UART3_Handler             (void) __attribute__((weak));
extern void UART4_Handler             (void) __attribute__((weak));
extern void UART5_Handler             (void) __attribute__((weak));
extern void UART6_Handler             (void) __attribute__((weak));
extern void UART7_Handler             (void) __attribute__((weak));
extern void I2C2_Handler              (void) __attribute__((weak));
extern void I2C3_Handler              (void) __attribute__((weak));
extern void Timer4A_Handler           (void) __attribute__((weak));
extern void Timer4B_Handler           (void) __attribute__((weak));
extern void Timer5A_Handler           (void) __attribute__((weak));
extern void Timer5B_Handler           (void) __attribute__((weak));
extern void WideTimer0A_Handler       (void) __attribute__((weak));
extern void WideTimer0B_Handler       (void) __attribute__((weak));
extern void WideTimer1A_Handler       (void) __attribute__((weak));
extern void WideTimer1B_Handler       (void) __attribute__((weak));
extern void WideTimer2A_Handler       (void) __attribute__((weak));
extern void WideTimer2B_Handler       (void) __attribute__((weak));
extern void WideTimer3A_Handler       (void) __attribute__((weak));
extern void WideTimer3B_Handler       (void) __attribute__((weak));
extern void WideTimer4A_Handler       (void) __attribute__((weak));
extern void WideTimer4B_Handler       (void) __attribute__((weak));
extern void WideTimer5A_Handler       (void) __attribute__((weak));
extern void WideTimer5B_Handler       (void) __attribute__((weak));
extern void FPUException_Handler      (void) __attribute__((weak));
extern void PWM1Gen0_Handler          (void) __attribute__((weak));
extern void PWM1Gen1_Handler          (void) __attribute__((weak));
extern void PWM1Gen2_Handler          (void) __attribute__((weak));
extern void PWM1Gen3_Handler          (void) __attribute__((weak));
extern void PWM1Fault_Handler         (void) __attribute__((weak));

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
    /* Exception Handlers */
    Reset_Handler,              // 1  The reset handler
    NMI_Handler,                // 2  The NMI handler
    HardFault_Handler,          // 3  The hard fault handler
    MpuFault_Handler,           // 4  The MPU fault handler
    BusFault_Handler,           // 5  The bus fault handler
    UsageFault_Handler,         // 6  The usage fault handler
    0,                          // 7  Reserved
    0,                          // 8  Reserved
    0,                          // 9  Reserved
    0,                          // 10  Reserved
    SVC_Handler,                // 11  SVCall handler
    DebugMon_Handler,           // 12  Debug monitor handler
    0,                          // 13  Reserved
    PendSV_Handler,             // 14  The PendSV handler
    SysTick_Handler,            // 15  The SysTick handler

    /* Interrupt Handlers */
    GPIOPortA_Handler,          // 16  GPIO Port A
    GPIOPortB_Handler,          // 17  GPIO Port B
    GPIOPortC_Handler,          // 18  GPIO Port C
    GPIOPortD_Handler,          // 19  GPIO Port D
    GPIOPortE_Handler,          // 20  GPIO Port E
    UART0_Handler,              // 21  UART0 Rx and Tx
    UART1_Handler,              // 22  UART1 Rx and Tx
    SSI0_Handler,               // 23  SSI0 Rx and Tx
    I2C0_Handler,               // 24  I2C0 Master and Slave
    PWM0Fault_Handler,          // 25  PWM Fault
    PWM0Gen0_Handler,           // 26  PWM Generator 0
    PWM0Gen1_Handler,           // 27  PWM Generator 1
    PWM0Gen2_Handler,           // 28  PWM Generator 2
    Quadrature0_Handler,        // 29  Quadrature Encoder 0
    ADC0Seq0_Handler,           // 30  ADC Sequence 0
    ADC1Seq1_Handler,           // 31  ADC Sequence 1
    ADC1Seq2_Handler,           // 32  ADC Sequence 2
    ADC1Seq3_Handler,           // 33  ADC Sequence 3
    WDT_Handler,                // 34  Watchdog timer
    Timer0A_Handler,            // 35  Timer 0 subtimer A
    Timer0B_Handler,            // 36  Timer 0 subtimer B
    Timer1A_Handler,            // 37  Timer 1 subtimer A
    Timer1B_Handler,            // 38  Timer 1 subtimer B
    Timer2A_Handler,            // 39  Timer 2 subtimer A
    Timer2B_Handler,            // 40  Timer 2 subtimer B
    Comp0_Handler,              // 41  Analog Comparator 0
    Comp1_Handler,              // 42  Analog Comparator 1
    Comp2_Handler,              // 43  Analog Comparator 2
    SysCtl_Handler,             // 44  System Control (PLL, OSC, BO)
    FlashCtl_Handler,           // 45  FLASH Control
    GPIOPortF_Handler,          // 46  GPIO Port F
    0,                          // 47  Reserved
    0,                          // 48  Reserved
    UART2_Handler,              // 49  UART2 Rx and Tx
    SSI1_Handler,               // 50  SSI1 Rx and Tx
    Timer3A_Handler,            // 51  Timer 3 subtimer A
    Timer3B_Handler,            // 52  Timer 3 subtimer B
    I2C1_Handler,               // 53  I2C1 Master and Slave
    Quadrature1_Handler,        // 54  Quadrature Encoder 1
    CAN0_Handler,               // 55  CAN0
    CAN1_Handler,               // 56  CAN1
    0,                          // 57  Reserved
    0,                          // 58  Reserved
    Hibernate_Handler,          // 59  Hibernate
    USB0_Handler,               // 60  USB0
    PWM3_Handler,               // 61  PWM Generator 3
    uDMA_Handler,               // 62  uDMA Software Transfer
    uDMA_Error,                 // 63  uDMA Error
    ADC1Seq0_Handler,           // 64  ADC1 Sequence 0
    ADC1Seq1_Handler,           // 65  ADC1 Sequence 1
    ADC1Seq2_Handler,           // 66  ADC1 Sequence 2
    ADC1Seq3_Handler,           // 67  ADC1 Sequence 3
    0,                          // 68  Reserved
    0,                          // 69  Reserved
    0,                          // 70  Reserved
    0,                          // 71  Reserved
    0,                          // 72  Reserved
    SSI2_Handler,               // 73  SSI2 Rx and Tx
    SSI3_Handler,               // 74  SSI3 Rx and Tx
    UART3_Handler,              // 75  UART3 Rx and Tx
    UART4_Handler,              // 76  UART4 Rx and Tx
    UART5_Handler,              // 77  UART5 Rx and Tx
    UART6_Handler,              // 78  UART6 Rx and Tx
    UART7_Handler,              // 79  UART7 Rx and Tx
    0,                          // 80  Reserved
    0,                          // 81  Reserved
    0,                          // 82  Reserved
    0,                          // 83  Reserved
    I2C2_Handler,               // 84  I2C2 Master and Slave
    I2C3_Handler,               // 85  I2C3 Master and Slave
    Timer4A_Handler,            // 86  Timer 4 subtimer A
    Timer4B_Handler,            // 87  Timer 4 subtimer B
    0,                          // 88  Reserved
    0,                          // 89  Reserved
    0,                          // 90  Reserved
    0,                          // 91  Reserved
    0,                          // 92  Reserved
    0,                          // 93  Reserved
    0,                          // 94  Reserved
    0,                          // 95  Reserved
    0,                          // 96  Reserved
    0,                          // 97  Reserved
    0,                          // 98  Reserved
    0,                          // 99  Reserved
    0,                          // 100  Reserved
    0,                          // 101  Reserved
    0,                          // 102  Reserved
    0,                          // 103  Reserved
    0,                          // 104  Reserved
    0,                          // 105  Reserved
    0,                          // 106  Reserved
    0,                          // 107  Reserved
    Timer5A_Handler,            // 108  Timer 5 subtimer A
    Timer5B_Handler,            // 109  Timer 5 subtimer B
    WideTimer0A_Handler,        // 110  Wide Timer 0 subtimer A
    WideTimer0B_Handler,        // 111  Wide Timer 0 subtimer B
    WideTimer1A_Handler,        // 112  Wide Timer 1 subtimer A
    WideTimer1B_Handler,        // 113  Wide Timer 1 subtimer B
    WideTimer2A_Handler,        // 114  Wide Timer 2 subtimer A
    WideTimer2B_Handler,        // 115  Wide Timer 2 subtimer B
    WideTimer3A_Handler,        // 116  Wide Timer 3 subtimer A
    WideTimer3B_Handler,        // 117  Wide Timer 3 subtimer B
    WideTimer4A_Handler,        // 118  Wide Timer 4 subtimer A
    WideTimer4B_Handler,        // 119  Wide Timer 4 subtimer B
    WideTimer5A_Handler,        // 120  Wide Timer 5 subtimer A
    WideTimer5B_Handler,        // 121  Wide Timer 5 subtimer B
    FPUException_Handler,       // 122  FPU
    0,                          // 123  Reserved
    0,                          // 124  Reserved
    0,                          // 125  Reserved
    0,                          // 126  Reserved
    0,                          // 127  Reserved
    0,                          // 128  Reserved
    0,                          // 129  Reserved
    0,                          // 130  Reserved
    0,                          // 131  Reserved
    0,                          // 132  Reserved
    0,                          // 133  Reserved
    0,                          // 134  Reserved
    0,                          // 135  Reserved
    0,                          // 136  Reserved
    0,                          // 137  Reserved
    0,                          // 138  Reserved
    0,                          // 139  Reserved
    0,                          // 140  Reserved
    0,                          // 141  Reserved
    0,                          // 142  Reserved
    0,                          // 143  Reserved
    0,                          // 144  Reserved
    0,                          // 145  Reserved
    0,                          // 146  Reserved
    0,                          // 147  Reserved
    0,                          // 148  Reserved
    0,                          // 149  Reserved
    PWM1Gen0_Handler,           // 150  PWM 1 Generator 0
    PWM1Gen1_Handler,           // 151  PWM 1 Generator 1
    PWM1Gen2_Handler,           // 152  PWM 1 Generator 2
    PWM1Gen3_Handler,           // 153  PWM 1 Generator 3
    PWM1Fault_Handler,          // 154  PWM 1 Fault
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
static void SVC_Handler	      	(void){ while(1);}
static void DebugMon_Handler	(void){ while(1);}

//These Functions are all weakly defined, so the user can write over them in an external file
void PendSV_Handler            (void){ while(1);}
void SysTick_Handler           (void){ while(1);}
void GPIOPortA_Handler         (void){ while(1);}
void GPIOPortB_Handler         (void){ while(1);}
void GPIOPortC_Handler         (void){ while(1);}
void GPIOPortD_Handler         (void){ while(1);}
void GPIOPortE_Handler	       (void){ while(1);}
void UART0_Handler             (void){ while(1);}
void UART1_Handler             (void){ while(1);}
void SSI0_Handler              (void){ while(1);}
void I2C0_Handler              (void){ while(1);}
void PWM0Fault_Handler         (void){ while(1);}
void PWM0Gen0_Handler          (void){ while(1);}
void PWM0Gen1_Handler          (void){ while(1);}
void PWM0Gen2_Handler          (void){ while(1);}
void Quadrature0_Handler       (void){ while(1);}
void ADC0_Handler              (void){ while(1);}
void ADC1_Handler              (void){ while(1);}
void ADC2_Handler              (void){ while(1);}
void ADC3_Handler              (void){ while(1);}
void WDT_Handler               (void){ while(1);}
void Timer0A_Handler	       (void){ while(1);}
void Timer0B_Handler	       (void){ while(1);}
void Timer1A_Handler	       (void){ while(1);}
void Timer1B_Handler	       (void){ while(1);}
void Timer2A_Handler	       (void){ while(1);}
void Timer2B_Handler	       (void){ while(1);}
void Comp0_Handler             (void){ while(1);}
void Comp1_Handler             (void){ while(1);}
void Comp2_Handler             (void){ while(1);}
void SysCtl_Handle             (void){ while(1);}
void FlashCtl_Handler	       (void){ while(1);}
void GPIOPortF_Handler	       (void){ while(1);}
void UART2_Handler             (void){ while(1);}
void SSI1_Handler              (void){ while(1);}
void Timer3A_Handler	       (void){ while(1);}
void Timer3B_Handler	       (void){ while(1);}
void I2C1_Handler              (void){ while(1);}
void Quadrature1_Handler       (void){ while(1);}
void CAN0_Handler              (void){ while(1);}
void CAN1_Handler              (void){ while(1);}
void Hibernate_Handler	       (void){ while(1);}
void USB0_Handler              (void){ while(1);}
void PWM3_Handler              (void){ while(1);}
void uDMA_Handler              (void){ while(1);}
void uDMA_Error	               (void){ while(1);}
void ADC1Seq0_Handler          (void) { while(1);}
void ADC1Seq1_Handler          (void) { while(1);}
void ADC1Seq2_Handler          (void) { while(1);}
void ADC1Seq3_Handler          (void) { while(1);}
void SSI2_Handler              (void) { while(1);}
void SSI3_Handler              (void) { while(1);}
void UART3_Handler             (void) { while(1);}
void UART4_Handler             (void) { while(1);}
void UART5_Handler             (void) { while(1);}
void UART6_Handler             (void) { while(1);}
void UART7_Handler             (void) { while(1);}
void I2C2_Handler              (void) { while(1);}
void I2C3_Handler              (void) { while(1);}
void Timer4A_Handler           (void) { while(1);}
void Timer4B_Handler           (void) { while(1);}
void Timer5A_Handler           (void) { while(1);}
void Timer5B_Handler           (void) { while(1);}
void WideTimer0A_Handler       (void) { while(1);}
void WideTimer0B_Handler       (void) { while(1);}
void WideTimer1A_Handler       (void) { while(1);}
void WideTimer1B_Handler       (void) { while(1);}
void WideTimer2A_Handler       (void) { while(1);}
void WideTimer2B_Handler       (void) { while(1);}
void WideTimer3A_Handler       (void) { while(1);}
void WideTimer3B_Handler       (void) { while(1);}
void WideTimer4A_Handler       (void) { while(1);}
void WideTimer4B_Handler       (void) { while(1);}
void WideTimer5A_Handler       (void) { while(1);}
void WideTimer5B_Handler       (void) { while(1);}
void FPUException_Handler      (void) { while(1);}
void PWM1Gen0_Handler          (void) { while(1);}
void PWM1Gen1_Handler          (void) { while(1);}
void PWM1Gen2_Handler          (void) { while(1);}
void PWM1Gen3_Handler          (void) { while(1);}
void PWM1Fault_Handler         (void) { while(1);}

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

