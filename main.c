#include <REGX52.H>
#include "XPT2046.h"
#include "stdio.h"
#include "UART.h"
#include "Delay.h"
#include "Timer0.h"

xdata unsigned char Receive[30];
volatile unsigned char flag,pwm,Compare;
volatile unsigned int f,T=0xFF9C;
sbit PWM_OUT = P2^0;

void Set_f(unsigned int f);

unsigned int Data1,Data2,Data3;
void main()
{
	Compare=50;
	Timer0_Init();
	Uart1_Init();
	while(1)
	{
		Data1=XPT2046_Read(XPT2046_AUX_12);
		Data2=XPT2046_Read(XPT2046_XP_12);
		Data3=XPT2046_Read(XPT2046_VBAT_12);
		printf("%d,%d,%d\n",Data1,Data2,Data3);
		Delay(100);
		if (flag)
		{
			unsigned char *p=Receive;
			flag=0;
			if(*p=='v')
			{
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
			if(*p=='f')
			{
				while (*p!='=')
				{
					p++;
				}
				p++;
				while (*p!='\0')
				{
					f=f*10+(*p-'0');
					p++;
				}
				Set_f(f);
				f=0;
			}
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
	TH0 = T >> 8;
	TL0 = T & 0xFF;
	T0Count++;
	T0Count%=100;
	if (T0Count<Compare)
	{
		PWM_OUT=0;
	}
	else
		PWM_OUT=1;
}

void Set_f(unsigned int f)
{
	T=65536-f/100;
	TH0 = T >> 8;
	TL0 = T & 0xFF;
}