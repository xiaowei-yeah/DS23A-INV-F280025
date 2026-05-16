/*
 * mb_types.h - Modbus RTU Slave Library Type Definitions
 */

#ifndef MB_TYPES_H
#define MB_TYPES_H

#include <stdint.h>
#include "hw_types.h"
/* ---- Event Types (bitmask, extensible) ---- */
typedef enum {
    MB_EVT_TIMEOUT = (1 << 0)   /* 3.5T frame silence detected, frame complete */
} MB_Event;

/* ---- Modbus Exception Codes ---- */
typedef enum {
    MB_EX_NONE             = 0x00,
    MB_EX_ILLEGAL_FUNCTION = 0x01,
    MB_EX_ILLEGAL_ADDRESS  = 0x02,
    MB_EX_ILLEGAL_VALUE    = 0x03,
    MB_EX_SLAVE_FAILURE    = 0x04
} MB_Exception;

/* ---- FSM States ---- */
typedef enum {
    MB_STATE_IDLE = 0,
    MB_STATE_RECEIVING,
    MB_STATE_FRAME_READY,
    MB_STATE_PROCESSING,
    MB_STATE_RESPONDING
} MB_State;

/* ---- Callback Types ---- */
typedef MB_Exception (*MB_RegReadCb)(uint16_t regAddr, uint16_t *buf, uint16_t count);
typedef MB_Exception (*MB_RegWriteCb)(uint16_t regAddr, const uint16_t *buf, uint16_t count);
typedef void (*MB_SendBufCb)(const uint8_t *data, uint16_t len);
typedef void (*MB_TxDoneCb)(void);

/* ---- Instance Structure ---- */
typedef struct {
    MB_State       state;
    uint8_t        slaveAddr;
    uint8_t        rxBuf[256];
    uint16_t       rxLen;
    uint8_t        txBuf[256];
    uint16_t       txLen;
    uint16_t       txPos;
    MB_RegReadCb   cbReadHolding;
    MB_RegReadCb   cbReadInput;
    MB_RegWriteCb  cbWriteHolding;
    MB_SendBufCb   cbSendBuf;
    MB_TxDoneCb    cbTxDone;
    uint8_t        eventFlags;
} MB_t;

#endif /* MB_TYPES_H */
