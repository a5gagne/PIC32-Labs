#include <p32xxxx.h>
#include <plib.h>

/*
the period timer register two would have to be set to generate an appropriate ISR.  For the second task of the lab the first steps would be to set the Watchdog Timer Postscalar.  
The postscalar for section 2’s task is ‘PS8192’.  After this the Watchdog timer was enabled in the main code and was fed after 8 seconds
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

Appendix B: Lab Code – Part II
Part II
#include <p32xxxx.h>
#include <plib.h>

#pragma config FPLLMUL=MUL_16 // multiplier set to 16
#pragma config FPLLIDIV=DIV_4 // inout divider set to 4
#pragma config FPLLODIV=DIV_8 // output divider set to 8
#pragma conig FWDTEN=OFF
#pragma config POSCMOD=HS,FNOSC=PRIPLL
#pragma config FPBDIV=DIV_2 // peripheral bus divider set to 2
#pragma interrupt myInterruptHandler ipl1 vector 0
#pragma config WDTPS = PS8192 // watchdog post scaler set to 1:8192 (8.192 seconds)
unsigned int count=0; // initialize counter

void myInterruptHandler(void) //
{
    count++; // add to counter
    if (count>=30) // when counter reaches 30 (15 seconds)
    {
        _LATF2=~_LATF2; // toggle bit 2 on port f
    }
    mT2ClearIntFlag(); //clear interrupt flag
}

void main ()
{
    SYSTEMConfigPerformance(4000000L);
    T2CON=0x8070; //
    PR2=4000; // period register set 
    TRISF=0; // initializes outputs on PORT F
    LATF=0; // initializes PORT F
    mT2SetIntPriority(1); // interrupt priority set
    INTEnableSystemSingleVectoredInt();
    mT2IntEnable(1); // enables timer 2 interrupt
    EnableWDT(); // enables watchdog timer
   while(1) // infinite while loop
   {

        if(count<=16) // when counter reaches 16 (8 seconds)
        {
            WDTCONSET=0x01; // feed the watchdog timer
        }
   }
}

