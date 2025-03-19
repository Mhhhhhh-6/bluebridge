#include <STC15F2K60S2.H>
#include <init.h>
#include <smg.h>
#include <ds1302.h>
void Timer0Init(void)		//1毫秒@12.000MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x20;		//设置定时初值
	TH0 = 0xD1;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;
	EA = 1;
}
uchar time10ms;
void Timer0server() interrupt 1
{
	smgdis();
	time10ms++;
}
void main()
{
	Init_system();
	Timer0Init();
	write_rtc();
	while(1)
	{
		if(time10ms>=10)
		{
			time10ms=0;
			read_rtc();
			smgtemp[7]=RTC[0]%16;
			smgtemp[6]=RTC[0]/16;
			smgtemp[4]=RTC[1]%16;
			smgtemp[3]=RTC[1]/16;
			smgtemp[1]=RTC[2]%16;
			smgtemp[0]=RTC[2]/16;
		}
	}
}
