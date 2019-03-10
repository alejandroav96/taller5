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
    PORTA=PORTB=PORTC=0x00;
    LATA=LATB=LATC=0x00;
    ADCON1bits.PCFG=0b1111;
    TRISA=0b0000000;
    TRISB=0b0000011;
    TRISCbits.RC6=0;
    TRISCbits.RC7=1;
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
    CCPR2L = 175;
    CCP2CONbits.DC2B=0b00;
    CCP2CONbits.CCP2M=0b1100;
    /* Bluetooth */
    RCSTA1bits.SPEN=1;
    RCSTA1bits.RX9=0;
    RCSTA1bits.CREN=1;
    TXSTAbits.SYNC=0;
    TXSTAbits.TX9=0;
    TXSTAbits.TXEN=1;
    TXSTAbits.BRGH=1;
    SPBRG=12;
    /* Setup analog functionality and port direction */

    /* Initialize peripherals */
    
    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */
    RCONbits.IPEN=1;
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    INTCONbits.INT0E=1;
    INTCONbits.TMR0IE=1;
    INTCON2bits.TMR0IP=1;
    INTCON2bits.INTEDG0=0;
    INTCON2bits.INTEDG1=0;
    INTCON3bits.INT1IE=1;
    INTCON3bits.INT1IP=1;
    PIE1bits.RCIE=1;
    IPR1bits.RCIP=1;
    
}
void BT_load_char(char byte){
    TXREG = byte;
    while(!TXIF);  
    while(!TRMT);
}
void BT_load_string(char* string){
    while(*string)
    BT_load_char(*string++);
}