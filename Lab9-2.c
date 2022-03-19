// configuration bit settings, Fcy=72 MHz, Fpb=36 MHz
#include <p32xxxx.h>
#include <plib.h>

/*
Going further, for the challenge portion of the lab, the potentiometer was used to change values on the seven segment display
*/

#pragma config POSCMOD=HS
#pragma config FNOSC=PRIPLL
#pragma config FPLLIDIV=DIV_2
#pragma config FPLLMUL=MUL_20
#pragma config FPLLODIV=DIV_1
#pragma config FPBDIV=DIV_2

#define POT 8 // 10 k potentiometer on AN5 input
#define AINPUTS 0xffef // Analog inputs POT, TSENS


void initADC( int amask)
{
    	AD1PCFG = amask;     // select analog input pins
    	AD1CON1 = 0x00E0;         // manual conversion sequence control
    	AD1CSSL = 0;         // no scanning required
    	AD1CON2 = 0;         // use MUXA, AVss/AVdd used as Vref+/-
    	AD1CON3=0x1F3F;     // Tad=2+1) x 2 x Tpb=6x27 ns>75 ns
    	AD1CON1bits.ADON=1;     // turn on the ADC
}                 //initADC

//Here is a basic conversion routine:

int readADC( int ch)
{
    	AD1CHSbits.CH0SA = ch;         // 1. select analog input
   	 AD1CON1bits.SAMP = 1;         // 2. start sampling

        
    	while (!AD1CON1bits.DONE);     // 5. wait conversion complete
  	  return ADC1BUF0;         // 6. read result
} // readADC

main ()
{

    	SYSTEMConfigPerformance(80000000L);        //Optimizesystemfrequencyat8MHz
    	mJTAGPortEnable(DEBUG_JTAGPORT_OFF);    //forMIkroEboardonly
   	mOSCSetPBDIV(OSC_PB_DIV_2);        //Peripheralbusfrequencynowis40000000Hz
        	OpenOC2(OC_ON|OC_TIMER2_SRC|OC_PWM_FAULT_PIN_DISABLE,0,0);
        OpenSPI2(SPI_MODE16_ON|MASTER_ENABLE_ON|CLK_POL_ACTIVE_LOW,SPI_ENABLE);
    	int a;
   	 TRISF=0x00;
    	LATF=0x00;
   	 T2CON=0x8070;                //TMR1on,prescale1:256 PB= 36 MHz
   	 PR2=0xFFFF;//setperiodregistertomax
   	 initADC(8);
        	mPORTCSetPinsDigitalOut(BIT_3);
        	mPORTCSetPinsDigitalOut(BIT_4);
        	mPORTCClearBits(BIT_3);
        	mPORTCSetBits(BIT_3);

        	SetDCOC2PWM(5000);
        	mPORTCClearBits(BIT_4);
        	mPORTCSetBits(BIT_4);

   	 while( 1)
    	{

       		 a = readADC( POT);     // select the POT input and convert
                   		 // reduce the 10-bit result to a 4 bit value (0..15)
                		 // (divide by 64 or shift right 6 times
      		  a =a >> 6;
              		  //printf(a);
      		  LATF = a;
               	   if(a== 1|| a == 6)
               	{
               		int num;
                		num = 0x7E;
            
                 		WriteSPI2(num);
               	 	mPORTCClearBits(BIT_4);
                		 mPORTCSetBits(BIT_4);
		}
               
   	 }                 // main loop
}
