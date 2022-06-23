
#ifndef __TM1637_H__
#define __TM1637_H__

#include "STC8H.h"
#include "my_type.h"
#include "disp_iic.h"




#define TM1637_SET(segData,length)   display_iic_write_data_LSB(segData,length)


#define LED_SIGE_A     10
#define LED_SIGE_B     11
#define LED_SIGE_C     12
#define LED_SIGE_d     13
#define LED_SIGE_E     14
#define LED_SIGE_F     15
#define LED_SIGE_H     16
#define LED_SIGE_L     17
#define LED_SIGE_r     18
#define LED_SIGE_P     19
#define LED_SIGE_N     20
#define LED_SIGE_M_    21
#define LED_SIGE_U_    22
#define LED_SIGE_D_    23
#define LED_SIGE_Uo    24
#define LED_SIGE_Do    25
#define LED_SIGE_OFF   30
#define LED_SIGE_U     26
#define LED_SIGE_S     5
#define LED_SIGE_Z     28
#define LED_SIGE_Y     29


typedef struct {
    char         grid_data[6]; // ��ʾ
    char         brightness;   // ���� 0-7 
    char         sec_flash;    // == 1   �� ð�ŵ���   
    char         flip;         // == 1   ��ת��ʾ  
    char         mirror;       // == 1   ������ʾ
    char         off;          // == 1   �ر���ʾ               
}_disp_buff_st;
extern void drive_tm1637_6bit(_disp_buff_st info);


#endif


