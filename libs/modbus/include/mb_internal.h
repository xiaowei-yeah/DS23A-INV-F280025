/*
 * mb_internal.h - Internal declarations shared between source files
 */

#ifndef MB_INTERNAL_H
#define MB_INTERNAL_H

#include "mb.h"

/* CRC16 calculation (implemented in mb_crc.c) */
uint16_t MB_Crc16(const uint8_t *data, uint16_t len);

/* Frame validation and FC dispatch (implemented in mb_fsm.c) */
void MB_FSM_Init(MB_t *mb);
void MB_FSM_FeedByte(MB_t *mb, uint8_t byte);
void MB_FSM_ProcessEvent(MB_t *mb, MB_Event evt);

/* Build exception response into txBuf */
void MB_BuildExceptionRsp(MB_t *mb, uint8_t fc, MB_Exception ex);

/* Function code handlers (implemented in mb_func.c) */
MB_Exception MB_HandleFC03(MB_t *mb, const uint8_t *req, uint16_t reqLen);
MB_Exception MB_HandleFC04(MB_t *mb, const uint8_t *req, uint16_t reqLen);
MB_Exception MB_HandleFC06(MB_t *mb, const uint8_t *req, uint16_t reqLen);
MB_Exception MB_HandleFC16(MB_t *mb, const uint8_t *req, uint16_t reqLen);
MB_Exception MB_HandleFC23(MB_t *mb, const uint8_t *req, uint16_t reqLen);

#endif /* MB_INTERNAL_H */
