/*
* File: 	fault.c
* Date: 	2025年10月28日
* Author: 	jin

* Description: 	
* Version: 		
*/
//------------------------------------------Include----------------------------------------

#include "projectall.h"

//-------------------------------------------Macro-----------------------------------------

//------------------------------------Function declaration---------------------------------

//--------------------------------------Struct And Type------------------------------------


//-------------------------------------------Value-----------------------------------------

const FaultPara_TypeDef     FaultParaDefault[FM_FaultID_End] =
{
    //故障名                  // 使能         // 类型              // 保护值        // 超过计值      // 恢复值        // 恢复计值      // 计数1     // 计数2     // 默认状态
    [FM_OverVolt_In     ] = {FM_Enable,     FM_OverType,        40,             500,            40,             5000,           0,          0,          FM_Nomal},
    [FM_UnderVolt_In    ] = {FM_Enable,     FM_UnderType,       8,              500,            8,              5000,           0,          0,          FM_Nomal},
    [FM_OverVolt_Out    ] = {FM_Enable,     FM_OverType,        40,             10,             40,             5000,           0,          0,          FM_Nomal},
    [FM_OverCurr_Out    ] = {FM_Enable,     FM_OverType,        5,              0,              1,              5000,           0,          0,          FM_Nomal},
    [FM_Spll            ] = {FM_Enable,     FM_UnderType,       1,              0,              0,              5000,           0,          0,          FM_Nomal}
};

static FaultPara_TypeDef    Fault[FM_FaultID_End];      // 故障定义
static uint32_t             FaultCode;                  // 故障码
static enum FM_Status       MainFaultStatus;            // 主故障状态

//------------------------------------Function definition----------------------------------

/****************************************************************
* Function: 
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void Fault_Init()
{
    memcpy(Fault,FaultParaDefault,sizeof(FaultParaDefault));
    FaultCode = 0;
    MainFaultStatus = FM_Nomal;
}

/******************************************************
* Function description: 设置故障
* Input:                Fault_ID:       故障ID
* Output:               void
*******************************************************/
void Fault_SetFault(enum FaultID Fault_ID)
{
    Fault[Fault_ID].FaultStatus = FM_Fault;
    FaultCode |= ( (uint32_t)0x01ul << Fault_ID );
    Fault[Fault_ID].FaultCount = 0;

}
/******************************************************
* Function description: 清除故障
* Input:                Fault_ID:       故障ID
* Output:               void
*******************************************************/
void Fault_ClearFault(enum FaultID Fault_ID)
{

    Fault[Fault_ID].FaultStatus = FM_Nomal;
    FaultCode &= ( ~((uint32_t)0x01ul << Fault_ID) );
    Fault[Fault_ID].FaultRecoverCount = 0;
}
/******************************************************
* Function description: 更新主故障状态
* Input:                void
* Output:               void
*******************************************************/
void Fault_StatusUpdata(void)
{
    if(FaultCode == 0)
    {
        MainFaultStatus = FM_Nomal;
    }
    else
    {
        MainFaultStatus = FM_Fault;
    }
}

/******************************************************
* Function description: 使能或禁止故障检测
* Input:                Fault_ID:       故障ID
*                       Fault_EnOrDis:  使能或禁止
* Output:               void
*******************************************************/
void Fault_EnableSet(enum FaultID Fault_ID,enum FM_EnOrDis Fault_EnOrDis)
{
    Fault[Fault_ID].FaultEnable = Fault_EnOrDis;
}

/******************************************************
* Function description: 设置故障限值
* Input:                Fault_ID:       故障ID
*                       Value:          设置值
* Output:               void
*******************************************************/
void Fault_ValueSet(enum FaultID Fault_ID,float Value)
{
    Fault[Fault_ID].FaultValue = Value;
}

/******************************************************
* Function description: 设置故障恢复值
* Input:                Fault_ID:       故障ID
*                       Value:          设置值
* Output:               void
*******************************************************/
void Fault_RecoverValueSet(enum FaultID Fault_ID,float Value)
{
    Fault[Fault_ID].FaultRecoverValue = Value;
}

