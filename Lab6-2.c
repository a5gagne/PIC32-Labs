#include <p32xxxx.h>
#include <stdlib.h>
#include <plib.h>

/*
The second task requires that an LED flashes a specified number of times. 
This number of flashes is equivalent to the index number of the value ‘7’ stored in an array.
The LED’s should be activated by an interrupt. The index is determined by cycling through an array and using an if statement to compare the values.
*/

#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2
#pragma config FPLLODIV = DIV_4, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_4
#pragma interrupt myInterruptHandler ipl1 vector 0


void myInterruptHandler(void)
{
    int i,j,index;
    char a[]={'1','1','1','1','1','7'};
   TRISF=0;
    LATF=0;

     for (i=0;i!=NULL;i++)
    {
        if (a[i]=='7')
        {
            index=2*(i+1);

            for(j=0;j<index;j++)
            {
                _LATF2=~_LATF2;
            }

        }
    }
    mT2ClearIntFlag();
}



void main()
{
    TRISF=0;
    LATF=0;
   

    SYSTEMConfigPerformance(4000000L);
    T2CON=0x8070;
    PR2=1000;
    mT2SetIntPriority(1);
    INTEnableSystemSingleVectoredInt();
   mT2IntEnable(1);  
  while(1){}

}

