#include <plib.h>

/*
The final project of BME 538 explores the use of serial communications through SPI, and UART, 
and allows the user to observe interaction between the PIC32 microcontrollers and the PC
A two item menu was made.  This menu gave the user options which, upon inputing, 
would manipulate LEDS on the pic32 microcontroller, and also output messages
*/

#if defined (__32MX340F512H__) || (__32MX360F512L__) || (__32MX460F512L__) || (__32MX795F512L__) || (__32MX430F064L__) || (__32MX450F256L__) || (__32MX470F512L__)
// Configuration Bit settings
// SYSCLK = 80 MHz (8MHz Crystal / FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 80 MHz (SYSCLK / FPBDIV)
// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT OFF
// Other options are don't care
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1
#define SYS_FREQ (80000000L)
#endif



#define	GetPeripheralClock()		(SYS_FREQ/(1 << OSCCONbits.PBDIV))
#define	GetInstructionClock()		(SYS_FREQ)

#if defined (__32MX340F512H__)

#define UART_MODULE_ID UART1 // use first UART.  ChipKit uC32 USB is on UART1

#endif


// Function Prototypes
void SendDataBuffer(const char *buffer, UINT32 size);
UINT32 GetMenuChoice(void);
UINT32 GetDataBuffer(char *buffer, UINT32 max_size);

// Constant Data
const char mainMenu[] =
{
    "\r\n a. Option 1\r\n"
    "b. Option 2\r\n"
};

int main(void)
{
    UINT32  menu_choice;
    UINT8   buf[1024];
    TRISE=0;
    LATE=0;

    UARTConfigure(UART_MODULE_ID, UART_ENABLE_PINS_TX_RX_ONLY);

    UARTSetFifoMode(UART_MODULE_ID, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);

    UARTSetLineControl(UART_MODULE_ID, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);

    UARTSetDataRate(UART_MODULE_ID, GetPeripheralClock(), 57600);

    UARTEnable(UART_MODULE_ID, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));

    SendDataBuffer(mainMenu, sizeof(mainMenu));
 // Code for Explore and Challenge Lab 11
    while(1)
    {
        menu_choice = GetMenuChoice();

        switch(menu_choice)
        {
        case 49:
            PORTE=0b0000000001000000;

            break;
        
        case 50:
            PORTE=0b0000000000011000;
            break;
            
        default:
            sprintf(buf,"\r\nInvalidSelection\r\n\r\n");
            SendDataBuffer(buf,strlen(buf));
            SendDataBuffer(mainMenu,sizeof(mainMenu));
            break;
        }
        if (menu_choice<11)
        {
            sprintf(buf,"\r\nYou Dummy Press A Letter\r\n\r\n");
            SendDataBuffer(buf,strlen(buf));
            SendDataBuffer(mainMenu,sizeof(mainMenu));
        }
        
    }

    return -1;
}
// *****************************************************************************
// void UARTTxBuffer(char *buffer, UINT32 size)
// *****************************************************************************
void SendDataBuffer(const char *buffer, UINT32 size)
{
    while(size)
    {
        while(!UARTTransmitterIsReady(UART_MODULE_ID))
            ;

        UARTSendDataByte(UART_MODULE_ID, *buffer);

        buffer++;
        size--;
    }

    while(!UARTTransmissionHasCompleted(UART_MODULE_ID))
        ;
}
// *****************************************************************************
// UINT32 GetDataBuffer(char *buffer, UINT32 max_size)
// *****************************************************************************
UINT32 GetDataBuffer(char *buffer, UINT32 max_size)
{
    UINT32 num_char;

    num_char = 0;

    while(num_char < max_size)
    {
        UINT8 character;

        while(!UARTReceivedDataIsAvailable(UART_MODULE_ID))
            ;

        character = UARTGetDataByte(UART_MODULE_ID);

        if(character == '\r')
            break;

        *buffer = character;

        buffer++;
        num_char++;
    }

    return num_char;
}
// *****************************************************************************
// UINT32 GetMenuChoice(void)
// *****************************************************************************
UINT32 GetMenuChoice(void)
{
    UINT8  menu_item;

    while(!UARTReceivedDataIsAvailable(UART_MODULE_ID))
        ;

    menu_item = UARTGetDataByte(UART_MODULE_ID);

    menu_item -= '0';
    
    return (UINT8)menu_item;
}
