/*
 * mb_cfg.h - Modbus RTU Slave Library Configuration
 *
 * Copy this file and adjust values for your project.
 * All macros have safe defaults if not defined.
 */

#ifndef MB_CFG_H
#define MB_CFG_H

/* ---- Max PDU size (address + FC + data + CRC = max 256 bytes) ---- */
#ifndef MB_CFG_MAX_PDU_SIZE
#define MB_CFG_MAX_PDU_SIZE       256
#endif

/* ---- Max registers per read/write operation (Modbus spec: 125 for read, 123 for write) ---- */
#ifndef MB_CFG_MAX_REGS
#define MB_CFG_MAX_REGS           125
#endif

/* ---- Function Code Enable (comment out to disable) ---- */
#define MB_CFG_FC03_ENABLE        /* Read Holding Registers  */
#define MB_CFG_FC04_ENABLE        /* Read Input Registers    */
#define MB_CFG_FC06_ENABLE        /* Write Single Register   */
#define MB_CFG_FC16_ENABLE        /* Write Multiple Registers */
#define MB_CFG_FC23_ENABLE        /* Read/Write Multiple Registers */

/* ---- Broadcast support (address 0x00) ---- */
#define MB_CFG_BROADCAST_ENABLE

/* ---- CRC algorithm ---- */
/* Define MB_CFG_CRC_TABLE for lookup-table (~570B ROM, faster) */
/* Undefine for bit-by-bit (~50B ROM, slower) */
 #define MB_CFG_CRC_TABLE

#endif /* MB_CFG_H */
