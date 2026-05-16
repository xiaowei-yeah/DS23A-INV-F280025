/*
 * mb_func.c - Modbus RTU Function Code Handlers
 *
 * Each handler:
 *   1. Validates request parameters
 *   2. Calls user callbacks for register access
 *   3. Builds response into mb->txBuf
 *   4. Returns MB_EX_NONE on success, or exception code on error
 *
 * The caller (mb_fsm.c) handles exception response construction and broadcast suppression.
 */

#include "mb_internal.h"

/* ---- Helper: read registers (shared by FC03/FC04/FC23) ---- */

static MB_Exception ReadRegisters(MB_t *mb, MB_RegReadCb cb,
                                  uint16_t startAddr, uint16_t count,
                                  uint8_t *rsp, uint16_t *rspLen)
{
    if (count == 0 || count > MB_CFG_MAX_REGS) {
        return MB_EX_ILLEGAL_VALUE;
    }

    /* Temporary buffer on stack for callback to write uint16_t values */
    uint16_t tmp[MB_CFG_MAX_REGS];
    MB_Exception ex = cb(startAddr, tmp, count);
    if (ex != MB_EX_NONE) {
        return ex;
    }

    /* Build response header */
    uint16_t byteCount = count * 2;
    rsp[0] = mb->slaveAddr;
    rsp[1] = mb->rxBuf[1]; /* FC */
    rsp[2] = (uint8_t)byteCount;

    /* Copy to response as big-endian */
    for (uint16_t i = 0; i < count; i++) {
        rsp[3 + i * 2]     = (uint8_t)(tmp[i] >> 8);
        rsp[3 + i * 2 + 1] = (uint8_t)(tmp[i] & 0xFF);
    }

    *rspLen = 3 + byteCount;
    return MB_EX_NONE;
}

/* ---- FC03: Read Holding Registers ---- */

#ifdef MB_CFG_FC03_ENABLE
MB_Exception MB_HandleFC03(MB_t *mb, const uint8_t *req, uint16_t reqLen)
{
    (void)reqLen;
    uint16_t startAddr = ((uint16_t)req[2] << 8) | req[3];
    uint16_t count     = ((uint16_t)req[4] << 8) | req[5];

    if (!mb->cbReadHolding) {
        return MB_EX_SLAVE_FAILURE;
    }

    uint16_t pduLen;
    MB_Exception ex = ReadRegisters(mb, mb->cbReadHolding, startAddr, count,
                                    mb->txBuf, &pduLen);
    if (ex != MB_EX_NONE) {
        return ex;
    }

    /* Append CRC */
    uint16_t crc = MB_Crc16(mb->txBuf, pduLen);
    mb->txBuf[pduLen]     = (uint8_t)(crc & 0xFF);
    mb->txBuf[pduLen + 1] = (uint8_t)(crc >> 8);
    mb->txLen = pduLen + 2;
    return MB_EX_NONE;
}
#endif

/* ---- FC04: Read Input Registers ---- */

#ifdef MB_CFG_FC04_ENABLE
MB_Exception MB_HandleFC04(MB_t *mb, const uint8_t *req, uint16_t reqLen)
{
    (void)reqLen;
    uint16_t startAddr = ((uint16_t)req[2] << 8) | req[3];
    uint16_t count     = ((uint16_t)req[4] << 8) | req[5];

    if (!mb->cbReadInput) {
        return MB_EX_SLAVE_FAILURE;
    }

    uint16_t pduLen;
    MB_Exception ex = ReadRegisters(mb, mb->cbReadInput, startAddr, count,
                                    mb->txBuf, &pduLen);
    if (ex != MB_EX_NONE) {
        return ex;
    }

    uint16_t crc = MB_Crc16(mb->txBuf, pduLen);
    mb->txBuf[pduLen]     = (uint8_t)(crc & 0xFF);
    mb->txBuf[pduLen + 1] = (uint8_t)(crc >> 8);
    mb->txLen = pduLen + 2;
    return MB_EX_NONE;
}
#endif

/* ---- FC06: Write Single Register ---- */

#ifdef MB_CFG_FC06_ENABLE
MB_Exception MB_HandleFC06(MB_t *mb, const uint8_t *req, uint16_t reqLen)
{
    (void)reqLen;
    uint16_t regAddr = ((uint16_t)req[2] << 8) | req[3];
    uint16_t value   = ((uint16_t)req[4] << 8) | req[5];

    if (!mb->cbWriteHolding) {
        return MB_EX_SLAVE_FAILURE;
    }

    MB_Exception ex = mb->cbWriteHolding(regAddr, &value, 1);
    if (ex != MB_EX_NONE) {
        return ex;
    }

    /* Response: echo the request frame */
    mb->txBuf[0] = mb->slaveAddr;
    mb->txBuf[1] = 0x06;
    mb->txBuf[2] = req[2];
    mb->txBuf[3] = req[3];
    mb->txBuf[4] = req[4];
    mb->txBuf[5] = req[5];

    uint16_t crc = MB_Crc16(mb->txBuf, 6);
    mb->txBuf[6] = (uint8_t)(crc & 0xFF);
    mb->txBuf[7] = (uint8_t)(crc >> 8);
    mb->txLen = 8;
    return MB_EX_NONE;
}
#endif

