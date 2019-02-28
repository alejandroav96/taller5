/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#define _XTAL_FREQ 2000000
/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
int count=0;
int press=0;
/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
int upDown=1;
int i;
void main(void) 
{   
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();
    
    /* TODO <INSERT USER APPLICATION CODE HERE> */
    while(1) 
    {   
        if(press) {
            press=0;
            if (upDown) {
                if(count>8){
                    while(press==0) {
                        pwm(2);
                        __delay_ms(20);
                    }
                } else {
                    while(press==0) {
                        pwm(1);
                        __delay_ms(20);
                    }
                }
                upDown=0;
            } else {
                upDown=1;
                pwm(0);
            }
        }
    }

}