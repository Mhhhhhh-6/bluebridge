#include <STC15F2K60S2.H>
#include <init.h>
#include <smg.h>
#include <ds1302.h>
void Timer0Init(void)		//1����@12.000MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0x20;		//���ö�ʱ��ֵ
	TH0 = 0xD1;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
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