/* ---- FC16: Write Multiple Registers ---- */

#ifdef MB_CFG_FC16_ENABLE
MB_Exception MB_HandleFC16(MB_t *mb, const uint8_t *req, uint16_t reqLen)
{
    uint16_t startAddr = ((uint16_t)req[2] << 8) | req[3];
    uint16_t count     = ((uint16_t)req[4] << 8) | req[5];
    uint16_t byteCount = req[6];

    if (count == 0 || count > MB_CFG_MAX_REGS || byteCount != count * 2) {
        return MB_EX_ILLEGAL_VALUE;
    }

    if (!mb->cbWriteHolding) {
        return MB_EX_SLAVE_FAILURE;
    }

    /* Minimum frame: addr(1) + FC(1) + start(2) + count(2) + byteCount(1) + data(N) + CRC(2) */
    if (reqLen < 7 + byteCount + 2) {
        return MB_EX_ILLEGAL_VALUE;
    }

    /* Convert big-endian data to host uint16_t array (on stack) */
    uint16_t regs[MB_CFG_MAX_REGS];
    for (uint16_t i = 0; i < count; i++) {
        regs[i] = ((uint16_t)req[7 + i * 2] << 8) | req[8 + i * 2];
    }

    MB_Exception ex = mb->cbWriteHolding(startAddr, regs, count);
    if (ex != MB_EX_NONE) {
        return ex;
    }

    /* Response: [addr][FC][start][count][CRC] */
    mb->txBuf[0] = mb->slaveAddr;
    mb->txBuf[1] = 0x10;
    mb->txBuf[2] = req[2];
    mb->txBuf[3] = req[3];
    mb->txBuf[4] = req[4];
    mb->txBuf[5] = req[5];

    uint16_t crc = MB_Crc16(mb->txBuf, 6);
    mb->txBuf[6] = (uint8_t)(crc & 0xFF);
    mb->txBuf[7] = (uint8_t)(crc >> 8);
    mb->txLen = 8;
    return MB_EX_NONE;
}
#endif

/* ---- FC23: Read/Write Multiple Registers ---- */

#ifdef MB_CFG_FC23_ENABLE
MB_Exception MB_HandleFC23(MB_t *mb, const uint8_t *req, uint16_t reqLen)
{
    uint16_t readStart  = ((uint16_t)req[2] << 8) | req[3];
    uint16_t readCount  = ((uint16_t)req[4] << 8) | req[5];
    uint16_t writeStart = ((uint16_t)req[6] << 8) | req[7];
    uint16_t writeCount = ((uint16_t)req[8] << 8) | req[9];
    uint16_t writeBytes = req[10];

    /* Validate read parameters */
    if (readCount == 0 || readCount > MB_CFG_MAX_REGS) {
        return MB_EX_ILLEGAL_VALUE;
    }

    /* Validate write parameters */
    if (writeCount == 0 || writeCount > MB_CFG_MAX_REGS || writeBytes != writeCount * 2) {
        return MB_EX_ILLEGAL_VALUE;
    }

    /* Minimum frame: addr(1)+FC(1)+rStart(2)+rCount(2)+wStart(2)+wCount(2)+wBytes(1)+data(N)+CRC(2) */
    if (reqLen < 11 + writeBytes + 2) {
        return MB_EX_ILLEGAL_VALUE;
    }

    /* ---- Write first (per Modbus spec) ---- */
    if (mb->cbWriteHolding) {
        uint16_t regs[MB_CFG_MAX_REGS];
        for (uint16_t i = 0; i < writeCount; i++) {
            regs[i] = ((uint16_t)req[11 + i * 2] << 8) | req[12 + i * 2];
        }
        MB_Exception ex = mb->cbWriteHolding(writeStart, regs, writeCount);
        if (ex != MB_EX_NONE) {
            return ex;
        }
    } else {
        return MB_EX_SLAVE_FAILURE;
    }

    /* ---- Then read ---- */
    if (!mb->cbReadHolding) {
        return MB_EX_SLAVE_FAILURE;
    }

    uint16_t pduLen;
    MB_Exception ex = ReadRegisters(mb, mb->cbReadHolding, readStart, readCount,
                                    mb->txBuf, &pduLen);
    if (ex != MB_EX_NONE) {
        return ex;
    }

    uint16_t crc = MB_Crc16(mb->txBuf, pduLen);
    mb->txBuf[pduLen]     = (uint8_t)(crc & 0xFF);
    mb->txBuf[pduLen + 1] = (uint8_t)(crc >> 8);
    mb->txLen = pduLen + 2;
    return MB_EX_NONE;
}
#endif
