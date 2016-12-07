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
    LATC = 0x0;
    
    IOCAP = 0x00; // Disable all IOC capability (pg 137)
    IOCAN = 0x00; // Disable all IOC capability (pg 138)
    
    FVRCONbits.FVREN = 0b0; // Disable FVR
    FVRCONbits.TSEN = 0b0; // Disable temperature indicator
    
    /* Setup analog functionality and port direction */
    TRISA = 0x00;
    ANSELA = 0x00; // Disable all analog input functionality.
    
    TRISC = 0x00;
    ANSELC = 0x00;
    
    ADCON0bits.ADON = 0b0; // Disable ADC
    DACCON0bits.DACEN = 0b0; // Disable DAC
    DACCON0bits.DACOE = 0b0; // Disable DAC Output
    
    SRCON0bits.SRLEN = 0b0; //Disable SR Latch
    
    CM1CON0bits.C1ON = 0b0; // Disable Comparator
    CM2CON0bits.C2ON = 0b0; // Disable Comparator
    
    MDCONbits.MDEN = 0b0; // Disable Digital Signal Modulator
    CPSCON0bits.CPSON = 0b0; // Disable Capacitive Sensing Module
    
    
    
    
    
    /* Initialize peripherals */

    /* Enable interrupts */
    INTCONbits.GIE = 0b0; // Disable all interrupts
}

