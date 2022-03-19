#include <p32xxxx.h>

/*
Task 2 required an LED to flash with a frequency of 1 Hz while an input pin attached to the keypad would light a separate LED located in PORT F
A simple timer was set up to control a flashing LED. To control the blinking LED in PORT F, ‘If’ statements were used to detect high or low logic values
*/

void delay (int count);			//Defines function
void main ()
{
    DDPCONbits.JTAGEN=0;			//Disables JTAG
    T1CON=0x8030;				//Allows timer to be used
    PR1=0xFFFF;	
    LATA=0; 				//Initialize Latch, and tri state
    TRISA=0b0100000000000000;
    LATF=0;
    TRISF=0;
     
    while (1)				//While loop for turning LEDs on/off
    {
        LATA=0b0000000001000000;		//Turns on LED using Latch
        delay (1000);
        LATA=0;					//Turns off Led using Latch
        delay (1000);				//Calls delay function
    }

}

void delay (int count)			//creates/defines delay function
{
    TMR1=0;					//Initializes timer one to 0
    while (TMR1 < count)		
    {
        if (PORTAbits.RA14 == 0)		//Checks if RA14 is logic 0
        {
        LATF=1;
        } 		// end if
        if (PORTAbits.RA14 == 1)		//Checks if RA14 is logic 1
        {
        LATF=0;
        }		//end if
    }		//end while
}		//end functions
