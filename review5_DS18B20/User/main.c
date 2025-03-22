#include <STC15F2K60S2.H>
#include <init.h>
#include <smg.h>
#include <onewire.h>
float t;//记录数据
uchar t_10ms;//等待数码管数据更新
uint t_500ms;//等待温度读取
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
void Timer0server() interrupt 1
{
	smgdis();
	t_10ms++;
	t_500ms++;
}
void main()
{
	Init_system();
	Timer0Init();
	while(1)
	{
		if(t_10ms>=10)
		{
			t_10ms=0;
			if(t_500ms>=500)
			{
				t=rd_temperature();
				t_500ms=0;
			}
			smgtemp[7]=(uint)t%10;
			smgtemp[6]=(uint)t/10%10;
			smgtemp[5]=(uint)t/100%10+32;
			smgtemp[4]=(uint)t/1000;
		}
	}
}