/*
* File:     samp.c
* Date:     2025Äê10ÔÂ14ÈÕ
* Author:   jin

* Description:
* Version:
*/

//--------------------------------------include-----------------------------------------

#include "projectall.h"

//---------------------------------------Macro-----------------------------------------

//--------------------------------Function declaration---------------------------------

//----------------------------------Value declaration----------------------------------

//----------------------------------Value definition-----------------------------------

//--------------------------------Function definition----------------------------------
/****************************************************************
* Function:     ADC____ISR
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
#pragma CODE_SECTION(INT_ADC_A_1_ISR,".TI.ramfunc");
__interrupt void INT_ADC_A_1_ISR(void)
{

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}



/****************************************************************
* Function:     DMA____ISR
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
#pragma CODE_SECTION(INT_DMA_A_ISR,".TI.ramfunc");
__interrupt void INT_DMA_A_ISR(void)
{

    samp_UpdateAll();

    FaultIsrTask();

    dcac_Func(samp_getReal(eCurr_OutA),samp_getReal(eVolt_OutA),samp_getReal(eVolt_InA));

    samp_RmsFunc(eVolt_OutA);

    static uint16_t cnt = 0;
    if(cnt>=400)cnt=0;
    ADCBuff1[cnt] = samp_getReal(eVolt_OutA);
    cnt++;


    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}


/****************************************************************
* Function:     TZ_____ISR
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
#pragma CODE_SECTION(INT_ePWM_Ap_TZ_ISR,".TI.ramfunc");
__interrupt void INT_ePWM_Ap_TZ_ISR(void)
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP2);
}

//---------------------------------------------end of this file----------------------------------------------
