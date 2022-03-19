#include <stdio.h>
#include <plib.h>

/*
When there is no button pressed on the keypad, the LED on Port F Bit 2 will flash at 0.5 Hz. 
When the “2” button is pressed the same LED will flash at 1 Hz. 
This should be achieved by incorporating the keypad button detection from previous labs, 
setting up the proper Timer frequencies and having Timer2 engage an interrupt handler routine
*/

#pragma config FPLLMUL = MUL_16
#pragma config FPLLIDIV = DIV_4
#pragma config FPLLODIV = DIV_8, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL
#pragma config FPBDIV = DIV_8

#define SYS_FREQ (4000000L)

#pragma interrupt InterruptHandler ipl1 vector 0

void InterruptHandler(void)
{
	int bit7 = 0b0000000010000000;
	int bit14 = 0b0100000000000000;
	int col = 0;
	int row = 0;
	if((PORTA & bit14)==0)
	{
		col = 2;
	)
	if(PORTA & bit7)==0)
	{
		row=1;
	}
	if((row==1) && (col==2))
	{
		PR2=2000;
		LATF = ~LATF;
	}
	else
	{
		PR2=1000;
		LATF=~LATF;
	}

mT2ClearIntFlag();
}

void main()
{
	SYSTEMConfigPerformance(4000000L);
TRISA=1;
LATA=0;
TRISF=0;
LATF=0;

PR2=1000;
T2CON = 0x8030;
mT2SetIntPriority(1);
INTEnableSystemSingleVectoredInt();

M2IntEnable(1);

while(1){};
}
