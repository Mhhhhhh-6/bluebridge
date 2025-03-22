#include "onewire.h"

//데悧窟코꼬儺珂변鑒
void Delay_OneWire(unsigned int t);
//{
//	while(t--);
//}

//데悧窟畇꾸鱗
void Write_DS18B20(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ = 0;
		DQ = dat&0x01;
		Delay_OneWire(5);
		DQ = 1;
		dat >>= 1;
	}
	Delay_OneWire(5);
}

//데悧窟뗍꾸鱗
unsigned char Read_DS18B20(void)
{
	unsigned char i;
	unsigned char dat;
  
	for(i=0;i<8;i++)
	{
		DQ = 0;
		dat >>= 1;
		DQ = 1;
		if(DQ)
		{
			dat |= 0x80;
		}	    
		Delay_OneWire(5);
	}
	return dat;
}

//DS18B20놓迦뺏
bit init_ds18b20(void)
{
  	bit initflag = 0;
  	
  	DQ = 1;
  	Delay_OneWire(12);
  	DQ = 0;
  	Delay_OneWire(80);
  	DQ = 1;
  	Delay_OneWire(10); 
    initflag = DQ;     
  	Delay_OneWire(5);
  
  	return initflag;
}
float rd_temperature()
{
	float temp;
	unsigned char msb;//高八位
	unsigned char lsb;//低八位
	init_ds18b20();//初始化 防止上次读数据对此次操作有影响
	Write_DS18B20(0xcc);//跳过ROM
	Write_DS18B20(0x44);//开放温度转换 传感器把测得的数据存进暂存寄存器
	Delay_OneWire(200);//等待
	init_ds18b20();//初始化上次的操作
	Write_DS18B20(0xcc);
	Write_DS18B20(0xbe);//开放数据读取 寄存器可以被读了
	lsb=Read_DS18B20();//先读低八位 再读高八位 之后还有一些东西可以读 总之有顺序 
	msb=Read_DS18B20();
	temp=((unsigned int)msb<<8|lsb)*6.25;//数据处理
	return temp;
}

void Delay_OneWire(unsigned int t)//12T 机器周期是1/12us 而时序要求1us 所以放大12倍
{
	unsigned char i;
	while(t--)
	{
		for (i=0;i<12;i++);
	}
}
