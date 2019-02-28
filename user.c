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
extern int press;
void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
    PORTA=0x00;
    LATA=0x00; 
    PORTB=0x00;
    LATB=0x00;
    ADCON1bits.PCFG=0b1111;
    TRISA=0b0000000;
    TRISB=0b0000011;
    /* Configuration Timer */
    T0CONbits.T08BIT=1;
    T0CONbits.T0CS=0;
    T0CONbits.PSA=0;
    T0CONbits.T0PS=0b111;
    /* Timer 2 */
    T2CONbits.T2CKPS=0b10;
    T2CONbits.TMR2ON=1;
    /* PWM */
    PR2 = 255;
    CCPR2L = 127;
    CCP2CONbits.DC2B=0b11;
    CCP2CONbits.CCP2M=0b1100;
    
    /* Setup analog functionality and port direction */

    /* Initialize peripherals */
    
    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */
    INTCONbits.GIE=1;
    INTCONbits.INT0E=1;
    INTCONbits.TMR0IE=1;
    INTCON2bits.TMR0IP=1;
    INTCON2bits.INTEDG0=1;
    INTCON2bits.INTEDG1=0;
    INTCON3bits.INT1IE=1;
    INTCON3bits.INT1IP=1;
    
}
void pwm(int cycle){
    if (cycle==1) {
        if (CCPR2L!=0) {
            CCPR2L = CCPR2L-1;
        } else {
            T0CONbits.TMR0ON=0;
            INTCON2bits.INTEDG0=1;
            press=1;
        }
    } else if (cycle==2) {
        if (CCPR2L!=255) {
            CCPR2L = CCPR2L+1;
        } else {
            T0CONbits.TMR0ON=0;
            INTCON2bits.INTEDG0=1;
            press=1;
        }
    }
}
