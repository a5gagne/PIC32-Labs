#include <p32xxxx.h>

/*
Task 1 requires the user to configure the keypad so that it interfaces with PORT A
To configure the keypad with PORT A, pins RA9, 10, 14, and 15 should be inputs and pins RA4-7 should be outputs
*/

void main ()
{

    while (1)
    {
   // mJTAGPortEnable(Debug_JTAGPORT_OFF);
    DDPCONbits.JTAGEN=0;				//Disables JTAG
    LATA=0; 						//Initialize LATCH		
    TRISA=0;						//Initialize TRI-STATE

    TRISA=0b1100011000000000;		//Sends I/O values to TRI-STATE
    LATA=0b0000000001100000;		//Sends I/O values to Latch A
 	
    } // end while 
} //end main
