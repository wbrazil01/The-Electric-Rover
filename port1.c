//===========================================================================
// File Name : port1.c
//
// Description: This file contains the initialization of port 1
//
// Author: William Brazil
// Date: August 2020
// Compiler: Built with IAR Embedded Workbench Version: V7.20.1
//===========================================================================
#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"

void Init_Port1(void){
  P1OUT = LOW;                  //P1 set Low
  P1DIR = OUTPUT;               //Set P1 direction to output
  
  //P1 Pin 0
  P1SEL0 &= ~RED_LED;           //RED_LED GPIO operation
  P1SEL1 &= ~RED_LED;           //RED_LED GPIO operation
  P1OUT &= ~RED_LED;             //Set LED off
  P1DIR |= RED_LED;             //RED_LED direction output
  
  //P1 Pin 1
  P1SEL0 |= A1_SEEED;           //ADC input for A1_SEED
  P1SEL1 |= A1_SEEED;           //ADC input for A1_SEED
  
  //P1 Pin 2 
  P1SEL0 |= V_DETECT_L;         //ADC input for V_DETECT_L
  P1SEL1 |= V_DETECT_L;         //ADC input for V_DETECT_L
  
  //P1 Pin 3 
  P1SEL0 |= V_DETECT_R;         //ADC input for V_DETECT_R
  P1SEL1 |= V_DETECT_R;         //ADC input for V_DETECT_R
  
  //P1 Pin 4 (NOT SURE)
  P1SEL0 |= A4_SEEED;           //ADC input for A4_SEEED
  P1SEL1 |= A4_SEEED;           //ADC input for A4_SEEED
  
  
  //P1 Pin 5 (NOT SURE)
  P1SEL0 |= V_THUMB;            //ADC input for V_THUMB
  P1SEL1 |= V_THUMB;            //ADC input for V_THUMB
  
  //P1 Pin 6 
  P1SEL0 |= UCA0RXD;            //set UCA0RXD operation
  P1SEL1 &= ~UCA0RXD;           //set UCA0RXD operation
  
  //P1 Pin 7 
  P1SEL0 |= UCA0TXD;            //set UCA0TXD operation
  P1SEL1 &= ~UCA0TXD;           //set UCA0TXD operation
  
}