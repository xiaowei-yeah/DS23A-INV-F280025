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

#ifndef BOARD_H
#define BOARD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//

#include "driverlib.h"
#include "device.h"

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************

//
// ANALOG -> myANALOGPinMux0 Pinmux
//

//
// EPWM2 -> ePWM_Ap Pinmux
//
//
// EPWM2_A - GPIO Settings
//
#define GPIO_PIN_EPWM2_A 2
#define ePWM_Ap_EPWMA_GPIO 2
#define ePWM_Ap_EPWMA_PIN_CONFIG GPIO_2_EPWM2_A
//
// EPWM2_B - GPIO Settings
//
#define GPIO_PIN_EPWM2_B 3
#define ePWM_Ap_EPWMB_GPIO 3
#define ePWM_Ap_EPWMB_PIN_CONFIG GPIO_3_EPWM2_B

//
// EPWM5 -> ePWM_Trigger Pinmux
//
//
// EPWM5_A - GPIO Settings
//
#define GPIO_PIN_EPWM5_A 16
#define ePWM_Trigger_EPWMA_GPIO 16
#define ePWM_Trigger_EPWMA_PIN_CONFIG GPIO_16_EPWM5_A
//
// EPWM5_B - GPIO Settings
//
#define GPIO_PIN_EPWM5_B 17
#define ePWM_Trigger_EPWMB_GPIO 17
#define ePWM_Trigger_EPWMB_PIN_CONFIG GPIO_17_EPWM5_B

//
// EPWM4 -> ePWM_Bp Pinmux
//
//
// EPWM4_A - GPIO Settings
//
#define GPIO_PIN_EPWM4_A 22
#define ePWM_Bp_EPWMA_GPIO 22
#define ePWM_Bp_EPWMA_PIN_CONFIG GPIO_22_EPWM4_A
//
// EPWM4_B - GPIO Settings
//
#define GPIO_PIN_EPWM4_B 23
#define ePWM_Bp_EPWMB_GPIO 23
#define ePWM_Bp_EPWMB_PIN_CONFIG GPIO_23_EPWM4_B
//
// GPIO5 - GPIO Settings
//
#define LED1_GPIO_PIN_CONFIG GPIO_5_GPIO5
//
// GPIO45 - GPIO Settings
//
#define LED2_GPIO_PIN_CONFIG GPIO_45_GPIO45
//
// GPIO41 - GPIO Settings
//
#define PWM_EN_GPIO_PIN_CONFIG GPIO_41_GPIO41
//
// GPIO4 - GPIO Settings
//
#define Key1_GPIO_PIN_CONFIG GPIO_4_GPIO4
//
// GPIO25 - GPIO Settings
//
#define Key2_GPIO_PIN_CONFIG GPIO_25_GPIO25
//
// GPIO40 - GPIO Settings
//
#define Key3_GPIO_PIN_CONFIG GPIO_40_GPIO40

//
// SCIA -> SCI_Modbus Pinmux
//
//
// SCIA_RX - GPIO Settings
//
#define GPIO_PIN_SCIA_RX 28
#define SCI_Modbus_SCIRX_GPIO 28
#define SCI_Modbus_SCIRX_PIN_CONFIG GPIO_28_SCIA_RX
//
// SCIA_TX - GPIO Settings
//
#define GPIO_PIN_SCIA_TX 29
#define SCI_Modbus_SCITX_GPIO 29
#define SCI_Modbus_SCITX_PIN_CONFIG GPIO_29_SCIA_TX

//*****************************************************************************
//
// ADC Configurations
//
//*****************************************************************************
#define ADC_A_BASE ADCA_BASE
#define ADC_A_RESULT_BASE ADCARESULT_BASE
#define ADC_A_SOC0 ADC_SOC_NUMBER0
#define ADC_A_FORCE_SOC0 ADC_FORCE_SOC0
#define ADC_A_SAMPLE_WINDOW_SOC0 150
#define ADC_A_TRIGGER_SOURCE_SOC0 ADC_TRIGGER_EPWM2_SOCA
#define ADC_A_CHANNEL_SOC0 ADC_CH_ADCIN6
void ADC_A_init();

#define ADC_C_BASE ADCC_BASE
#define ADC_C_RESULT_BASE ADCCRESULT_BASE
#define ADC_C_SOC0 ADC_SOC_NUMBER0
#define ADC_C_FORCE_SOC0 ADC_FORCE_SOC0
#define ADC_C_SAMPLE_WINDOW_SOC0 150
#define ADC_C_TRIGGER_SOURCE_SOC0 ADC_TRIGGER_EPWM2_SOCA
#define ADC_C_CHANNEL_SOC0 ADC_CH_ADCIN6
void ADC_C_init();


//*****************************************************************************
//
// ASYSCTL Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************
#define CpuTimer0_BASE CPUTIMER0_BASE
void CpuTimer0_init();

