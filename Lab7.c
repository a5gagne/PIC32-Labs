#include <p32xxxx.h>        /* will get the chip-specific things. */
#include <xc.h>             /* important for assembler calls. */
#include <plib.h>           /* peripheral libraries */

int count=0;

extern void asmfunction(int bits);  /* defined externally in asmfunction.S */
extern unsigned int asmVariable;    /* defined externally in asmfunction.S */
volatile unsigned int cVariable = 0;  /* volatile: don't optimize away. */
volatile unsigned int jak = 0;        /* volatile: don't optimize away. */

void __ISR(_TIMER_2_VECTOR, ipl1) T2InterruptHandler(void)
{
 asmfunction(0x00FFu); 
 mT2ClearIntFlag();
}
void main ()
{
    SYSTEMConfigPerformance(80000000L);  /* I want 80 MHz system clock. */
    TRISF = 0;                           /* Clear Port F latches */
    LATF = 0;
    T2CON=0x8070;
    PR2=2048*15*2;
    LATF = 1;
    mT2SetIntPriority(1);
    INTEnableSystemSingleVectoredInt();
    mT2IntEnable(1);
    while(1)
    {
      //  asmVariable++;
    }
} /* end of main() */

/* this is another function.  It's called from the assembler routine just before
__TRACE(id);
 * returned to main().  This demonstrates how an assembler function can call a
 * C function. */
void foo (void)
{
    jak++;
}
