#include "init.h"
void HC138_select(uchar channel,uchar dat)
{
	P0=dat;
	P2=(P2&0x1f)|(channel<<5);
	P2&=0x1f;
}
void Init_system()
{
	HC138_select(4,0xff);
	HC138_select(5,0x00);
}