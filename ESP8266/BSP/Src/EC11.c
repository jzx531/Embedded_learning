#include "EC11.h"
#include "usart.h"

#include "stdio.h"


int16_t Encoder_EC11_Scan(int16_t key,int16_t EC11_A,int16_t EC11_B) 
{
  static int8_t sta=0,sta_key=0;
  int16_t ScanResult = 0;   
  if(sta_key==0 && key==1){sta_key=1;}
  else if(sta_key==1){
    if(key==0){sta_key=2;}
  }
  else if(sta_key==2){
    if(key==1){
      sta_key=0;
      ScanResult=3;
    }
  }
  if(EC11_A==0 && sta==0){
    sta=1;
  } 
  else if(sta==1){
    if(EC11_A==1){
      if(EC11_B==1){
        if(key==0){ScanResult=2;sta_key=0;}
        else {ScanResult=1;}
      }      
      else if(EC11_B==0){
        if(key==0){ScanResult=-2;sta_key=0;}
        else {ScanResult=-1;}
      }
      sta=0;
    }
  }
  if(ScanResult!=0)printf("%d\r\n",ScanResult);	//输出查看，不需要可删除
  return ScanResult;      //返回值的取值：   0：无动作；  1：正转； -1：反转；  2：按下正转； -2：按下反转； 3：只按下并松开
}

