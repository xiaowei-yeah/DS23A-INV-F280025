/*
* File: 	key.c
* Date: 	2025年11月4日
* Author: 	jinjiale

* Description: 	
* Version: 		
*/
//------------------------------------------Include----------------------------------------

#include "projectall.h"

//-------------------------------------------Macro-----------------------------------------

#define DEBOUNCE_CNT (3)

// TIME1OUT_CNT < TIME2OUT_CNT  否则会冲突
#define TIME1OUT_CNT (50)       //双击检测
#define TIME2OUT_CNT (100)      //长按检测



//------------------------------------Function declaration---------------------------------

void key1_click();
void key1_doubleClick();
void key1_longClick();

void key2_click();
void key2_doubleClick();
void key2_longClick();

void key3_click();
void key3_doubleClick();
void key3_longClick();

//--------------------------------------Struct And Type------------------------------------
enum key_state_enum
{
    keyIdle,
    keyPress,
    keyDoublePress,
    keyLongPress,
    keyRelease,
};
enum key_evt_enum
{
    keyIdleEvt,
    keyPressEvt,
    keyTime1OutEvt,
    keyTime2OutEvt,
    keyReleaseEvt,
    keyLongPressEvt,
};

typedef struct
{
    enum key_state_enum state;
    enum key_evt_enum evt;
    enum key_state_enum nextState;
    void (*pCallbackFunc)();

}key_list_TypeDef;

typedef struct key_edgeChk_TypeDef
{
    uint16_t now;
    uint16_t last;
    uint16_t RE;
    uint16_t FE;
    uint16_t cnt;
}key_edgeChk_TypeDef;

typedef struct key_TypeDef
{
    key_edgeChk_TypeDef edge;
    enum key_state_enum state;
    enum key_evt_enum   evt;
    key_list_TypeDef *list;
    uint16_t listLen;
    uint16_t time1;
    uint16_t time1outvalue;
    uint16_t time2;
    uint16_t time2outvalue;
    void (*pInitFunc)(struct key_TypeDef *);
    void (*pRunFunc)(struct key_TypeDef * ,uint16_t io);

}key_TypeDef;

/****************************************************************
*                       需要自行修改
****************************************************************/
key_list_TypeDef list1[] =
{
 {keyIdle,          keyPressEvt,            keyPress,           NULL},
 {keyPress,         keyReleaseEvt,          keyIdle,            key1_click},        //短按
 {keyPress,         keyTime2OutEvt,         keyLongPress,       NULL},
 {keyLongPress,     keyReleaseEvt,          keyIdle,            NULL},
 {keyLongPress,     keyPressEvt,            keyLongPress,       key1_longClick},    //长按
};
key_list_TypeDef list2[] =
{
 {keyIdle,          keyPressEvt,            keyPress,           NULL},
 {keyPress,         keyReleaseEvt,          keyRelease,         NULL},
 {keyPress,         keyTime2OutEvt,         keyLongPress,       key2_longClick},   //长按
 {keyRelease,       keyTime1OutEvt,         keyIdle,            key2_click},       //短按
 {keyRelease,       keyPressEvt,            keyDoublePress,     key2_doubleClick},  //双击
 {keyLongPress,     keyReleaseEvt,          keyIdle,            NULL},
 {keyDoublePress,   keyReleaseEvt,          keyIdle,            NULL},
};
key_list_TypeDef list3[] =
{
 {keyIdle,          keyPressEvt,            keyPress,           NULL},
 {keyPress,         keyReleaseEvt,          keyIdle,            key3_click},        //短按
 {keyPress,         keyTime2OutEvt,         keyLongPress,       NULL},
 {keyLongPress,     keyReleaseEvt,          keyIdle,            NULL},
 {keyLongPress,     keyPressEvt,            keyLongPress,       key3_longClick},    //长按
};

//-------------------------------------------Value-----------------------------------------

key_TypeDef key1,key2,key3;

//------------------------------------Function definition----------------------------------

