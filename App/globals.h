/*
* File: 	globals.h
* Date: 	2025Äê9ÔÂ26ÈÕ
* Author: 	jin

* Description: 	
* Version: 		
*/
#ifndef APP_GLOBALS_H_
#define APP_GLOBALS_H_

#ifdef   GLOBALS_VAR
#define  OWN_EXT
#else
#define  OWN_EXT  extern
#endif
//------------------------------------------Include----------------------------------------



//--------------------------------------Macro definition-----------------------------------


enum en_dis_enum
{
    eDisable     = 0,
    eEnable      = 1
};

enum PN_Flg_enum
{
    eSinFlg_N           = 0,
    eSinFlg_P           = 1
};

typedef struct
{
    enum state_enum     State;
    enum en_dis_enum    RunningFlg;
    enum PN_Flg_enum    Input_PN_Flg;
}SysInf_TypeDef;

//------------------------------------Function declaration---------------------------------

void GlobalsVarInit(void);

//--------------------------------------Global value definition-----------------------------------

OWN_EXT float ADCBuff1[400];

OWN_EXT SysInf_TypeDef Sys;

#ifdef _DebugStr
    OWN_EXT char *strGlobalDebugErrInfo;
#endif


#endif /* APP_GLOBALS_H_ */

//---------------------------------------------end of this file----------------------------------------------
