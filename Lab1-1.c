#include <p32xxxx.h>

/*
The main objective of the lab was to manipulate the registers of Port F on the PIC32 microcontroller in order to have LEDs light up.
*/

void main (void)
{
    int i;
    LATF=0; //initialize
    TRISF=0;
    while (1)
    {
           LATF=0b0000000000111100;
            for (i=0; i < 10000; i++)
             {
                 LATF=0b0000000000111100;
             }
            for (i = 0; i < 10000; i++)
            {
                LATF=0;
            }
     }
}
