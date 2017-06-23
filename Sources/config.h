#ifndef CONFIG_H__
  #define CONFIG_H__
//!<软件版本号 v1.1
#define VERSIONS_MAJOR	(1u)
#define VERSIONS_MINOR	(1u)
#define CAN_BL_APP		(1u)
#define VERSION		"MC9S12G128 BIGDOGv1.1 2017-06-23"


#define LOCK_ADDR_TIMEOUT	500		//定义锁定地址时间，含义和时基有关
#define ADDR_ERR_TIMEOUT    500
#define FRONT_MODULE_ADDR	0x00    //前模块地址
#define WASH_TIMEOUT		300
#define WIPE_INT_TIMEOUT    300
#define WIPE_STOP_TIMEOUT   2000
#define WIPE_WPP_TIMEOUT    200
#define WIPE_WPP_DISCHARGING   16

//#define DEBUG

#endif

/********************************************************************
软件调试记录:
  2017-6-16 18:34:28
  	输出引脚 修改；
  	adc采样修改；
  2017-6-19 13:21:09
    增加地址选择以及地址冲突报警
  2017-6-20 16:30:01
    1.修改电流反馈系数
    2.增加雨刮程序。
    3.增加地址选择程序。
    4.增加休眠程序。
  2017-6-22 17:42:20
    修改地址异常报文位置。 协议修改
  2017-6-23 09:34:15
    修改雨刮地址定义
  
********************************************************************/
/*******************************************************************
硬件整改记录:
  2017-6-19 13:33:45
  36路输出反馈电阻修改:
     3A  ------> 2KΩ
     10A ------> 2kΩ
     15A ------> 510Ω
********************************************************************/


