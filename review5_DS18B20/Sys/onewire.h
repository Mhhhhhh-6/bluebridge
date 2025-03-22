#ifndef __ONEWIRE_H
#define __ONEWIRE_H

#include <STC15F2K60S2.H>

sbit DQ = P1^4;  

float rd_temperature(void);  

#endif
