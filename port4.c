//===========================================================================
// File Name : port4.c
//
// Description: This file contains the initialization of port 4
//
// Author: William Brazil
// Date: August 2020
// Compiler: Built with IAR Embedded Workbench Version: V7.20.1
//===========================================================================

#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"



void Init_Port4(void){
  P4OUT = LOW;          //P4 set Low
  P4DIR = OUTPUT;       //Set P4 direction to output
  
  //P4 Pin 0
  P4SEL0 &= ~RESET_LCD; //RESET_LED GP I/O operation
  P4SEL1 &= ~RESET_LCD; //RESET_LED GP I/O operation
  P4OUT &= ~RESET_LCD;  //Set RESET_LED on (inital value 0)
  P4DIR |= RESET_LCD;   //RESET_LED direction output
  
  //P4 Pin 1
  P4SEL0 &= ~SW1; // SW1 set as I/0
  P4SEL1 &= ~SW1; // SW1 set as I/0
  P4DIR &= ~SW1; // SW1 Direction = input
  P4PUD |= SW1; // Configure pull-up resistor SW1
  P4REN |= SW1; // Enable pull-up resistor SW1
  P4IES |= SW1; // SW1 Hi/Lo edge interrupt
  P4IFG &= ~SW1; // IFG SW1 cleared
  P4IE |= SW1; // SW1 interrupt Enabled
  
  //P4 Pin 2
  P4SEL0 |= UCA1RXD;    //USCI_A1 UART operation
  P4SEL1 &= ~UCA1RXD;   //USCI_A1 UART operation
  
  //P4 Pin 3
  P4SEL0 |= UCA1TXD;    //USCI_A1 UART operation
  P4SEL1 &= ~UCA1TXD;   //USCI_A1 UART operation
  
  //P4 Pin 4
  P4SEL0 &= ~UCB1_CS_LCD; //UCB1_CS_LCD GPIO operation
  P4SEL1 &= ~UCB1_CS_LCD; //UCB1_CS_LCD GPIO operation
  P4OUT |= UCB1_CS_LCD;   //Set UCB1_CS_LCD off (initial value 1)
  P4DIR |= UCB1_CS_LCD;   //UCB1_CS_LCD direction to output.

  //P4 Pin 5
  P4SEL0 |= UCB1CLK;    //UCB1CLK SPI BUS operation
  P4SEL1 &= ~UCB1CLK;   //UCB1CLK SPI BUS operation
  
  //P4 Pin 6
  P4SEL0 |= UCB1SIMO;   //UCB1SIMO SPI BUS operation
  P4SEL1 &= ~UCB1SIMO;  //UCB1SIMO SPI BUS operation
  
  //P4 Pin 7
  P4SEL0 |= UCB1SOMI;   //UCB1SOMI SPI BUS operation
  P4SEL1 &= ~UCB1SOMI;  //UCB1SOMI SPI BUS operation
}