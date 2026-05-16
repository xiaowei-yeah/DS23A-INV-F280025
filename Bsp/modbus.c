/*
* File: 	modbus.c
* Date: 	2026年5月15日
* Author: 	jinjiale

* Description: 	
* Version: 		
*/
//------------------------------------------Include----------------------------------------

#include "mb.h"

//-------------------------------------------Macro-----------------------------------------

#define HOLD_REG_COUNT  300
#define INPUT_REG_COUNT 300

//------------------------------------Function declaration---------------------------------
static MB_Exception ReadHolding(uint16_t addr, uint16_t *buf, uint16_t count);
static MB_Exception ReadInput(uint16_t addr, uint16_t *buf, uint16_t count);
static MB_Exception WriteHolding(uint16_t addr, const uint16_t *buf, uint16_t count);
extern void Sci_SendBuf(const uint8_t *data, uint16_t len);
//--------------------------------------Struct And Type------------------------------------

MB_t mb;
static uint16_t holdRegs[HOLD_REG_COUNT];
static uint16_t inputRegs[INPUT_REG_COUNT];

//-------------------------------------------Value-----------------------------------------

uint16_t gModbusOutTime_Cnt = 0;
#define  mOutTimeCntNmber   (4)

//------------------------------------Function definition----------------------------------

/****************************************************************
* Function: 
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void Modbus_Init(MB_t *mb)
{
    /* Modbus 初始化 */
    MB_Init(mb, 0x02);
    MB_RegisterCallbacks(mb,
                         ReadHolding,
                         ReadInput,
                         WriteHolding,
                         Sci_SendBuf,
                         NULL);
}
/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void ModbusOutTime_CounterChk(MB_t *mb)
{
    if (MB_GetState(mb) == MB_STATE_RECEIVING)
    {
        gModbusOutTime_Cnt++;
        if(gModbusOutTime_Cnt >= mOutTimeCntNmber)
        {
            gModbusOutTime_Cnt = 0;
            MB_SignalEvent(mb, MB_EVT_TIMEOUT);  // 帧完成
        }
    }
}


/* ========== 寄存器回调 ========== */

/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
static MB_Exception ReadHolding(uint16_t addr, uint16_t *buf, uint16_t count)
{
    if (addr + count > HOLD_REG_COUNT) return MB_EX_ILLEGAL_ADDRESS;
    for (uint16_t i = 0; i < count; i++) {
        buf[i] = holdRegs[addr + i];
    }
    return MB_EX_NONE;
}

static MB_Exception ReadInput(uint16_t addr, uint16_t *buf, uint16_t count)
{
    if (addr + count > INPUT_REG_COUNT) return MB_EX_ILLEGAL_ADDRESS;
    for (uint16_t i = 0; i < count; i++) {
        buf[i] = inputRegs[addr + i];
    }
    return MB_EX_NONE;
}

static MB_Exception WriteHolding(uint16_t addr, const uint16_t *buf, uint16_t count)
{
    if (addr + count > HOLD_REG_COUNT) return MB_EX_ILLEGAL_ADDRESS;
    for (uint16_t i = 0; i < count; i++) {
        holdRegs[addr + i] = buf[i];
    }
    return MB_EX_NONE;
}




//--------------------------------------end of this file-----------------------------------
