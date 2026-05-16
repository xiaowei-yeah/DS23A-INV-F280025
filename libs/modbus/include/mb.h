/*
 * mb.h - Modbus RTU Slave Library Public API
 *
 * Lightweight, non-blocking, bare-metal Modbus RTU slave library.
 * Zero heap allocation. Multi-instance support.
 *
 * Usage:
 *   1. MB_Init() to initialize instance
 *   2. MB_RegisterCallbacks() to register register access and UART TX callbacks
 *   3. Call MB_FeedByte() from UART RX ISR
 *   4. Call MB_SignalEvent(MB_EVT_TIMEOUT) when 3.5T silence detected (ISR-safe)
 *   5. Call MB_Poll() in main loop 鈥� processes events, sends responses
 */

#ifndef MB_H
#define MB_H

#include "mb_types.h"
#include "mb_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

extern MB_t mb;

/*
 * Initialize Modbus instance.
 * Must be called before any other API.
 */
void MB_Init(MB_t *mb, uint8_t slaveAddr);

/*
 * Register callbacks for register access and UART TX.
 * readHolding  - FC03/23 read holding registers (required if FC03/FC23 enabled)
 * readInput    - FC04 read input registers (required if FC04 enabled)
 * writeHolding - FC06/16/23 write holding registers (required if FC06/FC16/FC23 enabled)
 * sendBuf      - UART TX buffer send (required)
 * txDone       - TX complete notification for RS485 DE control (optional, NULL if unused)
 */
void MB_RegisterCallbacks(MB_t *mb,
                          MB_RegReadCb  readHolding,
                          MB_RegReadCb  readInput,
                          MB_RegWriteCb writeHolding,
                          MB_SendBufCb  sendBuf,
                          MB_TxDoneCb   txDone);

/*
 * Feed one received byte into the library.
 * Call from UART RX ISR or polling loop.
 */
void MB_FeedByte(MB_t *mb, uint8_t byte);

/*
 * Signal an event from ISR or periodic task.
 * Lightweight: only sets a bit in eventFlags.
 * Supported events:
 *   MB_EVT_TIMEOUT - 3.5T frame silence detected, frame is complete
 */
void MB_SignalEvent(MB_t *mb, MB_Event evt);

/*
 * Main polling function. Call in main loop.
 * Processes all pending events:
 *   MB_EVT_TIMEOUT 鈫� validates frame, dispatches FC handler,
 *                    sends response via cbSendBuf, calls cbTxDone
 * Returns current state (for diagnostics).
 */
MB_State MB_Poll(MB_t *mb);

/*
 * Get current FSM state (for debug/diagnostic).
 */
MB_State MB_GetState(const MB_t *mb);

/*
 * Get Modbus exception name string (for debug/logging).
 */
const char *MB_ExceptionStr(MB_Exception ex);

#ifdef __cplusplus
}
#endif

#endif /* MB_H */
