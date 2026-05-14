#include <REGX52.H>

void Timer0_Init(void)		//1毫秒@12.000MHz
{
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0x9C;				//设置定时初始值
	TH0 = 0xFF;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0=1;
	EA=1;
	PT0=0;
}

//void Timer0_Routine() interrupt 1
//{
//	static unsigned int T0Count=0,T1Count=0,T2Count=0;
//	TL0 = 0x18;				
//	TH0 = 0xFC;
//	T0Count++;
//	if (T0Count>=20)
//	{
//		T0Count=0;
//		Key_Loop();
//	}
//	T1Count++;
//	if (T1Count>=2)
//	{
//		T1Count=0;
//		NiXie_Loop();
//	}
//	T2Count++;
//	if (T2Count>=10)
//	{
//		T2Count=0;
//		Sec_Loop();
//	}
//}