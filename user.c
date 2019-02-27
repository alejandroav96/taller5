/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
    PORTA=0x00;
    LATA=0x00; 
    PORTB=0x00;
    LATB=0x00;
    ADCON1bits.PCFG=0b1111;
    TRISA=0b0000000;
    TRISB=0b0000001;
    /* Configuration Timer */
    T0CONbits.T08BIT=1;
    T0CONbits.T0CS=0;
    T0CONbits.PSA=0;
    T0CONbits.T0PS=0b111;
    /* Setup analog functionality and port direction */

    /* Initialize peripherals */
    
    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */
    INTCONbits.GIE=1;
    INTCONbits.INT0E=1;
    INTCONbits.TMR0IE=1;
    INTCON2bits.TMR0IP=1;
    INTCON2bits.INTEDG0=1;
    INTCONbits.RBIE=1;
    INTCON2bits.RBIP=1;
}

