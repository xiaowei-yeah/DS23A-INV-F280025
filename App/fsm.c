/*
* File: 	fsm.c
* Date: 	2025年10月21日
* Author: 	jin

* Description: 	
* Version: 		
*/
//------------------------------------------Include----------------------------------------

#include "projectall.h"

//-------------------------------------------Macro-----------------------------------------

#define     mFSM_TaskPeriod           2     // 任务周期时间 ms

//------------------------------------Function declaration---------------------------------

static uint16_t sfsm_Delay(uint16_t time);
static uint16_t sfsm_LongDelay(uint32_t time);
static uint16_t sfsm_FaultDelay(uint32_t time);
static void sfsm_ResetDelay(void);
static void sfsm_SetState(enum state_enum state);
static void sfsm_SetSubState(enum substate_enum state);
static uint16_t sfsm_ChkStateChange(void);

//--------------------------------------Struct And Type------------------------------------

//-------------------------------------------Value-----------------------------------------

static enum state_enum FSM_ParentState = State_PowerOn;
static enum substate_enum FSM_SubState = State_Sub_Init;
static uint16_t FSM_TurnStandByMode = 0;
static uint16_t FSM_TurnShutdownMode = 0;

static enum state_enum *pFSM_ParentState = &Sys.State;
static enum substate_enum *pFSM_SubState = &FSM_SubState;
static uint16_t *pFSM_TurnStandByMode = &FSM_TurnStandByMode;
static uint16_t *pFSM_TurnShutdownMode = &FSM_TurnShutdownMode;

static uint16_t FSM_TaskDelayCount1;
static uint32_t FSM_TaskDelayCount2;
static uint32_t FSM_TaskDelayCount3;

//------------------------------------Function definition----------------------------------

/****************************************************************
* Function: sXxxxxMode
* Description:  各状态任务
* Input:
* Output: None
* Return: None
****************************************************************/
static void sPowerOnMode(void)
{
    switch(*pFSM_SubState)
    {
    case State_Sub_Init:
    {
        if(sfsm_Delay(1000))
        {
            sfsm_SetSubState(State_Sub_1);
        }
    }
    break;
    case State_Sub_1:
    {
        static uint16_t cnt1 = 0;
        static uint32_t sum[eAdcName_End] = {0};
        cnt1++;

        sum[eCurr_OutA] += samp_getAd(eCurr_OutA);
        sum[eVolt_OutA] += samp_getAd(eVolt_OutA);

        if(cnt1>=500)
        {
            samp_setOffset(eCurr_OutA,-(float)(sum[eCurr_OutA]/cnt1));
            samp_setOffset(eVolt_OutA,-(float)(sum[eVolt_OutA]/cnt1));
            sfsm_SetSubState(State_Sub_End);
        }
    }
    break;
    case State_Sub_End:
    {
        if(sfsm_Delay(1000))
        {
            sfsm_SetState(State_StandBy);
        }
    }
    break;
    default:
    {
        sfsm_SetSubState(State_Sub_Init);

        #ifdef _DebugStr
            extern char *strGlobalDebugErrInfo;
            strGlobalDebugErrInfo = "FsmPo_case";
        #endif
    }
    break;
    }   // switch

}
static void sShutdownMode(void)
{
    if( sfsm_ChkStateChange() )
    {      ; }

    dcac_Stop();

}
static void sStandByMode(void)
{
    if( sfsm_ChkStateChange() )
    { return; }

    switch(*pFSM_SubState)
    {
    case State_Sub_Init:
    {
        if(sfsm_Delay(1000))
        {
            sfsm_SetSubState(State_Sub_1);
        }
    }
    break;
    case State_Sub_1:
    {
        if(sfsm_Delay(1000))
        {
            sfsm_SetSubState(State_Sub_End);
        }
    }
    break;
    case State_Sub_End:
    {
        if(sfsm_Delay(1000))
        {
            sfsm_SetState(State_NormalInv);
        }
    }
    break;
    default:
    {
        sfsm_SetSubState(State_Sub_Init);

        #ifdef _DebugStr
            extern char *strGlobalDebugErrInfo;
            strGlobalDebugErrInfo = "FsmPo_case";
        #endif
    }
    break;
    }   // switch

}
static void sSoftStartMode(void)
{
    if( sfsm_ChkStateChange() )
    { return; }

}
static void sNormalInvMode(void)
{
    if( sfsm_ChkStateChange() )
    { return; }

    dcac_Start();

}
static void sLimitInvMode(void)
{
    if( sfsm_ChkStateChange() )
    { return; }

}
static void sFaultMode(void)
{
    if( sfsm_ChkStateChange() )
    { return; }

    dcac_Stop();

}
static void sDebugMode(void)
{
    if( sfsm_ChkStateChange() )
    { return; }

}

