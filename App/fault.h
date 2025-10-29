/*
* File: 	fault.h
* Date: 	2025年10月28日
* Author: 	jin

* Description: 	
* Version: 		
*/
#ifndef APP_FAULT_H_
#define APP_FAULT_H_

//------------------------------------------Include----------------------------------------

//-------------------------------------------Macro-----------------------------------------

//--------------------------------------Struct And Type------------------------------------

//故障类型
enum FM_Type
{
    FM_OverType     = 0,        //过水平故障
    FM_UnderType    = 1,        //欠水平故障
    FM_HardWareType = 2,        //硬件故障
    FM_ComType      = 3,        //通信故障
};

//故障使能
enum FM_EnOrDis
{
    FM_Disable          = 0,
    FM_Enable           = 1,
    FM_ForceDisable     = 2,
};

//故障状态
enum FM_Status
{
    FM_Nomal            = 0,
    FM_Fault            = 1,
};
typedef struct
{
    enum FM_EnOrDis     FaultEnable;            //故障是否使能
    enum FM_Type        FaultType;              //故障类型
    float               FaultValue;             //故障保护点
    uint16_t            FaultTime;              //故障诊断时间
    float               FaultRecoverValue;      //故障恢复点
    uint16_t            FaultRecoverTime;       //故障恢复时间
    uint16_t            FaultCount;             //故障诊断计数
    uint16_t            FaultRecoverCount;      //故障恢复计数
    enum FM_Status      FaultStatus;            //故障状态:是否发生故障
}FaultPara_TypeDef;

//枚举所有故障ID
enum FaultID
{
    //慢速故障
    FM_OverVolt_In       = 0,     //
    FM_UnderVolt_In      = 1,     //
    FM_OverVolt_Out         = 2,     //
    FM_OverCurr_Out         = 3,     //
    FM_Spll                 = 4,
    FM_FaultID_End
};

//------------------------------------Function declaration---------------------------------
void Fault_Init();

void FaultTask(void);
void FaultIsrTask(void);

void Fault_RecoverAllFault(void);
uint32_t Fault_GetFaultCode(void);
uint16_t Fault_GetFaultStatus(void);
void Fault_EnableSet(enum FaultID Fault_ID,enum FM_EnOrDis Fault_EnOrDis);
void Fault_ClearFault(enum FaultID Fault_ID);
void Fault_SetFault(enum FaultID Fault_ID);

#endif /* APP_FAULT_H_ */

//--------------------------------------end of this file-----------------------------------
