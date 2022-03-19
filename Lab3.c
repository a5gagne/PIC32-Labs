#include <stdio.h>  //all rows in this code are columns and vice versa
#include <stdlib.h>
#include <p32xxxx.h>	
#include <plib.h>


/*
The objective of this project was to design a program for detecting when keys are pressed on the keypad.  
This action will turn on the LEDS corresponding to PORT F, which would indicate that a certain button was pressed
*/

int main()
{
    DDPCONbits.JTAGEN = 0;
    TRISA = 0xC600;
    LATA = 0x0000;
    TRISF = 0x0000;
    LATF = 0x0000;

    int bit4 = 0b0000000000010000;
    int bit5 = 0b0000000000100000;
    int bit6 = 0b0000000001000000;
    int bit7 = 0b0000000010000000;
    int bit9 = 0b0000001000000000;
    int bit10 =0b0000010000000000;
    int bit14 =0b0100000000000000;
    int bit15 =0b1000000000000000;
    int LOWbit=0b0000000011110000;

    int col = 0;
    int row = 0;

    while (1)
    {
        col =0;
        row =0;
        PORTF = 0x0000;
        PORTA = 0x0000;

        //Test the column value.
        //Column 1 = PORT A, bit 9
        //Column 2 = PORT A, bit 10
        //Column 3 = PORT A, bit 14
        //Column 4 = PORT A, bit 15


       if((PORTA & bit15)==0)
            col =4;         //assigning column 4 to bit 15

        if ((row==0) && (col!=0))
        {
        //Check PORTA Bit 7. This is row 1.
        LATA = ((PORTA | LOWbit) & (~bit7));
            if ((PORTA & bit15)==0)   
              row = 1;
        //Check PORTA Bit 6. This is row 2.   
        LATA = ((PORTA | LOWbit) & (~bit6));
            if ((PORTA & bit15)==0)                              
                row = 2;
        //Check PORTA Bit 5. This is row 3.          
        LATA = ((PORTA | LOWbit) & (~bit5));
            if ((PORTA & bit15)==0)                              
                row = 3;
        //Check PORTA Bit 4. This is row 4.                
        LATA = ((PORTA | LOWbit) & (~bit4));
            if ((PORTA & bit15)==0)                              
                row = 4;
        }   
        if (row ==1)
        {
            LATF = 0b0000000000000001;  //Turning on LED on PORTF
        }
        else if (row ==2)
        {
            LATF = 0b0000000000000010; //Turning on LED on PORTF
        }
        else if (row == 3)
        {
            LATF = 0b0000000000000100;  //Turning on LED on PORTF         
        }
        else if (row == 4)
        {
            LATF = 0b0000000000010000;  //Turning on LED on PORTF                  
        }
    }
return (0);
}