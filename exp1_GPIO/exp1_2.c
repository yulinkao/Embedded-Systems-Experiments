//**************************************************************************************
//
// Copyright: 2020-2021, �Ϻ���ͨ��ѧ���ӹ���ϵʵ���ѧ����
// File name: exp0.c
// Description: LED4(D4-PF0)��Լ��1000����Ϊ���ڻ�����˸��
//              ������PUSH1(USR_SW1-PJ0)����LED4(D4-PF0)��Լ��100����Ϊ���ڿ�����˸��
//              �ɿ�PUSH1(USR_SW1-PJ0)����LED4(D4-PF0)�ָ���1000����Ϊ���ڻ�����˸��
// Author:	�Ϻ���ͨ��ѧ���ӹ���ϵʵ���ѧ����
// Version: 1.0.0.20201228 
// Date��2020-12-28
// History��
//       
//**************************************************************************************

//**************************************************************************************
//
// ͷ�ļ�
//
//**************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"        // ��ַ�궨��
#include "inc/hw_types.h"         // �������ͺ궨�壬�Ĵ������ʺ���
#include "driverlib/debug.h"      // ������
#include "driverlib/gpio.h"       // ͨ��IO�ں궨��
#include "driverlib/pin_map.h"    // TM4Cϵ��MCU��Χ�豸�ܽź궨��
#include "driverlib/sysctl.h"     // ϵͳ���ƺ궨��

//**************************************************************************************
//
// �궨��
//
//**************************************************************************************
#define  MilliSecond      4000    // �γ�1msʱ������ѭ������ 
#define  FASTFLASHTIME    50	  // ����ʱ��50ms-100ms��
#define  SLOWFLASHTIME    3000     // ����ʱ��500ms-1s��

//**************************************************************************************
//
// ����ԭ������
//
//**************************************************************************************
void  DelayMilliSec(uint32_t ui32DelaySecond);		// �ӳ�һ��ʱ������λΪ����
void  GPIOInit(void);                               // GPIO��ʼ��
void  PF0Flash(uint8_t ui8KeyValue);      // ���ݴ���İ���ֵ������PF0����������
//void	PN0Flash(uint8_t ui8KeyValue);

//uint32_t ui32SysClock;
//**************************************************************************************
//
// ������
//
//**************************************************************************************
int main(void)
{
    uint8_t ui8KeyValue;
    volatile uint32_t ui32SysClock;
    
    // ʹ��16MHz�ڲ�ʱ��Դ��ϣ�����õ�ϵͳʱ��Ƶ��Ϊ16M
    // ui32SysClock���ʵ�����õ�ϵͳʱ��Ƶ��  
		ui32SysClock = SysCtlClockFreqSet(SYSCTL_OSC_INT,16000000); 
		
		//use extern 25M crystal
		//ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |SYSCTL_OSC_MAIN |SYSCTL_USE_OSC), 25000000);

		//use PLL
		//ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |SYSCTL_OSC_MAIN |SYSCTL_USE_PLL |SYSCTL_CFG_VCO_480), 60000000);
    
    
    GPIOInit();             // GPIO��ʼ��
 
    while(1)                // ����ѭ��
    {
                                        // ��ȡ PJ0 ��ֵ  0-���� 1-�ɿ�
        //ui8KeyValue = GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_0); 
        //PF0Flash(ui8KeyValue);          // ���ݴ���İ�������������PF0����������
			
				if (GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_0)	== 0)						//USR_SW1-PJ0 pressed
				{
						GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0xff);			// Turn on the LED_m0.
						//Delay(FASTFLASHTIME);
				}else{
						GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);			// Turn off the LED_m0.
						//Delay(FASTFLASHTIME);
				}
		
				if (GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_1)	== 0)		                                                                                                                                                                                                                                                                     				//USR_SW1-PJ1 pressed
				{
						GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0xff);			// Turn on the LED_m1.
						//DelayMilliSec(FASTFLASHTIME);
				}else{
						GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);			// Turn off the LED_m1.
						//DelayMilliSec(FASTFLASHTIME);
				}
		}
}

//**************************************************************************************
//
// ����ԭ�ͣ�void DelayMilliSec(uint32_t ui32DelaySecond) 
// �������ܣ��ӳ�һ��ʱ������λΪ����
// ����������ui32DelaySecond���ӳٺ�����
//
//**************************************************************************************
void DelayMilliSec(uint32_t ui32DelaySecond)  
{
    uint32_t ui32Loop;
	
    ui32DelaySecond = ui32DelaySecond * MilliSecond;
    for(ui32Loop = 0; ui32Loop < ui32DelaySecond; ui32Loop++){ };
}

//**************************************************************************************
//
// ����ԭ�ͣ�void GPIOInit(void)
// �������ܣ�GPIO��ʼ����ʹ��PortF������PF0Ϊ�����ʹ��PortJ������PJ0Ϊ����
// ������������
//
//**************************************************************************************
void GPIOInit(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);		   // ʹ�ܶ˿� F
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));	   // �ȴ��˿� F׼�����
		
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);		   // ʹ�ܶ˿� J	
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)){};  // �ȴ��˿� J׼�����
	
    // ���ö˿� F�ĵ�0λ��PF0��Ϊ�������
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
			
    // ���ö˿� F�ĵ�1λ��PF1��Ϊ�������
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);			

    // ���ö˿� N�ĵ�0λ��PN0��Ϊ�������			
		//GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
			
    // ���ö˿� N�ĵ�1λ��PN1��Ϊ�������			
		//GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
		
    // ���ö˿� J�ĵ�0λ��PJ0��Ϊ��������
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE,GPIO_PIN_0);
    
    // �˿� J�ĵ�0λ��Ϊ�������룬�������óɡ�����������
    GPIOPadConfigSet(GPIO_PORTJ_BASE,GPIO_PIN_0,GPIO_STRENGTH_2MA,
                     GPIO_PIN_TYPE_STD_WPU);       
}

//**************************************************************************************
// 
// ����ԭ�ͣ�void PF0Flash(uint8_t ui8KeyValue)
// �������ܣ����ݴ���İ���ֵ������PF0������������0-������1-����
// ����������ui8KeyValue������ֵ
//
//**************************************************************************************
void PF0Flash(uint8_t ui8KeyValue)
{
    uint32_t ui32DelayTime;
	
    if (ui8KeyValue	== 0)                                  // PUSH1(USR_SW1-PJ0) ����
        ui32DelayTime = FASTFLASHTIME;
    else                                                   // PUSH1(USR_SW1-PJ0) �ɿ�
        ui32DelayTime = SLOWFLASHTIME;
		
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0); // ���� LED4(D4-PF0)
    DelayMilliSec(ui32DelayTime);                          // ��ʱui32DelayTime���� 
		
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);        // �ر� LED4(D4-PF0)
    DelayMilliSec(ui32DelayTime);                          // ��ʱui32DelayTime���� 
}

//void PN0Flash(uint8_t ui8KeyValue)
//{
	  //if (ui8KeyValue	== 0)                                  // PUSH1(USR_SW1-PJ0) ����
			//GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_3, GPIO_PIN_3); // ���� LED4(D4-PF0)
    //else                                                   // PUSH1(USR_SW1-PJ0) �ɿ�
			//GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0);        // �ر� LED4(D4-PF0)
//}
