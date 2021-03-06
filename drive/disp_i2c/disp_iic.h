
#ifndef _DISP_IIC_H_
#define _DISP_IIC_H_


#include "STC8H.h"
#include "my_type.h"


//需要根据芯片实现以下引脚操作
#define   DISP_SCL_CRL        
#define   DISP_SCL_SET        
#define   DISP_SCL_OUT()      
#define   DISP_SDA_CRL        
#define   DISP_SDA_SET        
#define   DISP_SDA_OUT()      
#define   DISP_SDA_INPUT()   

//example
//#define   DISP_SCL_CRL        P10 = 0
//#define   DISP_SCL_SET        P10 = 1
//#define   DISP_SCL_OUT()      {P1M1|=0x01;P1M0|=0x01;}
//#define   DISP_SDA_CRL        P11 = 0
//#define   DISP_SDA_SET        P11 = 1
//#define   DISP_SDA_OUT()      {P1M1|=0x02;P1M0|=0x02;}
//#define   DISP_SDA_INPUT()    {P1M1&=~0x02;P1M0&=~0x02;}



extern void init_display_iic_gpio(void);
extern void display_iic_write_data_LSB(char* dataBuff,char length);
#endif