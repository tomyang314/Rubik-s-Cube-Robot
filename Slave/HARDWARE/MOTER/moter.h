#ifndef __MOTER_H
#define __MOTER_H
#include "sys.h"


void Moter_Init(u16 arr,u16 psc);
void front(u16 time,u8 mode);
void back(u16 time,u8 mode);
void up(u16 time,u8 mode);
void down(u16 time,u8 mode);
void left(u16 time,u8 mode);
void right(u16 time,u8 mode);


#endif

