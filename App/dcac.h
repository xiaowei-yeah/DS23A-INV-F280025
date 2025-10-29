/*
* File: 	dcac.h
* Date: 	2025Äê10ÔÂ24ÈÕ
* Author: 	jin

* Description: 	
* Version: 		
*/
#ifndef APP_DCAC_H_
#define APP_DCAC_H_

//------------------------------------------Include----------------------------------------

//-------------------------------------------Macro-----------------------------------------

//--------------------------------------Struct And Type------------------------------------

//------------------------------------Function declaration---------------------------------

void dcac_Init();
void dcac_Func(float Io ,float Vo ,float Vin);
void dcac_Start(void);
void dcac_Stop(void);
void dcac_SetVoltLoop(void);
void dcac_SetCurrLoop(void);
uint16_t dcac_GetSpllState(void);

#endif /* APP_DCAC_H_ */

//--------------------------------------end of this file-----------------------------------
