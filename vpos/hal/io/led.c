#include "vh_io_hal.h"
#include "led.h"


#define DELAY		0x100000

void vh_LedInit(void)
{
	//printk("[debug]call %s %X %X \n",__func__, vh_GPJ2CON, vh_GPJ2DAT);
	
	vh_GPJ2CON = LED1OUT | LED2OUT | LED3OUT | LED4OUT;
	vh_GPJ2DAT = LED1 | LED2 | LED3 | LED4;
	
	vh_GPJ2DAT = 0;
}


void vh_LedSet(unsigned char data)
{
	
}

void vh_LedOn(unsigned char data)
{
}

void vh_LedOff(unsigned char data)
{
}


