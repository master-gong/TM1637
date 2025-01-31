/**
* @file      TM1637.c
* @brief     TM1637/GN1637 驱动程序.
* @author    mastergong
* @date      2022-06-23
* @version   001
* @copyright -
*/
#include "tm1637.h"


//此码表只适合描述中模组， 不同连接方式码表不同
const char seg_code[]={
0x3F,  /* 0:  0 */
0x06,  /* 1:  1 */
0x5B,  /* 2:  2 */
0x4F,  /* 3:  3 */
0x66,  /* 4:  4 */
0x6D,  /* 5:  5 */
0x7D,  /* 6:  6 */
0x07,  /* 7:  7 */
0x7F,  /* 8:  8*/
0x6F,  /* 9:  9 */
0x77,  /* 10: A */
0x7C,  /* 11: B */
0x39,  /* 12: C */
0x5E,  /* 13: d */
0x79,  /* 14: E */
0x71,  /* 15: F */
0x76,  /* 16: H */
0x38,  /* 17: L */
0x50,  /* 18: r */
0x73,  /* 19：p */
0x37,  /* 20：N */
0x40,  /* 21: - 中- */
0x01,  /* 22：- 上- */
0x08,  /* 23：_ 下- */
0x63,  /* 24：o 上o */
0x5C,  /* 25：o 下o */
0x3E,  /* 26: U */
0x58,  /* 27：c */
0x6B,  /* 28：上o 下-*/
0x5D,  /* 29：下o 上-*/
0x00,  /* 30：  */
};

#define SECOND_CODE 0x80



//反转
static char code_reversed(char segCode)
{
  char res_data=0;
  if((segCode&0x01)==0x01){
    res_data|=0x08;
  } 

  if((segCode&0x02)==0x02){
    res_data|=0x10;
  }               

  if((segCode&0x04)==0x04){
    res_data|=0x20;
  }           
       
  if((segCode&0x08)==0x08){
    res_data|=0x01;
  }       

  if((segCode&0x10)==0x10){
    res_data|=0x02;
  }       

  if((segCode&0x20)==0x20){
    res_data|=0x04;
  }  

  if((segCode&0x40)==0x40){
    res_data|=0x40;
  }  
  return res_data;
}


//镜像
static char code_up_down_mirror(char segCode){
    char res_data = segCode;
    res_data &=~ 0x3F;

    if((segCode&0x01)==0x01){
        res_data |= 0x08;
    }
    if((segCode&0x02)==0x02){
        res_data |= 0x04;
    }

    if((segCode&0x04)==0x04){
        res_data |= 0x02;
    }

    if((segCode&0x08)==0x08){
        res_data |= 0x01;
    }

    if((segCode&0x10)==0x10){
        res_data |= 0x20;
    }

    if((segCode&0x20)==0x20){
        res_data |= 0x10;
    }

    return res_data;
}



//显示接口 
//0.36寸 6位数码管寸
void drive_tm1637_6bit(_disp_buff_st info)
{

   char buff[7];

   //--------亮度设置-----------
   if(info.brightness > 7){
      info.brightness = 7;
   }
    
   buff[0] = 0x40;
   
   TM1637_SET(buff,1);
   

   buff[0] = 0xC0;
   //-------code码赋值----------
   buff[1] = seg_code[info.grid_data[5]];
   buff[2] = seg_code[info.grid_data[4]];
   buff[3] = seg_code[info.grid_data[3]];
   buff[4] = seg_code[info.grid_data[2]];
   buff[5] = seg_code[info.grid_data[1]];
   buff[6] = seg_code[info.grid_data[0]];

   //-------翻转判断-----------
   if(info.flip == 0xA5){
      buff[6] = code_reversed(seg_code[info.grid_data[5]]);
      buff[5] = code_reversed(seg_code[info.grid_data[4]]);
      buff[4] = code_reversed(seg_code[info.grid_data[3]]);
      buff[3] = code_reversed(seg_code[info.grid_data[2]]);
      buff[2] = code_reversed(seg_code[info.grid_data[1]]);
      buff[1] = code_reversed(seg_code[info.grid_data[0]]);
   }
   
   //-------镜像判断-----------
  if(info.mirror == 0xA5){
      buff[1] = code_up_down_mirror(buff[1]);
      buff[2] = code_up_down_mirror(buff[2]);
      buff[3] = code_up_down_mirror(buff[3]);
      buff[4] = code_up_down_mirror(buff[4]);
      buff[5] = code_up_down_mirror(buff[5]);
      buff[6] = code_up_down_mirror(buff[6]);
  }

  //-------冒号显示------------
    if(info.sec_flash){
       buff[2] |= SECOND_CODE;
       buff[4] |= SECOND_CODE;
    }
    
    TM1637_SET(buff,7);

    
    if(info.off){ //关闭显示
        buff[0] = 0x80;
    }else{
        buff[0] = 0x88 | (info.brightness&0x07);
    } 

    TM1637_SET(buff,1);

}
