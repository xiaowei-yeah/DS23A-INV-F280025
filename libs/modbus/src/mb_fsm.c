/*
 * mb_fsm.c - Modbus RTU Slave State Machine
 *
 * States: IDLE -> RECEIVING -> FRAME_READY -> PROCESSING -> RESPONDING -> IDLE
 *
 * The library never blocks. State transitions are driven by:
 *   - MB_FeedByte():            stores received byte
 *   - MB_SignalEvent(MB_EVT_TIMEOUT): user signals 3.5T silence, frame is complete
 */

#include "mb_internal.h"
#include <string.h>

/* ---- Internal helpers ---- */

static int IsValidFC(uint8_t fc)
{
    switch (fc) {
#ifdef MB_CFG_FC03_ENABLE
    case 0x03: return 1;
#endif
#ifdef MB_CFG_FC04_ENABLE
    case 0x04: return 1;
#endif
#ifdef MB_CFG_FC06_ENABLE
    case 0x06: return 1;
#endif
#ifdef MB_CFG_FC16_ENABLE
    case 0x10: return 1;
#endif
#ifdef MB_CFG_FC23_ENABLE
    case 0x17: return 1;
#endif
    default: return 0;
    }
}

static int IsBroadcast(const MB_t *mb)
{
#ifdef MB_CFG_BROADCAST_ENABLE
    return (mb->rxBuf[0] == 0x00);
#else
    (void)mb;
    return 0;
#endif
}

/* Check if address is for us or broadcast */
static int AddressMatch(const MB_t *mb)
{
    uint8_t addr = mb->rxBuf[0];
    if (addr == mb->slaveAddr) return 1;
#ifdef MB_CFG_BROADCAST_ENABLE
    if (addr == 0x00) return 1;
#endif
    return 0;
}

/* Validate CRC of received frame. Frame includes CRC bytes. */
static int CheckCRC(const MB_t *mb)
{
    if (mb->rxLen < 4) return 0; /* Minimum: addr + FC + CRC16 */
    uint16_t computed = MB_Crc16(mb->rxBuf, mb->rxLen - 2);
    uint16_t received = (uint16_t)mb->rxBuf[mb->rxLen - 2]
                      | ((uint16_t)mb->rxBuf[mb->rxLen - 1] << 8);
    return (computed == received);
}

/* Append CRC to txBuf and set txLen */
static void AppendCRC(MB_t *mb, uint16_t pduLen)
{
    uint16_t crc = MB_Crc16(mb->txBuf, pduLen);
    mb->txBuf[pduLen]     = (uint8_t)(crc & 0xFF);
    mb->txBuf[pduLen + 1] = (uint8_t)(crc >> 8);
    mb->txLen = pduLen + 2;
}

/* Build exception response: [addr][FC|0x80][exception_code][CRC] */
void MB_BuildExceptionRsp(MB_t *mb, uint8_t fc, MB_Exception ex)
{
    mb->txBuf[0] = mb->slaveAddr;
    mb->txBuf[1] = fc | 0x80;
    mb->txBuf[2] = (uint8_t)ex;
    AppendCRC(mb, 3);
}

/* Check if send callback is registered; if not, discard and return to IDLE */
static int HasSendCb(const MB_t *mb)
{
    return (mb->cbSendBuf != (MB_SendBufCb)0);
}

/* Dispatch to FC handler, returns exception code */
static MB_Exception DispatchFC(MB_t *mb)
{
    uint8_t fc = mb->rxBuf[1];
    /* req points to full frame, reqLen includes CRC */
    switch (fc) {
#ifdef MB_CFG_FC03_ENABLE
    case 0x03: return MB_HandleFC03(mb, mb->rxBuf, mb->rxLen);
#endif
#ifdef MB_CFG_FC04_ENABLE
    case 0x04: return MB_HandleFC04(mb, mb->rxBuf, mb->rxLen);
#endif
#ifdef MB_CFG_FC06_ENABLE
    case 0x06: return MB_HandleFC06(mb, mb->rxBuf, mb->rxLen);
#endif
#ifdef MB_CFG_FC16_ENABLE
    case 0x10: return MB_HandleFC16(mb, mb->rxBuf, mb->rxLen);
#endif
#ifdef MB_CFG_FC23_ENABLE
    case 0x17: return MB_HandleFC23(mb, mb->rxBuf, mb->rxLen);
#endif
    default:
        return MB_EX_ILLEGAL_FUNCTION;
    }
}

