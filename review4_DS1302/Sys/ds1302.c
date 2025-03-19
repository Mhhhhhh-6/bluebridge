#include "ds1302.h"  									
uchar RTC[3]={0x55,0x04,0x20};//秒时分的BCD码
//写字节
void Write_Ds1302(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK = 0;
		SDA = temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

//向DS1302寄存器写入数据
void Write_Ds1302_Byte( unsigned char address,unsigned char dat )     
{
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_();  
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

//从DS1302寄存器读出数据
unsigned char Read_Ds1302_Byte ( unsigned char address )
{
 	unsigned char i,temp=0x00;
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1;	_nop_();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDA=0;	_nop_();
	SDA=1;	_nop_();
	return (temp);			
}
//写
void write_rtc()
{
	Write_Ds1302_Byte(0x8e,0x00);//开放
	Write_Ds1302_Byte(0x80,RTC[0]);//秒
	Write_Ds1302_Byte(0x82,RTC[1]);//分
	Write_Ds1302_Byte(0x84,RTC[2]);//时
	Write_Ds1302_Byte(0x8e,0x80);//关闭
}
//读
void read_rtc()
{
	RTC[0]=Read_Ds1302_Byte(0x81);//读取秒
	RTC[1]=Read_Ds1302_Byte(0x83);//读取分
	RTC[2]=Read_Ds1302_Byte(0x85);//读取时
}
