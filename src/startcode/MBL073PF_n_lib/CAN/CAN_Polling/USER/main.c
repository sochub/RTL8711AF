#include "sys.h"
#include "delay.h"
#include "uart.h"	  
#include "can.h"
#include "HAL_can.h"
#include "tim2.h" 
CanPeliRxMsg CanPeliRxMsgStructure;
/********************************************************************************************************
**函数信息 ：int main (void)                          
**功能描述 ：开机后，接收到报文并打印
**输入参数 ：
**输出参数 ：
********************************************************************************************************/
int main(void)
{
  u8 i = 0;
  delay_init();
  uart_initwBaudRate(115200);	 	//串口初始化为115200
  CANM_Init();
  CAN_Config(CAN_250K,ExtendedFrame_DoubleFilter,0x172,0x325,0x00,0x00);		//CAN验收屏蔽寄存器所有位被置为相关，即只可接受验收代码寄存器中的两个CAN_ID
  Tim2_UPCount_test(47,1000); //1ms时基
  while(1)
  {
    if(Time_Flag_1s)																	//每秒查询并打印一次
    {
      Time_Flag_1s = 0;
      CAN_Peli_Receive(&CanPeliRxMsgStructure);			//保留最近一次成功的CAN通信的信息到CanPeliRxMsgStructure结构体中
      printf("CANID:0x%x  Data",CanPeliRxMsgStructure.ID);	//串口打印
      for(i=0;i<8;i++)															
      {
        printf("%x",CanPeliRxMsgStructure.Data[i]);		//打印CAN报文内容
      }
      printf("\r\n");//换行
    }
  }
}




