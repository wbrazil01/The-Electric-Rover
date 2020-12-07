//===========================================================================
// File Name : port2.c
//
// Description: This file contains the initialization of port 2
//
// Author: William Brazil
// Date: August 2020
// Compiler: Built with IAR Embedded Workbench Version: V7.20.1
//===========================================================================
#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"

void Init_Port2(void){
//==============================================================================
  P2OUT = LOW;          // P2 set Low
  P2DIR = OUTPUT;       // Set P2 direction to output
  
  //P2 Pin 0
  P2SEL0 &= ~P2_0;      // P2_0 GPIO operation
  P2SEL1 &= ~P2_0;      // P2_0 GPIO operation
  P2DIR &= ~P2_0;       // Direction = input
  
  //P2 Pin 1
  P2SEL0 &= ~IR_LED;    // IR_LED GPIO operation
  P2SEL1 &= ~IR_LED;    // IR_LED GPIO operation
  P2OUT &= ~IR_LED;     // Initial Value = OFF
  P2DIR |= IR_LED;      // Direction = output
  
  //P2 Pin 2
  P2SEL0 &= ~P2_2;      // P2_2 GPIO operation
  P2SEL1 &= ~P2_2;      // P2_2 GPIO operation
  P2DIR &= ~P2_2;       // Direction = input
  
  //P2 Pin 3
  P2SEL0 &= ~SW2;       // SW2 Operation
  P2SEL1 &= ~SW2;       // SW2 Operation
  P2DIR &= ~SW2;        // Direction = input
  P2PUD |= SW2;         // Configure pullup resistor
  P2REN |= SW2;         // Enable pullup resistor
  P2IES |= SW2;         // P2.0 Hi/Lo edge interrupt
  P2IFG &= ~SW2;        // Clear all P2.6 interrupt flags
  P2IE |= SW2;          // P2.6 interrupt enabled
  
  //P2 Pin 4
  P2SEL0 &= ~P2_4;      // P2_4 GPIO operation
  P2SEL1 &= ~P2_4;      // P2_4 GPIO operation
  P2DIR &= ~P2_4;       // Direction = input
  
  //P2 Pin 5
  P2SEL0 &= ~P2_5;      // P2_5 GPIO operation
  P2SEL1 &= ~P2_5;      // P2_5 GPIO operation
  P2DIR &= ~P2_5;       // Direction = input
  
  //P2 Pin 6
  P2SEL0 &= ~LFXOUT;    // LFXOUT Clock operation
  P2SEL1 |= LFXOUT;     // LFXOUT Clock operation
  
  //P2 Pin 7
  P2SEL0 &= ~LFXIN;     // LFXIN Clock operation
  P2SEL1 |= LFXIN;      // LFXIN Clock operation
//==============================================================================
}
