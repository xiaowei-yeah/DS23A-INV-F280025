/*
* File: 	sci.c
* Date: 	2026年5月15日
* Author: 	jinjiale

* Description: 	
* Version: 		
*/
//------------------------------------------Include----------------------------------------

#include <device.h>
#include <driverlib.h>
#include <board.h>
#include "mb.h"

//-------------------------------------------Macro-----------------------------------------
#define TX_FIFO_SIZE  256
//------------------------------------Function declaration---------------------------------

//--------------------------------------Struct And Type------------------------------------
extern MB_t mb;
//-------------------------------------------Value-----------------------------------------
static uint8_t  txFifo[TX_FIFO_SIZE];
static volatile uint16_t txRd = 0;
static volatile uint16_t txWr = 0;
static volatile uint16_t txBusy = 0;   // 1 = 正在发送中

extern uint16_t gModbusOutTime_Cnt;
//------------------------------------Function definition----------------------------------

/****************************************************************
* Function: 
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
/* ========== 发送 FIFO + 中断 (非阻塞) ========== */
void Sci_SendBuf(const uint8_t *data, uint16_t len)
{
    /* 将整帧数据写入 FIFO (主循环调用, 非 ISR, 无需关中断) */
    for (uint16_t i = 0; i < len; i++) {
        txFifo[txWr] = data[i];
        txWr = (txWr + 1) % TX_FIFO_SIZE;
    }

    /* 使能 TX 中断, 由 TX ISR 逐字节取出发送 */
    if (!txBusy) {
        txBusy = 1;
        SciaRegs.SCIFFTX.bit.TXFFIENA = 1;  // 使能 SCI TX 中断
    }
}

/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
#pragma CODE_SECTION(INT_SCI_Modbus_RX_ISR,".TI.ramfunc");
__interrupt void INT_SCI_Modbus_RX_ISR(void)
{
    gModbusOutTime_Cnt = 0;
    uint16_t rxWord = SciaRegs.SCIRXBUF.all;  // 读取接收缓冲区 (16位)
    MB_FeedByte(&mb, (uint8_t)(rxWord & 0xFF)); // 取低 8 位喂入库

    SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}
/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
#pragma CODE_SECTION(INT_SCI_Modbus_TX_ISR,".TI.ramfunc");
__interrupt void INT_SCI_Modbus_TX_ISR(void)
{

    if (txRd != txWr) {
        /* FIFO 中还有数据, 取出一个字节发送 */
        SciaRegs.SCITXBUF.all = (uint16_t)txFifo[txRd];
        txRd = (txRd + 1) % TX_FIFO_SIZE;
    } else {
        /* FIFO 空, 关闭 TX 中断, 切回接收模式 */
        SciaRegs.SCIFFTX.bit.TXFFIENA = 0;
        txBusy = 0;
    }

    SciaRegs.SCIFFTX.bit.TXFFINTCLR=1;  // Clear SCI Interrupt flag
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}


//--------------------------------------end of this file-----------------------------------
