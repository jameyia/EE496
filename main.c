/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

unsigned int multiplexed_counter = 0;
unsigned int next_frame_counter = 0;
unsigned int fade_frame_counter = 1;
unsigned char clear_buffer_flag = 0x00;
//unsigned short long current_frame = 0x000000;
unsigned short long fade_frame = 0x000000;
unsigned int multiplexed_segment_counter = 0;
unsigned char current_frame[18] = {8,7,6,5,4,3,2,1,0,8,7,6,5,4,3,2,1,0};


/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();
     
    while(1)
    {
        /* TODO <INSERT USER APPLICATION CODE HERE> */
            
    }

}

