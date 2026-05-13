#include <REGX52.H>
#include "XPT2046.h"
#include "stdio.h"
#include "UART.h"

unsigned int Data1,Data2;
void main()
{
	Uart1_Init();
	while(1)
	{
		Data1=XPT2046_Read(XPT2046_XP_8);
		Data2=XPT2046_Read(XPT2046_YP_8);
		printf("%d,%d\n",Data1,Data2);
	}
}