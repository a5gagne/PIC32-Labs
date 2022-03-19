#include <p32xxxx.h>

/*
The objective for Task 2 was to only light up bits two, three, four, and 5. 
These bits would flash SOS in Morse code (three short flashes, followed by three long flashes, followed by three short flashes)
*/

void main (void)
{
    int i, j;
    LATF=0; //initialize
    TRISF=0;
   while (1)
   {
        for (j=0; j < 3; j++)
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
         for (j=0; j < 3; j++)
         {
           LATF=0b0000000000111100;
            for (i=0; i < 19000; i++)
             {
                 LATF=0b0000000000111100;
              }
            for (i = 0; i < 19000; i++)
            {
                LATF=0;
             }
          }
    }
}
