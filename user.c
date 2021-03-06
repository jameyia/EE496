/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

extern unsigned char clear_buffer_flag;
extern unsigned int multiplexed_counter;
extern unsigned int next_frame_counter;
extern unsigned int fade_frame_counter;
extern unsigned char current_frame[];
extern unsigned short long fade_frame;
extern unsigned int multiplexed_segment_counter;


void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
    // PORT A
    
    WPUA = 0x00; // Enable weak pull ups for all pins on port
    INLVLA = 0x00; // All pins us TTL input levels
    LATA = 0x00;
    
    // PORT C
    WPUC = 0x00;
    INLVLC = 0x00;
    LATC = 0x00;
    
    IOCAP = 0x00; // Disable all IOC capability (pg 137)
    IOCAN = 0x00; // Disable all IOC capability (pg 138)
    
    FVRCONbits.FVREN = 0b0; // Disable FVR
    FVRCONbits.TSEN = 0b0; // Disable temperature indicator
    
    /* Setup analog functionality and port direction */
    TRISA = 0x00;
    ANSELA = 0x00; // Disable all analog input functionality.
    
    TRISC = 0b001010;
    ANSELC = 0x00;
    
    ADCON0bits.ADON = 0b0; // Disable ADC
    DACCON0bits.DACEN = 0b0; // Disable DAC
    DACCON0bits.DACOE = 0b0; // Disable DAC Output
    
    SRCON0bits.SRLEN = 0b0; //Disable SR Latch
    
    CM1CON0bits.C1ON = 0b0; // Disable Comparator
    CM2CON0bits.C2ON = 0b0; // Disable Comparator
    
    MDCONbits.MDEN = 0b0; // Disable Digital Signal Modulator
    CPSCON0bits.CPSON = 0b0; // Disable Capacitive Sensing Module
    
    
    APFCON0bits.SDOSEL = 0b0; // SDO1 is on RC2
    APFCON0bits.SSSEL = 0b0; // 'SS1 is on RC3
    
    /* Initialize peripherals */
    
    // TIMER 0 OPTION_REG
    OPTION_REGbits.nWPUEN = 0b1; //Weak Pull-ups disabled
    OPTION_REGbits.TMR0CS = 0b0; // Internal Clock (Fosc/4)
    OPTION_REGbits.PSA = 0b1; //No Prescaler
    
    // MSSP1
    SSP1STATbits.CKE = 0b1; //
    
    SSP1CON1bits.SSPEN = 0b1; // Enable MSSP
    SSP1CON1bits.CKP = 0b0; // 
    SSP1CON1bits.SSPM = 0b0000; // SPI Master Mode; Clock is Fosc/4 = 8MHz
    
    

    /* Enable interrupts */
    INTCONbits.GIE = 0b1; // Enable interrupts
    INTCONbits.TMR0IE = 0b1; // Enable Timer 0 interrupt
    INTCONbits.PEIE = 0b1; // Enable Peripheral interrupt bits
    //PIE1bits.SSP1IE = 0b1; // Enable MSSP
}

void write_leds()
{
            SSP1BUF = 1 << multiplexed_segment_counter;
            while(SSP1STATbits.BF == 0);
            clear_buffer_flag = SSP1BUF;
            SSP1BUF = ~(fade_frame >> (multiplexed_segment_counter * 8));
            while(SSP1STATbits.BF == 0);
            clear_buffer_flag = SSP1BUF;
            LATCbits.LATC5 = 1;
            LATCbits.LATC5 = 0;
}

void update_fade()
{
    int i = 0;
    
    for(i = 0; i < 18; i++)
    {
        if(current_frame[i] >= fade_frame_counter)
        {
            fade_frame = (fade_frame << 1) + 1;
        }
        
        else
        {
            fade_frame = fade_frame << 1;
        }
    }
}

void get_next_frame()
{
    unsigned char temp;
    int i = 0;
    
    temp = current_frame[0];
    
    for(i = 0; i < 17; i++)
    {
        current_frame[i] = current_frame[i+1];
    }
    
    current_frame[17] = temp;
}