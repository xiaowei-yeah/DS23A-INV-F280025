/*
* File: 	ctrl.h
* Date: 	2025Äê10ÔÂ24ÈÕ
* Author: 	jin

* Description: 	
* Version: 		
*/
#ifndef APP_CTRL_H_
#define APP_CTRL_H_

//------------------------------------------Include----------------------------------------

//-------------------------------------------Macro-----------------------------------------

//--------------------------------------Struct And Type------------------------------------

/****************************************************************
* Description:
****************************************************************/
typedef struct ctrl_pi_TyprDef{

    float kp;
    float ki;
    float max;
    float min;
    float ts;

    float ref;
    float fbk;
    float vi;
    float out;


} ctrl_pi_TyprDef;


/****************************************************************
* Description:
****************************************************************/
typedef struct ctrl_2p2z_TyprDef{

    float b2;
    float b1;
    float b0;
    float a2;
    float a1;
    float max;
    float min;
    float imin;

    float ref;
    float fbk;
    float err;
    float err1;
    float err2;
    float out;
    float out1;
    float out2;

} ctrl_2p2z_TyprDef;


/****************************************************************
* Description:
****************************************************************/
typedef struct ctrl_sogi_TyprDef{

    float ts;
    float w;
    float kp;
    float ui;
    float uo_a;
    float uo_b;
    float sum1;


} ctrl_sogi_TyprDef;


/****************************************************************
* Description:
****************************************************************/
typedef struct ctrl_spll_TyprDef{

    float               ui;
    float               wt;
    float               w;
    float               wn;
    float               ud;
    float               uq;

    ctrl_sogi_TyprDef   sogi;
    ctrl_pi_TyprDef     pi;

    float               chkThreshold;
    uint16_t            ok;

} ctrl_spll_TyprDef;



//------------------------------------Function declaration---------------------------------

void ctrl_sogi_Init(ctrl_sogi_TyprDef *self, float kp ,float ts,float wn);
void ctrl_sogi_Run(ctrl_sogi_TyprDef *self, float ui);

void ctrl_spll_Init(ctrl_spll_TyprDef *self, float ts, float wn);
void ctrl_spll_Run(ctrl_spll_TyprDef *self, float ui);

void ctrl_pi_Init(ctrl_pi_TyprDef *self, float kp,float ki,float max,float min,float ts);
float ctrl_pi_Run(ctrl_pi_TyprDef *self, float ref,float fbk);

void ctrl_2p2z_Init(ctrl_2p2z_TyprDef *self, float b0,float b1,float b2,float a1,float a2,float max,float min);
float ctrl_2p2z_Run(ctrl_2p2z_TyprDef *self, float ref,float fbk);



#endif /* APP_CTRL_H_ */

//--------------------------------------end of this file-----------------------------------