//*****************************************************************************
//
// DMA Configurations
//
//*****************************************************************************
extern const void *Dma_SourceAddr;
extern const void *Dma_DestinationAddr;
#define DMA_C_BASE DMA_CH1_BASE 
#define DMA_C_BURSTSIZE 16U
#define DMA_C_TRANSFERSIZE 2U
#define DMA_C_SRC_WRAPSIZE 16U
#define DMA_C_DEST_WRAPSIZE 32U
void DMA_C_init();

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
#define ePWM_Ap_BASE EPWM2_BASE
#define ePWM_Ap_TBPRD 2500
#define ePWM_Ap_COUNTER_MODE EPWM_COUNTER_MODE_UP_DOWN
#define ePWM_Ap_TBPHS 0
#define ePWM_Ap_CMPA 1000
#define ePWM_Ap_CMPB 0
#define ePWM_Ap_CMPC 0
#define ePWM_Ap_CMPD 0
#define ePWM_Ap_DBRED 100
#define ePWM_Ap_DBFED 100
#define ePWM_Ap_TZA_ACTION EPWM_TZ_ACTION_LOW
#define ePWM_Ap_TZB_ACTION EPWM_TZ_ACTION_LOW
#define ePWM_Ap_OSHT_SOURCES EPWM_TZ_SIGNAL_DCAEVT1
#define ePWM_Ap_TZ_INTERRUPT_SOURCES EPWM_TZ_INTERRUPT_DCAEVT1
#define ePWM_Ap_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define ePWM_Trigger_BASE EPWM5_BASE
#define ePWM_Trigger_TBPRD 500
#define ePWM_Trigger_COUNTER_MODE EPWM_COUNTER_MODE_UP_DOWN
#define ePWM_Trigger_TBPHS 2
#define ePWM_Trigger_CMPA 0
#define ePWM_Trigger_CMPB 0
#define ePWM_Trigger_CMPC 0
#define ePWM_Trigger_CMPD 0
#define ePWM_Trigger_DBRED 0
#define ePWM_Trigger_DBFED 0
#define ePWM_Trigger_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define ePWM_Trigger_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define ePWM_Trigger_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define ePWM_Bp_BASE EPWM4_BASE
#define ePWM_Bp_TBPRD 2500
#define ePWM_Bp_COUNTER_MODE EPWM_COUNTER_MODE_UP_DOWN
#define ePWM_Bp_TBPHS 2
#define ePWM_Bp_CMPA 1000
#define ePWM_Bp_CMPB 0
#define ePWM_Bp_CMPC 0
#define ePWM_Bp_CMPD 0
#define ePWM_Bp_DBRED 100
#define ePWM_Bp_DBFED 100
#define ePWM_Bp_TZA_ACTION EPWM_TZ_ACTION_LOW
#define ePWM_Bp_TZB_ACTION EPWM_TZ_ACTION_LOW
#define ePWM_Bp_OSHT_SOURCES EPWM_TZ_SIGNAL_DCAEVT1
#define ePWM_Bp_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
#define LED1 5
void LED1_init();
#define LED2 45
void LED2_init();
#define PWM_EN 41
void PWM_EN_init();
#define Key1 4
void Key1_init();
#define Key2 25
void Key2_init();
#define Key3 40
void Key3_init();

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for INT_ePWM_Ap_TZ
// ISR need to be defined for the registered interrupts
#define INT_ePWM_Ap_TZ INT_EPWM2_TZ
#define INT_ePWM_Ap_TZ_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP2
extern __interrupt void INT_ePWM_Ap_TZ_ISR(void);

// Interrupt Settings for INT_SCI_Modbus_RX
// ISR need to be defined for the registered interrupts
#define INT_SCI_Modbus_RX INT_SCIA_RX
#define INT_SCI_Modbus_RX_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP9
extern __interrupt void INT_SCI_Modbus_RX_ISR(void);

// Interrupt Settings for INT_SCI_Modbus_TX
// ISR need to be defined for the registered interrupts
#define INT_SCI_Modbus_TX INT_SCIA_TX
#define INT_SCI_Modbus_TX_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP9
extern __interrupt void INT_SCI_Modbus_TX_ISR(void);

//*****************************************************************************
//
// SCI Configurations
//
//*****************************************************************************
#define SCI_Modbus_BASE SCIA_BASE
#define SCI_Modbus_BAUDRATE 9600
#define SCI_Modbus_CONFIG_WLEN SCI_CONFIG_WLEN_8
#define SCI_Modbus_CONFIG_STOP SCI_CONFIG_STOP_ONE
#define SCI_Modbus_CONFIG_PAR SCI_CONFIG_PAR_NONE
#define SCI_Modbus_FIFO_TX_LVL SCI_FIFO_TX0
#define SCI_Modbus_FIFO_RX_LVL SCI_FIFO_RX1
void SCI_Modbus_init();

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void	Board_init();
void	ADC_init();
void	ASYSCTL_init();
void	CPUTIMER_init();
void	DMA_init();
void	EPWM_init();
void	GPIO_init();
void	INTERRUPT_init();
void	SCI_init();
void	SYNC_init();
void	PinMux_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
