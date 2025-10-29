/*
* File:     samp.c
* Date:     2025Äê10ÔÂ14ÈÕ
* Author:   jin

* Description:
* Version:
*/

//--------------------------------------include-----------------------------------------

#include "projectall.h"

//---------------------------------------Macro-----------------------------------------

#define cADC_ALL_NUM       (eAdcName_End)
#define cADC_COMDE_FULL     (4095)
#define cADC_VREF           (3.3f)

#define cSAMP_GAIN_VOLT     (53.0f*cADC_VREF/cADC_COMDE_FULL)
#define cSAMP_GAIN_CURR     (cADC_VREF/cADC_COMDE_FULL/0.132f)


typedef struct {
    float ui;
    float pu;
    float real;
    float sum1;
    float sum2;
    uint16_t cnt;
    uint16_t lastPN;

}Rms_typedef;

typedef struct {
    float Ad;
    float Pu;
    float Real;
    float Gain_A2R;
    float Offset;
    float Cali_A;
    float Cali_B;

    Rms_typedef rms;

}AdcCali_typedef;

//--------------------------------Function declaration---------------------------------

uint16_t dma_getBuff(uint16_t p);

//----------------------------------Value declaration----------------------------------

//----------------------------------Value definition-----------------------------------

static AdcCali_typedef Ain[cADC_ALL_NUM];

//--------------------------------Function definition----------------------------------

/****************************************************************
* Function:     samp_Init
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void samp_Init()
{
    for(uint16_t i = 0; i < cADC_ALL_NUM; i++)
    {
        Ain[i].Gain_A2R = 1;
        Ain[i].Offset = -cADC_COMDE_FULL/2;
        Ain[i].Cali_A = 1;
        Ain[i].Cali_B = 0;
    }

    Ain[eCurr_OutA].Gain_A2R = cSAMP_GAIN_CURR;
    Ain[eCurr_OutB].Gain_A2R = cSAMP_GAIN_CURR;
    Ain[eCurr_OutC].Gain_A2R = cSAMP_GAIN_CURR;
    Ain[eVolt_OutA].Gain_A2R = cSAMP_GAIN_VOLT;
    Ain[eVolt_OutB].Gain_A2R = cSAMP_GAIN_VOLT;
    Ain[eVolt_OutC].Gain_A2R = cSAMP_GAIN_VOLT;
    Ain[eVolt_InA].Gain_A2R = cSAMP_GAIN_VOLT;
    Ain[eVolt_InB].Gain_A2R = cSAMP_GAIN_VOLT;
    Ain[eVolt_InC].Gain_A2R = cSAMP_GAIN_VOLT;

    Ain[eVolt_OutA].Offset = -2017;
    Ain[eVolt_InA].Offset = -2014;
}
/****************************************************************
* Function:     samp_updateAdc2Real_
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
#pragma CODE_SECTION(samp_updateAdc2Real,".TI.ramfunc");
uint16_t samp_updateAdc2Real(AdcName_enum id,uint16_t ad)
{
    if(id >= cADC_ALL_NUM)
    {
        return 0;
    }
    Ain[id].Ad = ad;
    Ain[id].Real = (Ain[id].Ad + Ain[id].Offset) * Ain[id].Gain_A2R \
                    * Ain[id].Cali_A + Ain[id].Cali_B;
    return 1;
}

#pragma CODE_SECTION(samp_UpdateAll,".TI.ramfunc");
void samp_UpdateAll()
{
    samp_updateAdc2Real(eCurr_OutA, (dma_getBuff(0)+dma_getBuff(16))>>1 );
    samp_updateAdc2Real(eVolt_OutA, (dma_getBuff(1)+dma_getBuff(17))>>1 );
    samp_updateAdc2Real(eVolt_InA, (dma_getBuff(2)+dma_getBuff(18))>>1 );
}

/****************************************************************
* Function:     samp_set
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
uint16_t samp_setCaliPara(AdcName_enum id,float a,float b)
{
    if(id >= cADC_ALL_NUM)
    {
        return 0;
    }
    Ain[id].Cali_A = a;
    Ain[id].Cali_B = b;
    return 1;
}
/****************************************************************
* Function:     samp_Get
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
#pragma CODE_SECTION(samp_getReal,".TI.ramfunc");
float samp_getReal(AdcName_enum id)
{
    return Ain[id].Real;
}
#pragma CODE_SECTION(samp_getPu,".TI.ramfunc");
float samp_getPu(AdcName_enum id)
{
    return Ain[id].Pu;
}

float samp_getAd(AdcName_enum id)
{
    return Ain[id].Ad;
}

float samp_getRms(AdcName_enum id)
{
    return Ain[id].rms.real;
}





/****************************************************************
* Function:     sampsamp_Rmsfunc_Get
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
#pragma CODE_SECTION(samp_Rmsfunc,".TI.ramfunc");
float samp_Rmsfunc(Rms_typedef *v ,float ui)
{
    v->ui = ui;

    v->cnt++;
    v->sum1 += v->ui*v->ui;

    if(v->ui > 0 && v->lastPN == 0 && v->cnt > 250)
    {
        v->real = sqrtf(v->sum1/(float)v->cnt);
        v->sum1 = 0;
        v->lastPN = 1;
        v->cnt = 0;
    }
    else if(v->ui < 0 && v->lastPN == 1 && v->cnt > 50)
    {
        v->lastPN = 0;
    }

    return v->real;
}
#pragma CODE_SECTION(samp_RmsFunc,".TI.ramfunc");
float samp_RmsFunc(AdcName_enum id)
{
    if(id >= cADC_ALL_NUM)
    {
        return 0;
    }
    return samp_Rmsfunc(&Ain[id].rms,Ain[id].Real);
}


//---------------------------------------------end of this file----------------------------------------------
