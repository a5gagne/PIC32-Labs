#include <p32xxxx.h>
#include <plib.h>

/*
The first task of the lab was to determine the appropriate settings and to program Timer 2 to generate an ISR that will flash certain LEDs  on Port F
*/

#pragma config FPLLMUL=MUL_16 // multiplier set to 16
#pragma config FPLLIDIV=DIV_4 // input divider set to 4
#pragma config FPLLODIV=DIV_8 // output divider set to 8
#pragma conig FWDTEN=OFF 
#pragma config POSCMOD=HS,FNOSC=PRIPLL
#pragma config FPBDIV=DIV_2 // peripheral bus divider set to 2
#pragma interrupt myInterruptHandler ipl1 vector 0 // interrupt handler


void myInterruptHandler(void) //interrupt handler function
{	
    _LATF2=~_LATF2; //toggles bits 2 and 3 on Port F
    _LATF3=~_LATF3;
    
    mT2ClearIntFlag(); //clear interrupt flag
}

void main ()
{
    SYSTEMConfigPerformance(4000000L);
    T2CON=0x8070; //configure timer
    PR2=4000; 
    TRISF=0; //initialize outputs on PORT F
    LATF=0; //initialize PORT F
    mT2SetIntPriority(1); //interrupt priority
    INTEnableSystemSingleVectoredInt(); 
    mT2IntEnable(1); //enable interrupt
    while(1){} //infinite while loop


}