/* ---- FSM entry points ---- */

void MB_FSM_Init(MB_t *mb)
{
    if (!mb) return;
    mb->state = MB_STATE_IDLE;
    mb->rxLen = 0;
    mb->txLen = 0;
    mb->txPos = 0;
}

void MB_FSM_FeedByte(MB_t *mb, uint8_t byte)
{
    if (!mb) return;
    switch (mb->state) {
    case MB_STATE_IDLE:
        /* First byte = slave address */
        mb->rxLen = 0;
        if (mb->rxLen < MB_CFG_MAX_PDU_SIZE) {
            mb->rxBuf[mb->rxLen++] = byte;
            mb->state = MB_STATE_RECEIVING;
        }
        break;

    case MB_STATE_RECEIVING:
        if (mb->rxLen < MB_CFG_MAX_PDU_SIZE) {
            mb->rxBuf[mb->rxLen++] = byte;
        } else {
            /* Overflow, discard frame */
            mb->state = MB_STATE_IDLE;
            mb->rxLen = 0;
        }
        break;

    default:
        /* Ignore bytes while processing/responding */
        break;
    }
}

void MB_FSM_ProcessEvent(MB_t *mb, MB_Event evt)
{
    (void)evt; /* Only one event type currently */
    if (!mb) return;

    switch (mb->state) {

    case MB_STATE_RECEIVING:
        /* User signals 3.5T silence detected → frame is complete */
        mb->state = MB_STATE_FRAME_READY;
        /* Fall through to process FRAME_READY */

        if (mb->state == MB_STATE_FRAME_READY) {
            /* Validate frame */
            if (!CheckCRC(mb) || !AddressMatch(mb)) {
                /* Silent discard */
                mb->state = MB_STATE_IDLE;
                mb->rxLen = 0;
                break;
            }

            /* Validate function code */
            if (!IsValidFC(mb->rxBuf[1])) {
                if (!IsBroadcast(mb)) {
                    MB_BuildExceptionRsp(mb, mb->rxBuf[1], MB_EX_ILLEGAL_FUNCTION);
                    mb->state = MB_STATE_RESPONDING;
                    mb->txPos = 0;
                } else {
                    mb->state = MB_STATE_IDLE;
                }
                mb->rxLen = 0;
                break;
            }

            /* Dispatch to FC handler */
            mb->state = MB_STATE_PROCESSING;
            MB_Exception ex = DispatchFC(mb);

            if (ex != MB_EX_NONE) {
                /* FC handler returned error */
                if (!IsBroadcast(mb) && HasSendCb(mb)) {
                    MB_BuildExceptionRsp(mb, mb->rxBuf[1], ex);
                    mb->state = MB_STATE_RESPONDING;
                    mb->txPos = 0;
                } else {
                    mb->state = MB_STATE_IDLE;
                }
            } else if (IsBroadcast(mb)) {
                /* Broadcast: no response */
                mb->state = MB_STATE_IDLE;
            } else {
                /* Normal response ready in txBuf */
                if (HasSendCb(mb)) {
                    mb->state = MB_STATE_RESPONDING;
                    mb->txPos = 0;
                } else {
                    mb->state = MB_STATE_IDLE;
                }
            }
            mb->rxLen = 0;
        }
        break;

    default:
        /* Ignore events in other states */
        break;
    }
}