/******************************************************
* Function description: 设置故障限值
* Input:                Fault_ID:       故障ID
*                       Value:          设置值
* Output:               void
*******************************************************/
void Fault_TimeSet(enum FaultID Fault_ID,uint16_t Time)
{
    Fault[Fault_ID].FaultTime = Time;
}

/******************************************************
* Function description: 设置故障恢复值
* Input:                Fault_ID:       故障ID
*                       Value:          设置值
* Output:               void
*******************************************************/
void Fault_RecoverTimeSet(enum FaultID Fault_ID,uint16_t Time)
{
    Fault[Fault_ID].FaultRecoverTime = Time;
}

/******************************************************
* Function description: 获取主故障状态
* Input:                void
* Output:               主故障状态
*******************************************************/
#pragma CODE_SECTION(Fault_GetFaultStatus,".TI.ramfunc");
uint16_t Fault_GetFaultStatus(void)
{
    return MainFaultStatus;
}

/******************************************************
* Function description: 获取故障码
* Input:                void
* Output:               故障码
*******************************************************/
#pragma CODE_SECTION(Fault_GetFaultCode,".TI.ramfunc");
uint32_t Fault_GetFaultCode(void)
{
    return FaultCode;
}

/******************************************************
* Function description: 获取故障位状态
* Input:                ID
* Output:               故障位状态
*******************************************************/
enum FM_Status Fault_GetFaultBitStatus(enum FaultID Fault_ID)
{
    return Fault[Fault_ID].FaultStatus;
}

/******************************************************
* Function Fault_RecoverAllFault: 恢复所有故障
* Input:                void
* Output:               void
*******************************************************/
void Fault_RecoverAllFault(void)
{
    //恢复所有故障
    for(enum FaultID Fault_ID = (enum FaultID)0 ;Fault_ID < FM_FaultID_End ;Fault_ID++)
    {
        if(Fault[Fault_ID].FaultStatus == FM_Fault)
        {
            Fault_ClearFault(Fault_ID);
        }
    }
}
/******************************************************
* Function description: 过水平故障检测
* Input:                Fault_ID:       故障ID
*                       Value:          采样值
*                       Period:         函数被调用周期(ms)
* Output:               void
*******************************************************/
void Fault_OverCheck(enum FaultID Fault_ID,float Value)
{
    if((Fault[Fault_ID].FaultEnable==FM_Enable)&&(Fault[Fault_ID].FaultStatus==FM_Nomal))
    {
        if(Fault[Fault_ID].FaultType==FM_OverType)
        {
            if(Value > Fault[Fault_ID].FaultValue)
            {
                if(Fault[Fault_ID].FaultCount >= Fault[Fault_ID].FaultTime)
                {
                    Fault_SetFault(Fault_ID);//设置故障
                }
                else
                {
                    Fault[Fault_ID].FaultCount ++;
                }
            }
            else
            {
                if(Fault[Fault_ID].FaultCount > 0)
                {
                    Fault[Fault_ID].FaultCount--;
                }
                else
                {
                    Fault[Fault_ID].FaultCount = 0;
                }
            }
        }
    }
}

/******************************************************
* Function description: 欠水平故障检测
* Input:                Fault_ID:       故障ID
*                       Value:          采样值
*                       Period:         函数被调用周期(ms)
* Output:               void
*******************************************************/
void Fault_UnderCheck(enum FaultID Fault_ID,float Value)
{
    if((Fault[Fault_ID].FaultEnable==FM_Enable)&&(Fault[Fault_ID].FaultStatus==FM_Nomal))
    {
        if(Fault[Fault_ID].FaultType==FM_UnderType)
        {
            if(Value < Fault[Fault_ID].FaultValue)
            {
                if(Fault[Fault_ID].FaultCount >= Fault[Fault_ID].FaultTime)
                {
                    Fault_SetFault(Fault_ID);//设置故障
                }
                else
                {
                    Fault[Fault_ID].FaultCount ++;
                }
            }
            else
            {
                if(Fault[Fault_ID].FaultCount > 0)
                {
                    Fault[Fault_ID].FaultCount--;
                }
                else
                {
                    Fault[Fault_ID].FaultCount = 0;
                }
            }
        }
    }
}

