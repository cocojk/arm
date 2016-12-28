#include "vh_io_hal.h"
#include "led.h"


#define DELAY		0x100000

void vh_LedInit(void)
{
	//printk("[debug]call %s %X %X \n",__func__, vh_GPJ2CON, vh_GPJ2DAT);
	int i,j,dly;
	vh_GPJ2CON = 0x1111;
	vh_GPJ2DAT = 0x0;
	for(i=0;i<5;i++)
	{
		for(j=0;j<4;j++)
		{
			vh_LedSet(j);
			for(dly=0;dly<DELAY;dly++);
		}
	}

	vh_GPJ2DAT =0 ;

}


void vh_LedSet(unsigned char data)
{
	switch(data)
	{
		case 0: vh_GPJ2DAT = 0x01;
				break;
		case 1: vh_GPJ2DAT = 0x02;
				break;
		case 2: vh_GPJ2DAT = 0x04;
				break;
		case 3: vh_GPJ2DAT = 0x08;
				break;
	}
}

void vh_LedOn(unsigned char data)
{
}

void vh_LedOff(unsigned char data)
{
}


