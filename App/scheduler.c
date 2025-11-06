/*
* File: 	scheduler.c
* Date: 	2025年9月29日
* Author: 	jin

* Description: 	
* Version: 		
*/

//------------------------------------------Include----------------------------------------

#include "projectall.h"
#include "fsm.h"

//--------------------------------------Macro definition-----------------------------------

#define TICK_PER_SECOND 1000

//------------------------------------Function declaration---------------------------------

extern uint32_t tick_Get();
extern void key_Run();

//--------------------------------------Value declaration----------------------------------

//--------------------------------------Value definition-----------------------------------

//------------------------------------Function definition----------------------------------

static void Loop_1000Hz(void) //1ms执行一次
{
    //////////////////////////////////////////////////////////////////////

    FaultTask();

    //////////////////////////////////////////////////////////////////////
}

static void Loop_500Hz(void) //2ms执行一次
{
    //////////////////////////////////////////////////////////////////////

    sFSM_Run();

    //////////////////////////////////////////////////////////////////////
}

static void Loop_200Hz(void) //5ms执行一次
{
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
}

static void Loop_100Hz(void) //10ms执行一次
{
    //////////////////////////////////////////////////////////////////////

    key_Run();

//    static uint16_t nowkey1;
//    static uint16_t nowkey2;
//    static uint16_t nowkey3;
//    static uint16_t lastkey1;
//    static uint16_t lastkey2;
//    static uint16_t lastkey3;
//    nowkey1 = GPIO_readPin(Key1);
//    nowkey2 = GPIO_readPin(Key2);
//    nowkey3 = GPIO_readPin(Key3);
//
//    if(nowkey1==0 && lastkey1==1)
//    {
//        dcac_SetTargetVoltAm(dcac_GetTargetVoltAm()-5);
//    }
//    if(nowkey2==0 && lastkey2==1)
//    {
//        if(Sys.State==State_Shutdown)
//        {
//            task_TurnStandByMode_Func();
//        }
//        if(Sys.State==State_NormalInv || Sys.State==State_StandBy)
//        {
//            task_TurnShutdownMode_Func();
//        }
//    }
//    if(nowkey3==0 && lastkey3==1)
//    {
//        dcac_SetTargetVoltAm(dcac_GetTargetVoltAm()+5);
//    }
//    lastkey1 = nowkey1;
//    lastkey2 = nowkey2;
//    lastkey3 = nowkey3;

    //////////////////////////////////////////////////////////////////////
}

static void Loop_50Hz(void) //20ms执行一次
{
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////

}

static void Loop_20Hz(void) //50ms执行一次
{
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
}

static void Loop_2Hz(void) //500ms执行一次
{
    //////////////////////////////////////////////////////////////////////


    if(Sys.State==State_Shutdown)
    {
        GPIO_writePin(LED2, 1);
        GPIO_writePin(LED1, 0);
    }
    else
    {
        GPIO_writePin(LED2, 0);
        GPIO_togglePin(LED1);
    }

    //////////////////////////////////////////////////////////////////////
}


//////////////////////////////////////////////////////////////////////
//调度器初始化
//////////////////////////////////////////////////////////////////////
//系统任务配置，创建不同执行频率的“线程”
static sched_task_TypeDef sched_tasks[] =
{
    {Loop_1000Hz, 1000, 0, 0},
    {Loop_500Hz, 500, 0, 0},
    {Loop_200Hz, 200, 0, 0},
    {Loop_100Hz, 100, 0, 0},
    {Loop_50Hz, 50, 0, 0},
    {Loop_20Hz, 20, 0, 0},
    {Loop_2Hz, 2, 0, 0},
};

//根据数组长度，判断线程数量
const uint16_t cTaskNum = (sizeof(sched_tasks) / sizeof(sched_task_TypeDef));


/****************************************************************
* Function:     Scheduler_Setup
* Description:
* Input: a -
*        b -
* Output: None
* Return: None
****************************************************************/
void Scheduler_Setup(void)
{
    uint16_t index = 0;
    //初始化任务表
    for (index = 0; index < cTaskNum; index++)
    {
        //计算每个任务的延时周期数
        sched_tasks[index].interval_ticks = TICK_PER_SECOND / sched_tasks[index].rate_hz;
        //最短周期为1，也就是1ms
        if (sched_tasks[index].interval_ticks < 1)
        {
            sched_tasks[index].interval_ticks = 1;
        }
    }
}


/****************************************************************
* Function:  Scheduler_Run
* Description:
* Input: a -
*        b -
* Output: None
* Return: None
****************************************************************/
void Scheduler_Run(void)
{
    uint16_t index = 0;

    for (index = 0; index < cTaskNum; index++)
    {

        uint32_t tnow = tick_Get();

        if (tnow - sched_tasks[index].last_run >= sched_tasks[index].interval_ticks)
        {
            sched_tasks[index].last_run = tnow;
            sched_tasks[index].task_func();
        }
    }
}



//---------------------------------------------end of this file----------------------------------------------