/******************************************************
* Function description: 过水平故障恢复
* Input:                Fault_ID:       故障ID
*                       Value:          采样值
*                       Period:         函数被调用周期(ms)
* Output:               void
*******************************************************/
void Fault_OverRecoverCheck(enum FaultID Fault_ID,float Value)
{
    if((Fault[Fault_ID].FaultEnable==FM_Enable)&&(Fault[Fault_ID].FaultStatus==FM_Fault))
    {
        if((Fault[Fault_ID].FaultType==FM_OverType))
        {
            if(Value < Fault[Fault_ID].FaultRecoverValue)
            {
                if(Fault[Fault_ID].FaultRecoverCount >= Fault[Fault_ID].FaultRecoverTime)
                {
                    Fault_ClearFault(Fault_ID);//清除故障
                }
                else
                {
                    Fault[Fault_ID].FaultRecoverCount ++;
                }
            }
            else
            {
                Fault[Fault_ID].FaultRecoverCount = 0;
            }
        }
    }
}

/******************************************************
* Function description: 欠水平故障恢复
* Input:                Fault_ID:       故障ID
*                       Value:          采样值
*                       Period:         函数被调用周期(ms)
* Output:               void
*******************************************************/
void Fault_UnderRecoverCheck(enum FaultID Fault_ID,float Value)
{
    if((Fault[Fault_ID].FaultEnable==FM_Enable)&&(Fault[Fault_ID].FaultStatus==FM_Fault))
    {
        if((Fault[Fault_ID].FaultType==FM_UnderType))
        {
            if(Value > Fault[Fault_ID].FaultRecoverValue)
            {
                if(Fault[Fault_ID].FaultRecoverCount >= Fault[Fault_ID].FaultRecoverTime)
                {
                    Fault_ClearFault(Fault_ID);//清除故障
                }
                else
                {
                    Fault[Fault_ID].FaultRecoverCount ++;
                }
            }
            else
            {
                Fault[Fault_ID].FaultRecoverCount = 0;
            }
        }
    }
}


/******************************************************
* Function description: 故障检测任务
* Input:                void
* Output:               void
*******************************************************/
void Fault_CheckTask(void)
{
    Fault_OverCheck(FM_OverVolt_In,  samp_getReal(eVolt_InA));
    Fault_UnderCheck(FM_UnderVolt_In,samp_getReal(eVolt_InA));
    Fault_UnderCheck(FM_Spll,           dcac_GetSpllState());
}

/******************************************************
* Function description: 快速故障任务
* Input:                void
* Output:               void
*******************************************************/
#pragma CODE_SECTION(FaultIsrTask,".TI.ramfunc");
void FaultIsrTask(void)
{
    Fault_OverCheck(FM_OverVolt_Out,    samp_getReal(eVolt_OutA));
    Fault_OverCheck(FM_OverCurr_Out,    samp_getReal(eCurr_OutA));
}

/******************************************************
* Function description: 故障恢复任务
* Input:                void
* Output:               void
*******************************************************/
void Fault_RecoverTask(void)
{
    Fault_OverRecoverCheck(FM_OverVolt_In,  samp_getReal(eVolt_InA));
    Fault_UnderRecoverCheck(FM_UnderVolt_In,samp_getReal(eVolt_InA));
    Fault_UnderRecoverCheck(FM_Spll,        dcac_GetSpllState());

    Fault_OverRecoverCheck(FM_OverVolt_Out,  samp_getReal(eVolt_OutA));
    Fault_OverRecoverCheck(FM_OverCurr_Out,  samp_getReal(eCurr_OutA));
}

/******************************************************
* Function description: 故障任务
* Input:                void
* Output:               void
*******************************************************/
void FaultTask(void)
{
    Fault_CheckTask();
    Fault_RecoverTask();
    Fault_StatusUpdata();
}



//--------------------------------------end of this file-----------------------------------
