/*
 * mb.c - Modbus RTU Slave Library Public API Implementation
 *
 * Thin wrappers that delegate to the FSM (mb_fsm.c).
 */

#include "mb_internal.h"

void MB_Init(MB_t *mb, uint8_t slaveAddr)
{
    if (!mb) return;
    mb->slaveAddr       = slaveAddr;
    mb->cbReadHolding   = (MB_RegReadCb)0;
    mb->cbReadInput     = (MB_RegReadCb)0;
    mb->cbWriteHolding  = (MB_RegWriteCb)0;
    mb->cbSendBuf       = (MB_SendBufCb)0;
    mb->cbTxDone        = (MB_TxDoneCb)0;
    mb->eventFlags      = 0;
    MB_FSM_Init(mb);
}

void MB_RegisterCallbacks(MB_t *mb,
                          MB_RegReadCb  readHolding,
                          MB_RegReadCb  readInput,
                          MB_RegWriteCb writeHolding,
                          MB_SendBufCb  sendBuf,
                          MB_TxDoneCb   txDone)
{
    if (!mb) return;
    mb->cbReadHolding  = readHolding;
    mb->cbReadInput    = readInput;
    mb->cbWriteHolding = writeHolding;
    mb->cbSendBuf      = sendBuf;
    mb->cbTxDone       = txDone;
}

void MB_FeedByte(MB_t *mb, uint8_t byte)
{
    if (!mb) return;
    MB_FSM_FeedByte(mb, byte);
}

void MB_SignalEvent(MB_t *mb, MB_Event evt)
{
    if (!mb) return;
    mb->eventFlags |= (uint8_t)evt;
}

MB_State MB_Poll(MB_t *mb)
{
    if (!mb) return MB_STATE_IDLE;

    if (mb->eventFlags & MB_EVT_TIMEOUT) {
        mb->eventFlags &= ~MB_EVT_TIMEOUT;
        MB_FSM_ProcessEvent(mb, MB_EVT_TIMEOUT);
    }

    if (mb->state == MB_STATE_RESPONDING && mb->txLen > 0) {
        if (mb->cbSendBuf) {
            mb->cbSendBuf(mb->txBuf, mb->txLen);
        }
        mb->txLen = 0;
        mb->txPos = 0;
        mb->state = MB_STATE_IDLE;
        if (mb->cbTxDone) {
            mb->cbTxDone();
        }
    }

    return mb->state;
}

MB_State MB_GetState(const MB_t *mb)
{
    if (!mb) return MB_STATE_IDLE;
    return mb->state;
}

const char *MB_ExceptionStr(MB_Exception ex)
{
    switch (ex) {
    case MB_EX_NONE:             return "OK";
    case MB_EX_ILLEGAL_FUNCTION: return "Illegal Function";
    case MB_EX_ILLEGAL_ADDRESS:  return "Illegal Address";
    case MB_EX_ILLEGAL_VALUE:    return "Illegal Value";
    case MB_EX_SLAVE_FAILURE:    return "Slave Failure";
    default:                     return "Unknown";
    }
}
