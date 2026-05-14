#include <REGX52.H>
#include "XPT2046.h"
#include "stdio.h"
#include "UART.h"
#include "Delay.h"
#include "Timer0.h"

xdata unsigned char Receive[30];
volatile unsigned char flag,pwm,Compare;
sbit PWM_OUT = P2^0;

unsigned int Data1,Data2;
void main()
{
	Compare=5;
	Timer0_Init();
	Uart1_Init();
	while(1)
	{
		Data1=XPT2046_Read(XPT2046_XP_8);
		Data2=XPT2046_Read(XPT2046_VBAT_8);
		printf("%d,%d\n",Data1,Data2);
		Delay(100);
		if (flag)
		{
			unsigned char *p=Receive;
			flag=0;
			while (*p!='=')
			{
				p++;
			}
			p++;
			while (*p!='\0')
			{
				pwm=pwm*10+(*p-'0');
				p++;
			}
			Compare=pwm;
			pwm=0;
		}
	}
}

void UART_Routine() interrupt 4
{
	unsigned char c;
	static unsigned char i=0;
	if(RI==1)
	{
		c=SBUF;
		RI=0;
		if (c!='\n')
		{
			Receive[i]=c;
			i++;
		}
		else
		{
			Receive[i] = '\0';
			flag=1;
			i=0;
		}
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned char T0Count=0;
	TL0 = 0x9C;				//设置定时初始值
	TH0 = 0xFF;
	T0Count++;
	T0Count%=100;
	if (T0Count<Compare)
	{
		PWM_OUT=0;
	}
	else
		PWM_OUT=1;
}