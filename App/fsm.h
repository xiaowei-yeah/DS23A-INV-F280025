/*
* File: 	fsm.h
* Date: 	2025Äê10ÔÂ21ÈÕ
* Author: 	jin

* Description: 	
* Version: 		
*/
#ifndef APP_FRAME_FSM_H_
#define APP_FRAME_FSM_H_

//------------------------------------------Include----------------------------------------

//-------------------------------------------Macro-----------------------------------------

//--------------------------------------Struct And Type------------------------------------

enum state_enum
{
    State_PowerOn       =0,
    State_Shutdown      =1,
    State_StandBy       =2,
    State_SoftStart     =3,
    State_NormalInv     =4,
    State_LimitInv      =5,
    State_Fault         =6,
    State_Debug         =7,
};
enum substate_enum
{
    State_Sub_Init       =0,
    State_Sub_1          =1,
    State_Sub_2          =2,
    State_Sub_3          =3,
    State_Sub_4          =4,
    State_Sub_5          =5,
    State_Sub_6          =6,
    State_Sub_7          =7,
    State_Sub_8          =8,
    State_Sub_9          =9,
    State_Sub_10         =10,
    State_Sub_11         =11,
    State_Sub_12         =12,
    State_Sub_13         =13,
    State_Sub_14         =14,
    State_Sub_15         =15,
    State_Sub_16         =16,
    State_Sub_17         =17,
    State_Sub_18         =18,
    State_Sub_19         =19,
    State_Sub_End
};

//------------------------------------Function declaration---------------------------------

void sFSM_Run(void);
void task_TurnStandByMode_Func();
void task_TurnShutdownMode_Func();
static enum state_enum sfsm_GetState(void);

#endif /* APP_FRAME_FSM_H_ */

//--------------------------------------end of this file-----------------------------------
