/*
 * Copyright (c) 2020 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "board.h"

//*****************************************************************************
//
// Board Configurations
// Initializes the rest of the modules. 
// Call this function in your application if you wish to do all module 
// initialization.
// If you wish to not use some of the initializations, instead of the 
// Board_init use the individual Module_inits
//
//*****************************************************************************
void Board_init()
{
	EALLOW;

	PinMux_init();
	SYNC_init();
	ASYSCTL_init();
	ADC_init();
	CPUTIMER_init();
	DMA_init();
	EPWM_init();
	GPIO_init();
	INTERRUPT_init();

	EDIS;
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
	//
	// PinMux for modules assigned to CPU1
	//
	
	//
	// ANALOG -> myANALOGPinMux0 Pinmux
	//
	// Analog PinMux for A0/C15
	GPIO_setPinConfig(GPIO_231_GPIO231);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(231, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A1
	GPIO_setPinConfig(GPIO_232_GPIO232);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(232, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A10/C10
	GPIO_setPinConfig(GPIO_230_GPIO230);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(230, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A11/C0
	GPIO_setPinConfig(GPIO_237_GPIO237);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(237, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A12/C1
	GPIO_setPinConfig(GPIO_238_GPIO238);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(238, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A14/C4
	GPIO_setPinConfig(GPIO_239_GPIO239);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(239, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A15/C7
	GPIO_setPinConfig(GPIO_233_GPIO233);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(233, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A2/C9
	GPIO_setPinConfig(GPIO_224_GPIO224);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(224, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A3/C5/VDAC
	GPIO_setPinConfig(GPIO_242_GPIO242);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(242, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A4/C14
	GPIO_setPinConfig(GPIO_225_GPIO225);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(225, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A5/C2
	GPIO_setPinConfig(GPIO_244_GPIO244);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(244, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A6
	GPIO_setPinConfig(GPIO_228_GPIO228);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(228, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A7/C3
	GPIO_setPinConfig(GPIO_245_GPIO245);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(245, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A8/C11
	GPIO_setPinConfig(GPIO_241_GPIO241);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(241, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A9/C8
	GPIO_setPinConfig(GPIO_227_GPIO227);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(227, GPIO_ANALOG_ENABLED);
	// Analog PinMux for C6
	GPIO_setPinConfig(GPIO_226_GPIO226);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(226, GPIO_ANALOG_ENABLED);
	//
	// EPWM2 -> ePWM_Ap Pinmux
	//
	GPIO_setPinConfig(ePWM_Ap_EPWMA_PIN_CONFIG);
	GPIO_setPadConfig(ePWM_Ap_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(ePWM_Ap_EPWMA_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(ePWM_Ap_EPWMB_PIN_CONFIG);
	GPIO_setPadConfig(ePWM_Ap_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(ePWM_Ap_EPWMB_GPIO, GPIO_QUAL_SYNC);

	//
	// EPWM5 -> ePWM_Trigger Pinmux
	//
	GPIO_setPinConfig(ePWM_Trigger_EPWMA_PIN_CONFIG);
	GPIO_setPadConfig(ePWM_Trigger_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(ePWM_Trigger_EPWMA_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(ePWM_Trigger_EPWMB_PIN_CONFIG);
	GPIO_setPadConfig(ePWM_Trigger_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(ePWM_Trigger_EPWMB_GPIO, GPIO_QUAL_SYNC);

	//
	// EPWM4 -> ePWM_Bp Pinmux
	//
	GPIO_setPinConfig(ePWM_Bp_EPWMA_PIN_CONFIG);
	GPIO_setPadConfig(ePWM_Bp_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(ePWM_Bp_EPWMA_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(ePWM_Bp_EPWMB_PIN_CONFIG);
	GPIO_setPadConfig(ePWM_Bp_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(ePWM_Bp_EPWMB_GPIO, GPIO_QUAL_SYNC);

	// GPIO5 -> LED1 Pinmux
	GPIO_setPinConfig(GPIO_5_GPIO5);
	// GPIO45 -> LED2 Pinmux
	GPIO_setPinConfig(GPIO_45_GPIO45);
	// GPIO41 -> PWM_EN Pinmux
	GPIO_setPinConfig(GPIO_41_GPIO41);
	// GPIO4 -> Key1 Pinmux
	GPIO_setPinConfig(GPIO_4_GPIO4);
	// GPIO25 -> Key2 Pinmux
	GPIO_setPinConfig(GPIO_25_GPIO25);
	// GPIO40 -> Key3 Pinmux
	GPIO_setPinConfig(GPIO_40_GPIO40);

}

//*****************************************************************************
//
// ADC Configurations
//
//*****************************************************************************
void ADC_init(){
	ADC_A_init();
}

void ADC_A_init(){
	//
	// ADC Initialization: Write ADC configurations and power up the ADC
	//
	// Set the analog voltage reference selection and ADC module's offset trims.
	// This function sets the analog voltage reference to internal (with the reference voltage of 1.65V or 2.5V) or external for ADC
	// which is same as ASysCtl APIs.
	//
	ADC_setVREF(ADC_A_BASE, ADC_REFERENCE_EXTERNAL, ADC_REFERENCE_2_5V);
	//
	// Configures the analog-to-digital converter module prescaler.
	//
	ADC_setPrescaler(ADC_A_BASE, ADC_CLK_DIV_2_0);
	//
	// Sets the timing of the end-of-conversion pulse
	//
	ADC_setInterruptPulseMode(ADC_A_BASE, ADC_PULSE_END_OF_CONV);
	//
	// Powers up the analog-to-digital converter core.
	//
	ADC_enableConverter(ADC_A_BASE);
	//
	// Delay for 1ms to allow ADC time to power up
	//
	DEVICE_DELAY_US(500);
	//
	// SOC Configuration: Setup ADC EPWM channel and trigger settings
	//
	// Disables SOC burst mode.
	//
	ADC_disableBurstMode(ADC_A_BASE);
	//
	// Sets the priority mode of the SOCs.
	//
	ADC_setSOCPriority(ADC_A_BASE, ADC_PRI_ALL_ROUND_ROBIN);
	//
	// Start of Conversion 0 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 0
	//	  	Trigger			: ADC_TRIGGER_EPWM2_SOCA
	//	  	Channel			: ADC_CH_ADCIN6
	//	 	Sample Window	: 15 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(ADC_A_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM2_SOCA, ADC_CH_ADCIN6, 15U);
	ADC_setInterruptSOCTrigger(ADC_A_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
	//
	// ADC Interrupt 1 Configuration
	// 		Source	: ADC_SOC_NUMBER0
	// 		Interrupt Source: enabled
	//		Continuous Mode	: enabled
	//
	//
	ADC_setInterruptSource(ADC_A_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
	ADC_clearInterruptStatus(ADC_A_BASE, ADC_INT_NUMBER1);
	ADC_enableContinuousMode(ADC_A_BASE, ADC_INT_NUMBER1);
	ADC_enableInterrupt(ADC_A_BASE, ADC_INT_NUMBER1);
}


//*****************************************************************************
//
// ASYSCTL Configurations
//
//*****************************************************************************
void ASYSCTL_init(){
	//
	// asysctl initialization
	//
	// Disables the temperature sensor output to the ADC.
	//
	ASysCtl_disableTemperatureSensor();
	//
	// Set the analog voltage reference selection to external.
	//
	ASysCtl_setAnalogReferenceExternal( ASYSCTL_VREFHIA | ASYSCTL_VREFHIC );
}

//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************
void CPUTIMER_init(){
	CpuTimer0_init();
}

void CpuTimer0_init(){
	CPUTimer_setEmulationMode(CpuTimer0_BASE, CPUTIMER_EMULATIONMODE_RUNFREE);
	CPUTimer_setPreScaler(CpuTimer0_BASE, 99U);
	CPUTimer_setPeriod(CpuTimer0_BASE, 999U);
	CPUTimer_disableInterrupt(CpuTimer0_BASE);
	CPUTimer_stopTimer(CpuTimer0_BASE);

	CPUTimer_reloadTimerCounter(CpuTimer0_BASE);
	CPUTimer_startTimer(CpuTimer0_BASE);
}

//*****************************************************************************
//
// DMA Configurations
//
//*****************************************************************************
void DMA_init(){
    DMA_initController();
	DMA_A_init();
}

void DMA_A_init(){
    DMA_setEmulationMode(DMA_EMULATION_FREE_RUN);
    DMA_configAddresses(DMA_A_BASE, Dma_DestinationAddr, Dma_SourceAddr);
    DMA_configBurst(DMA_A_BASE, 16U, 1, 1);
    DMA_configTransfer(DMA_A_BASE, 2U, -15, 1);
    DMA_configWrap(DMA_A_BASE, 16U, 0, 32U, 0);
    DMA_configMode(DMA_A_BASE, DMA_TRIGGER_ADCA1, DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_ENABLE | DMA_CFG_SIZE_16BIT);
    DMA_setInterruptMode(DMA_A_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_A_BASE);
    DMA_disableOverrunInterrupt(DMA_A_BASE);
    DMA_enableTrigger(DMA_A_BASE);
    DMA_startChannel(DMA_A_BASE);
}

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
void EPWM_init(){
    EPWM_setClockPrescaler(ePWM_Ap_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(ePWM_Ap_BASE, 2500);	
    EPWM_setTimeBaseCounter(ePWM_Ap_BASE, 0);	
    EPWM_setTimeBaseCounterMode(ePWM_Ap_BASE, EPWM_COUNTER_MODE_UP_DOWN);	
    EPWM_setCountModeAfterSync(ePWM_Ap_BASE, EPWM_COUNT_MODE_UP_AFTER_SYNC);	
    EPWM_disablePhaseShiftLoad(ePWM_Ap_BASE);	
    EPWM_setPhaseShift(ePWM_Ap_BASE, 0);	
    EPWM_setSyncInPulseSource(ePWM_Ap_BASE, EPWM_SYNC_IN_PULSE_SRC_DISABLE);	
    EPWM_enableSyncOutPulseSource(ePWM_Ap_BASE, EPWM_SYNC_OUT_PULSE_ON_CNTR_ZERO);	
    EPWM_setSyncPulseSource(ePWM_Ap_BASE, HRPWM_PWMSYNC_SOURCE_ZERO);	
    EPWM_setCounterCompareValue(ePWM_Ap_BASE, EPWM_COUNTER_COMPARE_A, 1000);	
    EPWM_setCounterCompareShadowLoadMode(ePWM_Ap_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);	
    EPWM_setCounterCompareValue(ePWM_Ap_BASE, EPWM_COUNTER_COMPARE_B, 0);	
    EPWM_setCounterCompareShadowLoadMode(ePWM_Ap_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_disableActionQualifierShadowLoadMode(ePWM_Ap_BASE, EPWM_ACTION_QUALIFIER_A);	
    EPWM_setActionQualifierShadowLoadMode(ePWM_Ap_BASE, EPWM_ACTION_QUALIFIER_A, EPWM_AQ_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_disableActionQualifierShadowLoadMode(ePWM_Ap_BASE, EPWM_ACTION_QUALIFIER_B);	
    EPWM_setActionQualifierShadowLoadMode(ePWM_Ap_BASE, EPWM_ACTION_QUALIFIER_B, EPWM_AQ_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(ePWM_Ap_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setDeadBandDelayPolarity(ePWM_Ap_BASE, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);	
    EPWM_setDeadBandDelayMode(ePWM_Ap_BASE, EPWM_DB_RED, true);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(ePWM_Ap_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(ePWM_Ap_BASE);	
    EPWM_setRisingEdgeDelayCount(ePWM_Ap_BASE, 100);	
    EPWM_setDeadBandDelayMode(ePWM_Ap_BASE, EPWM_DB_FED, true);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(ePWM_Ap_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(ePWM_Ap_BASE);	
    EPWM_setFallingEdgeDelayCount(ePWM_Ap_BASE, 100);	
    EPWM_setTripZoneAction(ePWM_Ap_BASE, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(ePWM_Ap_BASE, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(ePWM_Ap_BASE, EPWM_TZ_ACTION_EVENT_DCAEVT1, EPWM_TZ_ACTION_DISABLE);	
    EPWM_setTripZoneAction(ePWM_Ap_BASE, EPWM_TZ_ACTION_EVENT_DCAEVT2, EPWM_TZ_ACTION_DISABLE);	
    EPWM_setTripZoneAction(ePWM_Ap_BASE, EPWM_TZ_ACTION_EVENT_DCBEVT1, EPWM_TZ_ACTION_DISABLE);	
    EPWM_setTripZoneAction(ePWM_Ap_BASE, EPWM_TZ_ACTION_EVENT_DCBEVT2, EPWM_TZ_ACTION_DISABLE);	
    EPWM_enableTripZoneSignals(ePWM_Ap_BASE, EPWM_TZ_SIGNAL_DCAEVT1);	
    EPWM_enableTripZoneInterrupt(ePWM_Ap_BASE, EPWM_TZ_INTERRUPT_DCAEVT1);	
    EPWM_enableADCTrigger(ePWM_Ap_BASE, EPWM_SOC_A);	
    EPWM_setADCTriggerSource(ePWM_Ap_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO_OR_PERIOD);	
    EPWM_setADCTriggerEventPrescale(ePWM_Ap_BASE, EPWM_SOC_A, 1);	
    EPWM_enableADCTrigger(ePWM_Ap_BASE, EPWM_SOC_B);	
    EPWM_setADCTriggerSource(ePWM_Ap_BASE, EPWM_SOC_B, EPWM_SOC_TBCTR_ZERO);	
    EPWM_setClockPrescaler(ePWM_Trigger_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(ePWM_Trigger_BASE, 500);	
    EPWM_setTimeBaseCounter(ePWM_Trigger_BASE, 0);	
    EPWM_setTimeBaseCounterMode(ePWM_Trigger_BASE, EPWM_COUNTER_MODE_UP_DOWN);	
    EPWM_setCountModeAfterSync(ePWM_Trigger_BASE, EPWM_COUNT_MODE_UP_AFTER_SYNC);	
    EPWM_enablePhaseShiftLoad(ePWM_Trigger_BASE);	
    EPWM_setPhaseShift(ePWM_Trigger_BASE, 2);	
    EPWM_setSyncInPulseSource(ePWM_Trigger_BASE, EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM2);	
    EPWM_setSyncPulseSource(ePWM_Trigger_BASE, HRPWM_PWMSYNC_SOURCE_ZERO);	
    EPWM_setCounterCompareValue(ePWM_Trigger_BASE, EPWM_COUNTER_COMPARE_A, 0);	
    EPWM_setCounterCompareShadowLoadMode(ePWM_Trigger_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(ePWM_Trigger_BASE, EPWM_COUNTER_COMPARE_B, 0);	
    EPWM_setCounterCompareShadowLoadMode(ePWM_Trigger_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_disableActionQualifierShadowLoadMode(ePWM_Trigger_BASE, EPWM_ACTION_QUALIFIER_A);	
    EPWM_setActionQualifierShadowLoadMode(ePWM_Trigger_BASE, EPWM_ACTION_QUALIFIER_A, EPWM_AQ_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(ePWM_Trigger_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(ePWM_Trigger_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(ePWM_Trigger_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(ePWM_Trigger_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(ePWM_Trigger_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(ePWM_Trigger_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_disableActionQualifierShadowLoadMode(ePWM_Trigger_BASE, EPWM_ACTION_QUALIFIER_B);	
    EPWM_setActionQualifierShadowLoadMode(ePWM_Trigger_BASE, EPWM_ACTION_QUALIFIER_B, EPWM_AQ_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(ePWM_Trigger_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(ePWM_Trigger_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(ePWM_Trigger_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(ePWM_Trigger_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(ePWM_Trigger_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(ePWM_Trigger_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(ePWM_Trigger_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(ePWM_Trigger_BASE);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(ePWM_Trigger_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(ePWM_Trigger_BASE);	
    EPWM_enableADCTrigger(ePWM_Trigger_BASE, EPWM_SOC_A);	
    EPWM_setADCTriggerSource(ePWM_Trigger_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO_OR_PERIOD);	
    EPWM_setADCTriggerEventPrescale(ePWM_Trigger_BASE, EPWM_SOC_A, 5);	
    EPWM_enableADCTrigger(ePWM_Trigger_BASE, EPWM_SOC_B);	
    EPWM_setADCTriggerSource(ePWM_Trigger_BASE, EPWM_SOC_B, EPWM_SOC_TBCTR_ZERO);	
    EPWM_setADCTriggerEventPrescale(ePWM_Trigger_BASE, EPWM_SOC_B, 5);	
    EPWM_setClockPrescaler(ePWM_Bp_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(ePWM_Bp_BASE, 2500);	
    EPWM_setTimeBaseCounter(ePWM_Bp_BASE, 0);	
    EPWM_setTimeBaseCounterMode(ePWM_Bp_BASE, EPWM_COUNTER_MODE_UP_DOWN);	
    EPWM_setCountModeAfterSync(ePWM_Bp_BASE, EPWM_COUNT_MODE_UP_AFTER_SYNC);	
    EPWM_enablePhaseShiftLoad(ePWM_Bp_BASE);	
    EPWM_setPhaseShift(ePWM_Bp_BASE, 2);	
    EPWM_setSyncInPulseSource(ePWM_Bp_BASE, EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM2);	
    EPWM_setSyncPulseSource(ePWM_Bp_BASE, HRPWM_PWMSYNC_SOURCE_ZERO);	
    EPWM_setCounterCompareValue(ePWM_Bp_BASE, EPWM_COUNTER_COMPARE_A, 1000);	
    EPWM_setCounterCompareShadowLoadMode(ePWM_Bp_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);	
    EPWM_setCounterCompareValue(ePWM_Bp_BASE, EPWM_COUNTER_COMPARE_B, 0);	
    EPWM_setCounterCompareShadowLoadMode(ePWM_Bp_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_disableActionQualifierShadowLoadMode(ePWM_Bp_BASE, EPWM_ACTION_QUALIFIER_A);	
    EPWM_setActionQualifierShadowLoadMode(ePWM_Bp_BASE, EPWM_ACTION_QUALIFIER_A, EPWM_AQ_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(ePWM_Bp_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(ePWM_Bp_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(ePWM_Bp_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(ePWM_Bp_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(ePWM_Bp_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(ePWM_Bp_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_disableActionQualifierShadowLoadMode(ePWM_Bp_BASE, EPWM_ACTION_QUALIFIER_B);	
    EPWM_setActionQualifierShadowLoadMode(ePWM_Bp_BASE, EPWM_ACTION_QUALIFIER_B, EPWM_AQ_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(ePWM_Bp_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(ePWM_Bp_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(ePWM_Bp_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(ePWM_Bp_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(ePWM_Bp_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(ePWM_Bp_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setDeadBandDelayPolarity(ePWM_Bp_BASE, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);	
    EPWM_setDeadBandDelayMode(ePWM_Bp_BASE, EPWM_DB_RED, true);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(ePWM_Bp_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(ePWM_Bp_BASE);	
    EPWM_setRisingEdgeDelayCount(ePWM_Bp_BASE, 100);	
    EPWM_setDeadBandDelayMode(ePWM_Bp_BASE, EPWM_DB_FED, true);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(ePWM_Bp_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(ePWM_Bp_BASE);	
    EPWM_setFallingEdgeDelayCount(ePWM_Bp_BASE, 100);	
    EPWM_setTripZoneAction(ePWM_Bp_BASE, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(ePWM_Bp_BASE, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(ePWM_Bp_BASE, EPWM_TZ_ACTION_EVENT_DCAEVT1, EPWM_TZ_ACTION_DISABLE);	
    EPWM_setTripZoneAction(ePWM_Bp_BASE, EPWM_TZ_ACTION_EVENT_DCAEVT2, EPWM_TZ_ACTION_DISABLE);	
    EPWM_setTripZoneAction(ePWM_Bp_BASE, EPWM_TZ_ACTION_EVENT_DCBEVT1, EPWM_TZ_ACTION_DISABLE);	
    EPWM_setTripZoneAction(ePWM_Bp_BASE, EPWM_TZ_ACTION_EVENT_DCBEVT2, EPWM_TZ_ACTION_DISABLE);	
    EPWM_enableTripZoneSignals(ePWM_Bp_BASE, EPWM_TZ_SIGNAL_DCAEVT1);	
    EPWM_enableADCTrigger(ePWM_Bp_BASE, EPWM_SOC_A);	
    EPWM_setADCTriggerSource(ePWM_Bp_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO_OR_PERIOD);	
    EPWM_enableADCTrigger(ePWM_Bp_BASE, EPWM_SOC_B);	
    EPWM_setADCTriggerSource(ePWM_Bp_BASE, EPWM_SOC_B, EPWM_SOC_TBCTR_ZERO);	
}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init(){
	LED1_init();
	LED2_init();
	PWM_EN_init();
	Key1_init();
	Key2_init();
	Key3_init();
}

void LED1_init(){
	GPIO_setPadConfig(LED1, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(LED1, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(LED1, GPIO_DIR_MODE_OUT);
}
void LED2_init(){
	GPIO_setPadConfig(LED2, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(LED2, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(LED2, GPIO_DIR_MODE_OUT);
}
void PWM_EN_init(){
	GPIO_writePin(PWM_EN, 1);
	GPIO_setPadConfig(PWM_EN, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(PWM_EN, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(PWM_EN, GPIO_DIR_MODE_OUT);
}
void Key1_init(){
	GPIO_setPadConfig(Key1, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(Key1, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(Key1, GPIO_DIR_MODE_IN);
}
void Key2_init(){
	GPIO_setPadConfig(Key2, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(Key2, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(Key2, GPIO_DIR_MODE_IN);
}
void Key3_init(){
	GPIO_setPadConfig(Key3, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(Key3, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(Key3, GPIO_DIR_MODE_IN);
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init(){
	
	// Interrupt Settings for INT_DMA_A
	// ISR need to be defined for the registered interrupts
	Interrupt_register(INT_DMA_A, &INT_DMA_A_ISR);
	Interrupt_enable(INT_DMA_A);
	
	// Interrupt Settings for INT_ePWM_Ap_TZ
	// ISR need to be defined for the registered interrupts
	Interrupt_register(INT_ePWM_Ap_TZ, &INT_ePWM_Ap_TZ_ISR);
	Interrupt_enable(INT_ePWM_Ap_TZ);
	
	// Interrupt Settings for INT_ADC_A_1
	// ISR need to be defined for the registered interrupts
	Interrupt_register(INT_ADC_A_1, &INT_ADC_A_1_ISR);
	Interrupt_enable(INT_ADC_A_1);
}
//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************
void SYNC_init(){
	SysCtl_setSyncOutputConfig(SYSCTL_SYNC_OUT_SRC_EPWM1SYNCOUT);
	//
	// SOCA
	//
	SysCtl_enableExtADCSOCSource(0);
	//
	// SOCB
	//
	SysCtl_enableExtADCSOCSource(0);
}