/****************************************************************
* Function:     sFSM_Run
* Description:  外部调用运行状态机
* Input:
* Output: None
* Return: None
****************************************************************/
void sFSM_Run(void)
{
    switch(*pFSM_ParentState)
    {
        case State_PowerOn:
        sPowerOnMode();
        break;

        case State_Shutdown:
        sShutdownMode();
        break;

        case State_StandBy:
        sStandByMode();
        break;

        case State_SoftStart:
        sSoftStartMode();
        break;

        case State_NormalInv:
        sNormalInvMode();
        break;

        case State_LimitInv:
        sLimitInvMode();
        break;

        case State_Fault:
        sFaultMode();
        break;

        case State_Debug:
        sDebugMode();
        break;

        default:
        break;
    }

}

/****************************************************************
* Function:     sfsm_Delay
* Description:  状态机用定时
* Input:
* Output: None
* Return: None
****************************************************************/
static uint16_t sfsm_Delay(uint16_t time)
{
    if(++FSM_TaskDelayCount1 >= time / mFSM_TaskPeriod)
    {
        FSM_TaskDelayCount1 = 0;
        return 1;
    }
    return 0;
}

static uint16_t sfsm_LongDelay(uint32_t time)
{
    if(++FSM_TaskDelayCount2 >= time / mFSM_TaskPeriod)
    {
        FSM_TaskDelayCount2 = 0;
        return 1;
    }
    return 0;
}

static uint16_t sfsm_FaultDelay(uint32_t time)
{
    if(++FSM_TaskDelayCount3 >= time / mFSM_TaskPeriod)
    {
        FSM_TaskDelayCount3 = 0;
        return 1;
    }
    return 0;
}

static void sfsm_ResetDelay(void)
{
    FSM_TaskDelayCount1 = 0;
    FSM_TaskDelayCount2 = 0;
    FSM_TaskDelayCount3 = 0;
}

/****************************************************************
* Function:     sfsm_SetState
* Description:  切换状态，切换前需要做一些清除准备工作。
* Input:
* Output: None
* Return: None
****************************************************************/
static void sfsm_SetState(enum state_enum state)
{
    sfsm_ResetDelay();
    sfsm_SetSubState(State_Sub_Init);
    *pFSM_ParentState = state;
}

static void sfsm_SetSubState(enum substate_enum state)
{
    sfsm_ResetDelay();
    *pFSM_SubState = state;
}

static enum state_enum sfsm_GetState(void)
{
    return *pFSM_ParentState;
}

/****************************************************************
* Function:     sfsm_ChkStateChange
* Description:  检测有无切换状态信号，并切换。
* Input:
* Output: None
* Return: None
****************************************************************/
static uint16_t sfsm_ChkStateChange(void)
{
    uint16_t rtn = 0;
    if(*pFSM_TurnStandByMode == 1)
    {
        *pFSM_TurnStandByMode = 0;
        sfsm_SetState(State_StandBy);
        rtn = 1;
    }
    if(*pFSM_TurnShutdownMode == 1)
    {
        *pFSM_TurnShutdownMode = 0;
        sfsm_SetState(State_Shutdown);
        rtn = 1;
    }
    return rtn;
}

/****************************************************************
* Function:     task_TurnXxxxxMode_Func
* Description:  外部调用，切换状态。
* Input:
* Output: None
* Return: None
****************************************************************/
void task_TurnStandByMode_Func()
{
    if(*pFSM_ParentState == State_Shutdown)
    {
        *pFSM_TurnStandByMode = 1;
    }
}
void task_TurnShutdownMode_Func()
{
    if(*pFSM_ParentState != State_Shutdown)
    {
        *pFSM_TurnShutdownMode = 1;
    }
}

//--------------------------------------end of this file-----------------------------------

/*

switch(*pFSM_SubState)
{
case State_Sub_Init:
{

}
break;
case State_Sub_1:
{

}
break;
case State_Sub_End:
{

}
break;
default:
{
    sfsm_SetSubState(State_Sub_Init);

    #ifdef _DebugStr
        extern char *strGlobalDebugErrInfo;
        strGlobalDebugErrInfo = "FsmXX_case";
    #endif
}
break;
}   // switch

*/


