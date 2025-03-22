#include <STC15F2K60S2.H>
#include <init.h>
#include <smg.h>
#include <onewire.h>
float t;//��¼����
uchar t_10ms;//�ȴ���������ݸ���
uint t_500ms;//�ȴ��¶ȶ�ȡ
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