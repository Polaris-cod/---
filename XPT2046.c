#include <REGX52.H>

sbit CS=P3^5;
sbit DCLK=P3^6;
sbit DIN=P3^4;
sbit DOUT=P3^7;

unsigned int XPT2046_Read(unsigned char Command)
{
	unsigned char i;
	unsigned int ADValue=0;
	DCLK=0;
	CS=0;
	for (i=0;i<8;i++)
	{
		DIN=Command&(0x80>>i);
		DCLK=1;
		DCLK=0;
	}
	for (i=0;i<16;i++)
	{
		DCLK=1;
		DCLK=0;
		if(DOUT) ADValue|=(0x8000>>i);
	}
	CS=1;
	if (Command&0x08)
		ADValue=ADValue>>8;
	else
		ADValue=ADValue>>4;
	return ADValue;
}