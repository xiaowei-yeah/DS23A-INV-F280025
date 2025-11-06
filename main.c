/*
* File:     main.c
* Date:     2025Äê9ÔÂ29ÈÕ
* Author:   jin

* Description:
* Version:
*/
//
// Included Files
//
#include "projectall.h"


extern void tick_Update(void);
extern void key_Init();
//
// Main
//
void main(void)
{
    //
    // Initializes system control, device clock, and peripherals
    //


    Device_init();

    //
    // Initializes PIE and clear PIE registers. Disables CPU interrupts.
    // and clear all CPU interrupt flags.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();


    //
    // Board Initialization
    //
    Board_init();

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);



    GlobalsVarInit();

    samp_Init();

    key_Init();
    dcac_Init();

    Scheduler_Setup();

    //
    // Enables CPU interrupts
    //
    Interrupt_enableMaster();

    //
    // Loop.
    //
    for(;;)
    {
        tick_Update();
        Scheduler_Run();
    }
}



//
// End of File
//
