//**************************************************************************************
//SW1-D2,SW2-D4
// 头文件
//
//**************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"        // 基址宏定义
#include "inc/hw_types.h"         // 数据类型宏定义，寄存器访问函数
#include "driverlib/debug.h"      // 调试用
#include "driverlib/gpio.h"       // 通用IO口宏定义
#include "driverlib/pin_map.h"    // TM4C系列MCU外围设备管脚宏定义
#include "driverlib/sysctl.h"     // 系统控制宏定义


//**************************************************************************************
//
// 函数原型声明
//
//**************************************************************************************
void  GPIOSet(void);                               // GPIO初始化
void  Flash(uint8_t ui8KeyValue);      //根据输入亮灯
//**************************************************************************************
//
uint32_t p_ui32SysClock;
// 主程序
//
//**************************************************************************************
int main(void)
{
    uint8_t ui8KeyValue;
		p_ui32SysClock = SysCtlClockFreqSet(SYSCTL_OSC_INT,16000000);
    GPIOSet();             // GPIO初始化
    while(1)                // 无限循环
    {
				ui8KeyValue = GPIOPinRead(GPIO_PORTJ_BASE,3);	
				if(!ui8KeyValue)
						ui8KeyValue = 3;
				else
					ui8KeyValue = ui8KeyValue%3;
        Flash(ui8KeyValue);          
    }
}

//**************************************************************************************
//
// 函数原型：void GPIOSet(void)
// 函数功能：GPIO初始化。使能与输出pin设置
// 函数参数：无
//
//**************************************************************************************
void GPIOSet(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);		   // 使能端口 N
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION));	   // 等待端口 N准备完毕
		
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);		   // 使能端口 J	
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)){};  // 等待端口 J准备完毕
	
    // 设置端口 PN0,PN1为输出引脚
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, 3);			
	
    // 设置端口 J的第0,1位（PJ0,PJ1）为输入引脚
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE,3);
    
    // 端口 J的第0,1位作为按键输入，类型设置成“推挽上拉”
    GPIOPadConfigSet(GPIO_PORTJ_BASE,3,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);			
}

//**************************************************************************************
// 
// 函数原型：void Flash(uint8_t ui8KeyValue)
// 函数功能：根据传入的按键值，决定D1,D2亮灭
// 函数参数：ui8KeyValue按键值
//
//**************************************************************************************
void Flash(uint8_t ui8KeyValue_1)
{
		GPIOPinWrite(GPIO_PORTN_BASE, 3, ui8KeyValue_1); 
}
