/*
* File: 	globals.c
* Date: 	2025Äê9ÔÂ26ÈÕ
* Author: 	jin

* Description: 	
* Version: 		
*/
#define GLOBALS_VAR
//------------------------------------------Include----------------------------------------

#include <projectall.h>

//------------------------------------Function declaration---------------------------------

//--------------------------------------Value declaration----------------------------------

//--------------------------------------Value definition-----------------------------------

//------------------------------------Function definition----------------------------------

/****************************************************************
* Function: GlobalsVarInit
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void GlobalsVarInit(void)
{
    Sys.State = State_PowerOn;
    Sys.RunningFlg = eDisable;

    #ifdef _DebugStr
        extern char *strGlobalDebugErrInfo;
        strGlobalDebugErrInfo = "Normal";
    #endif

}



//---------------------------------------------end of this file----------------------------------------------
