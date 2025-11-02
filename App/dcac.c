/*
* File: 	dcac.c
* Date: 	2025年10月24日
* Author: 	jin

* Description: 	
* Version: 		
*/
//------------------------------------------Include----------------------------------------

#include "projectall.h"
#include "ctrl.h"

//-------------------------------------------Macro-----------------------------------------

#define mPi     (3.141592654f)
#define m2Pi    (6.283185308f)
#define mPi2    (1.570796327f)
#define mPi3    (1.047197551f)
#define mSqrt2  (1.414213562f)
#define m2Sqrt2 (2.828427125f)
#define mSqrt3  (1.732050808f)
#define m2Sqrt3 (3.464101615f)
#define m3Sqrt3 (5.196152423f)

//------------------------------------Function declaration---------------------------------

//--------------------------------------Struct And Type------------------------------------

typedef struct {

    float       inputVolt;
    float       inputCurr;
    float       ouputVolt;
    float       ouputCurr;

    float       targetVoltAm;
    float       targetCurrAm;

    float       targetVolt;
    float       targetCurr;

    float       wm;

    float       baseSin;
    float       lastSin;

    float       wn;
    float       ts;

    enum en_dis_enum    en;
    enum en_dis_enum    currflg;
    enum en_dis_enum    voltflg;
    enum en_dis_enum    openloopflg;

    enum en_dis_enum    firstOverZeroflg;

    ctrl_spll_TyprDef       spll;
//    ctrl_2p2z_TyprDef       ctrl_iPR;
    ctrl_pi_TyprDef         ctrl_iPI;
    ctrl_pi_TyprDef         ctrl_vPI;

}dcac_TypeDef;

dcac_TypeDef dcac;

//-------------------------------------------Value-----------------------------------------

//------------------------------------Function definition----------------------------------

/****************************************************************
* Function: 
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void dcac_init(dcac_TypeDef *self)
{
    self->inputVolt = 0;
    self->inputCurr = 0;
    self->ouputVolt = 0;
    self->ouputCurr = 0;
    self->targetVolt = 0;
    self->targetCurr = 0;
    self->targetVoltAm = 30;
    self->targetCurrAm = 0;
    self->ts = (1.0f / 20000.0f);
    self->wn = (m2Pi * 50);
    self->wm = 0;
    self->baseSin = 0;
    self->lastSin = 0;

    self->en = eDisable;

    ctrl_spll_Init(&self->spll,self->ts,self->wn);
    ctrl_pi_Init(&self->ctrl_iPI,1,10,100,-100,self->ts);
    ctrl_pi_Init(&self->ctrl_vPI,2,20,100,-100,self->ts);

}
void dcac_Init()
{
    dcac_init(&dcac);
    dcac.currflg = eDisable;
    dcac.voltflg = eDisable;
    dcac.openloopflg = eEnable;
}

/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
#pragma CODE_SECTION(dcac_func,".TI.ramfunc");
void dcac_func(dcac_TypeDef *self ,float Io ,float Vo ,float Vin)
{
    static uint16_t first;

    self->ouputCurr = Io;
    self->ouputVolt = Vo;
    self->inputVolt = 50.0f;


    if(self->currflg == eEnable)    // 并网 锁相
    {
        ctrl_spll_Run(&self->spll,self->ouputVolt);
        self->baseSin = -cosf(self->spll.wt);
    }
    else                            // 离网 产生正弦信号
    {
        static float wt1;
        wt1 += 0.01571f;
        if(wt1 > m2Pi)
        {
            wt1 = wt1 - m2Pi;
        }
        self->baseSin = sinf(wt1);
        self->spll.ok = eEnable;
    }

    // 锁相完成,启动后检测首次过零
    if(self->en == eEnable && self->firstOverZeroflg == eDisable && self->spll.ok)
    {
        if(self->baseSin >= 0 && self->lastSin < 0)
        {
            self->firstOverZeroflg = eEnable;
        }
        self->lastSin = self->baseSin;
    }

    // 逆变
    if(self->en == eEnable && self->firstOverZeroflg == eEnable && self->spll.ok)    // 过零点开始运行，冲击小。
    {
        if(first == 1)  // 首次执行，打开PWM使能
        {
            first = 0;
            pwm_allon();
        }

        // 并网 电流环
        if(self->currflg == eEnable)
        {
            self->targetCurr = self->targetCurrAm * self->baseSin;
            float ctrl_out = ctrl_pi_Run(&self->ctrl_iPI,self->targetCurr,self->ouputCurr);
            self->wm = (ctrl_out + self->ouputVolt) / self->inputVolt;
        }
        // 离网 电压环
        else if(self->voltflg == eEnable)
        {
            self->targetVolt = self->targetVoltAm * self->baseSin;
            float ctrl_out = ctrl_pi_Run(&self->ctrl_vPI,self->targetVolt,self->ouputVolt);
            self->wm = (ctrl_out + self->ouputVolt) / self->inputVolt;

        }
        // 开环
        else if(self->openloopflg == eEnable)   //
        {
            self->wm = self->targetVoltAm / self->inputVolt * self->baseSin;

        }

        // 单极性调制输出
        if(self->wm > 0)    // 正半波
        {
            pwm_setduty_a(self->wm);
            pwm_setduty_b(0);
        }
        else                // 负半波
        {
            pwm_setduty_a(0);
            pwm_setduty_b(-self->wm);
        }
    }
    else    // !en
    {
        pwm_alloff();   //关闭PWM引脚

        if(first == 0)  // 首次关闭，初始化控制器
        {
            dcac_init(self);
            first = 1;
        }
    }

}
#pragma CODE_SECTION(dcac_Func,".TI.ramfunc");
void dcac_Func(float Io ,float Vo ,float Vin)
{
    dcac_func(&dcac,Io,Vo,Vin);
}

/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void dcac_Start(void)
{
    dcac.en = eEnable;
}

void dcac_Stop(void)
{
    dcac.en = eDisable;
}

void dcac_SetVoltLoop(void)
{
    dcac.en = eDisable;
    dcac.openloopflg = eDisable;
    dcac.currflg = eDisable;
    dcac.voltflg = eEnable;
}
void dcac_SetCurrLoop(void)
{
    dcac.en = eDisable;
    dcac.openloopflg = eDisable;
    dcac.voltflg = eDisable;
    dcac.currflg = eEnable;
}
uint16_t dcac_GetSpllState(void)
{
    return dcac.spll.ok;
}

void dcac_SetTargetVoltAm(float v)
{
    v = v > 50 ? 50 : v;
    v = v < 0 ? 0 : v;
    dcac.targetVoltAm = v;
}
float dcac_GetTargetVoltAm()
{
    return dcac.targetVoltAm;
}


//--------------------------------------end of this file-----------------------------------
