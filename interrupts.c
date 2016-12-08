/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"           /* For MACRO definitions */

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
#ifndef _PIC12

extern unsigned char var;
extern unsigned int multiplexed_counter;
extern unsigned int next_frame_counter;

void interrupt isr(void)
{
    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */

    if(INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1)
    {
        INTCONbits.TMR0IF = 0; // clear interrupt flag
        
        multiplexed_counter++;
        
        
        if(multiplexed_counter >= MULTIPLEX_LEDS)
        {
            // MULTIPLEX / SHIFT OUT DATA!!!
            multiplexed_counter = 0;
            next_frame_counter++;
            
            
            
            if(next_frame_counter >= NEXT_FRAME)
            {
                // UPDATE FRAME
                next_frame_counter = 0;
                var++;
                
                
                SSP1BUF = var;
                LATCbits.LATC5 = 1;
                LATCbits.LATC5 = 0;
                
            }
        }
        
        
    }
    
#if 0
    
    /* TODO Add interrupt routine code here. */

    /* Determine which flag generated the interrupt */
    if(<Interrupt Flag 1>)
    {
        <Interrupt Flag 1=0>; /* Clear Interrupt Flag 1 */
    }
    else if (<Interrupt Flag 2>)
    {
        <Interrupt Flag 2=0>; /* Clear Interrupt Flag 2 */
    }
    else
    {
        /* Unhandled interrupts */
    }
    
    

#endif

}
#endif