/****************************************************************
* Function: 
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void key_Debouncing(struct key_edgeChk_TypeDef *self ,uint16_t io)
{
    // 按键消抖
    if(self->now != io)
    {
        self->cnt++;
    }
    else
    {
        self->cnt = 0;
    }
    if(self->cnt >= DEBOUNCE_CNT)
    {
        self->now = io;
        self->cnt = 0;
    }

    // 检测上升沿和下降沿
    if(self->now != self->last)
    {
        if(self->now == 0)
        {
            self->FE = 1;
            self->RE = 0;
        }
        else
        {
            self->FE = 0;
            self->RE = 1;
        }
        self->last = self->now;
    }

}

void key_evtTrigger(struct key_TypeDef *self)
{
    // 按下 抬起 事件
    if(self->edge.now == 0)
    {
        self->evt = keyPressEvt;
    }
    else
    {
        self->evt = keyReleaseEvt;
    }
    // 超时事件1
    if( self->time1 < self->time1outvalue)
    {
        self->time1++;
    }
    else
    {
        self->evt = keyTime1OutEvt;
        self->time1 = 0;
    }
    // 超时事件2
    if( self->time2 < self->time2outvalue)
    {
        self->time2++;
    }
    else
    {
        self->evt = keyTime2OutEvt;
        self->time2 = 0;
    }

}

void key_run(struct key_TypeDef *self ,uint16_t io)
{

    key_Debouncing(&self->edge ,io);

    key_evtTrigger(self);


    for(uint16_t i = 0; i < self->listLen; i++)
    {
        if(self->state == (self->list + i)->state && self->evt == (self->list + i)->evt)
        {
            self->time1 = 0;
            self->time2 = 0;
            self->evt = keyIdleEvt;
            self->state = (self->list + i)->nextState;
            if((self->list + i)->pCallbackFunc != NULL)
            {
                (*(self->list + i)->pCallbackFunc)();
            }
        }
    }
}


/****************************************************************
*                      ↓ 需要自行修改 ↓
****************************************************************/

/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void key1_init(struct key_TypeDef *self)
{
    self->list = list1;
    self->listLen = sizeof(list1)/sizeof(key_list_TypeDef);
    self->time1outvalue = TIME1OUT_CNT;
    self->time2outvalue = TIME2OUT_CNT;
    self->pRunFunc = key_run;
}
void key2_init(struct key_TypeDef *self)
{
    self->list = list2;
    self->listLen = sizeof(list2)/sizeof(key_list_TypeDef);
    self->time1outvalue = TIME1OUT_CNT;
    self->time2outvalue = TIME2OUT_CNT;
    self->pRunFunc = key_run;
}
void key3_init(struct key_TypeDef *self)
{
    self->list = list3;
    self->listLen = sizeof(list3)/sizeof(key_list_TypeDef);
    self->time1outvalue = TIME1OUT_CNT;
    self->time2outvalue = TIME2OUT_CNT;
    self->pRunFunc = key_run;
}

/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void key_Init()
{
    key1.pInitFunc = key1_init;
    key2.pInitFunc = key2_init;
    key3.pInitFunc = key3_init;

    (*key1.pInitFunc)(&key1);
    (*key2.pInitFunc)(&key2);
    (*key3.pInitFunc)(&key3);

}

/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/
void key_Run()
{
    (*key1.pRunFunc)(&key1,GPIO_readPin(Key1));
    (*key2.pRunFunc)(&key2,GPIO_readPin(Key2));
    (*key3.pRunFunc)(&key3,GPIO_readPin(Key3));
}


/****************************************************************
* Function:
* Description:
* Input:
* Output: None
* Return: None
****************************************************************/

//**************************
void key1_click()
{
    dcac_SetTargetVoltAm(dcac_GetTargetVoltAm()-1);
}
void key1_doubleClick()
{

}
void key1_longClick()
{
    dcac_SetTargetVoltAm(dcac_GetTargetVoltAm()-0.1);
}
//**************************
void key2_click()
{
    task_TurnShutdownMode_Func();
}
void key2_doubleClick()
{

}
void key2_longClick()
{
    task_TurnStandByMode_Func();
}
//**************************
void key3_click()
{
    dcac_SetTargetVoltAm(dcac_GetTargetVoltAm()+1);
}
void key3_doubleClick()
{

}
void key3_longClick()
{
    dcac_SetTargetVoltAm(dcac_GetTargetVoltAm()+0.1);
}
//**************************


//--------------------------------------end of this file-----------------------------------
