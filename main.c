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
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#define time 0.131072
/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
int read = 0;
int limit = 0;
char Buffer[20];
char send[20];
float kp = 12;
float ki = 0;
float kd = 0;
int currentSpeed;
int refSpeed = 3600;
int timer = 0;
int count = 0;
int count2 = 0;
int plus = 0;
float errora = 0;
float errorv = 0;
/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void) 
{   
    /* Configure the oscillator for the device */
    ConfigureOscillator();
    /* Initialize I/O and Peripherals for application */
    InitApp();
    /* TODO <INSERT USER APPLICATION CODE HERE> */
    int j = 0;
    while(1) 
    {   
        if (read){
            read = 0;
            char du[20] = "";
            for(j=1; j<limit; j++){
                du[j-1] = Buffer[j];
            }
            switch (Buffer[0]){
                case 'V':
                    refSpeed = atoi(du);
                    break;
                case 'P':
                    kp = atof(du);
                    break;
                case 'I':
                    ki = atof(du);
                    break;
                case 'D':
                    kd = atof(du);
                    break;
            }
        }
        if (timer){
            count2 = count;
            timer = count = 0;            
            sprintf(send, "#%d", count2);
            BT_load_string(send);
            currentSpeed = (60.0*count2/time);
            errora = (refSpeed-currentSpeed)/10000.0;
            plus = (kp*errora) + (kd*60.0*((errora-errorv)/time)) + (ki*time*((errora+errorv)/120.0));
            if (plus>=20) {
                plus=8;
            } else if (plus<=-20) {
                plus=-8;
            }
            CCPR2L -= plus;
            if(CCPR2L>=255){
                CCPR2L=254;
            } else if (CCPR2L<=0){
                CCPR2L=1;
            }
            errorv = errora;
        }
    }
}