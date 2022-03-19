#include <p32xxxx.h>
#include <plib.h>
#include <xc.h>

/*
The first task requires that the Output Compare PWM begins at 75% and then drops down to 25% for two complete iterations. 
The second task requires that the 7-segment display shows a counting sequence from 10 to 20 in base 16 (hexadecimal), 
updating the number once per second. Procedure: Rather than having the PWM begin at 75% and then drop to 25% in a single period, 
we altered the code from the lectures to run one period at 75% and then alternate to a period at 25%. 
*/

#define CCLK (80000000L)
#define PBCLK (CCLK/2)

#define SAMPLE_RATE 3000
#define MAX_PWM PBCLK/SAMPLE_RATE
#define PR MAX_PWM-1
#define PWMvalue2 100
#define PWMvalue3 25
int DUTY_CYCLE=(PR+1)*((float)PWMvalue2/100);
int DUTY_CYCLE2=(PR+1)*((float)PWMvalue3/100);
int count=0;

void __ISR(_TIMER_2_VECTOR,ipl7) T2Interrupt(void)
{
    count++;
   
    if (count%2==0)
    {
        SetDCOC2PWM(DUTY_CYCLE);
    }
    else
 
        SetDCOC2PWM(DUTY_CYCLE2);


    mT2ClearIntFlag();
}

void main()
{
    SYSTEMConfigPerformance(CCLK);
    mOSCSetPBDIV(OSC_PB_DIV_2);
    mJTAGPortEnable(DEBUG_JTAGPORT_OFF);
    OpenOC2(OC_ON|OC_TIMER2_SRC|OC_PWM_FAULT_PIN_DISABLE,0,0);
    OpenSPI2 (SPI_MODE16_ON|MASTER_ENABLE_ON|CLK_POL_ACTIVE_LOW,SPI_ENABLE) ;
    OpenTimer2(T2_ON|T2_PS_1_1|T2_SOURCE_INT,PR);
    INTEnableSystemMultiVectoredInt();
    //PR2 = 1000;
    mT2SetIntPriority(1);
    mT2ClearIntFlag();
    mT2IntEnable(1);
    TRISC=0x00;
    LATC=0;
    mPORTCSetPinsDigitalOut(BIT_3 );
    mPORTCSetBits(BIT_3);
    SetDCOC2PWM(DUTY_CYCLE);
    while(1)
    {
        WriteSPI2(0x0000);
        mPORTCClearBits(BIT_4);
        mPORTCSetBits(BIT_4);
        
        //_RC3=1;
        //_RC4=1;
      
    }
}
