//**************************************************************************************
//SW1-D2,SW2-D4
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
// ����ԭ������
//
//**************************************************************************************
void  GPIOSet(void);                               // GPIO��ʼ��
void  Flash(uint8_t ui8KeyValue);      //������������
//**************************************************************************************
//
uint32_t p_ui32SysClock;
// ������
//
//**************************************************************************************
int main(void)
{
    uint8_t ui8KeyValue;
		p_ui32SysClock = SysCtlClockFreqSet(SYSCTL_OSC_INT,16000000);
    GPIOSet();             // GPIO��ʼ��
    while(1)                // ����ѭ��
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
// ����ԭ�ͣ�void GPIOSet(void)
// �������ܣ�GPIO��ʼ����ʹ�������pin����
// ������������
//
//**************************************************************************************
void GPIOSet(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);		   // ʹ�ܶ˿� N
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION));	   // �ȴ��˿� N׼�����
		
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);		   // ʹ�ܶ˿� J	
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)){};  // �ȴ��˿� J׼�����
	
    // ���ö˿� PN0,PN1Ϊ�������
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, 3);			
	
    // ���ö˿� J�ĵ�0,1λ��PJ0,PJ1��Ϊ��������
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE,3);
    
    // �˿� J�ĵ�0,1λ��Ϊ�������룬�������óɡ�����������
    GPIOPadConfigSet(GPIO_PORTJ_BASE,3,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);			
}

//**************************************************************************************
// 
// ����ԭ�ͣ�void Flash(uint8_t ui8KeyValue)
// �������ܣ����ݴ���İ���ֵ������D1,D2����
// ����������ui8KeyValue����ֵ
//
//**************************************************************************************
void Flash(uint8_t ui8KeyValue_1)
{
		GPIOPinWrite(GPIO_PORTN_BASE, 3, ui8KeyValue_1); 
}
