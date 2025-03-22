#ifndef _INIT_H_
#define _INIT_H_
#include <STC15F2K60S2.H>
typedef unsigned char uchar;
typedef unsigned int uint;
void HC138_select(uchar channel,uchar dat);
void Init_system();
#endif