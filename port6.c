//===========================================================================
// File Name : port6.c
//
// Description: This file contains the initialization of port 6
//
// Author: William Brazil
// Date: August 2020
// Compiler: Built with IAR Embedded Workbench Version: V7.20.1
//===========================================================================

#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"

void Init_Port6(void){
  P6OUT = LOW;          //P6 set low
  P6DIR = INPUT;       //Set P6 direction to output
  
  //P6 pin 0
  P6SEL0 |= R_FORWARD; //R_FORWARD GPIO operation
  P6SEL1 &= ~R_FORWARD; //R_FORWARD GPIO operation
  P6DIR |= R_FORWARD; //R_FORWARD output
  
  //P6 pin 1
  P6SEL0 |= ~L_FORWARD; //L_FORWARD GPIO operation
  P6SEL1 &= ~L_FORWARD; //L_FORWARD GPIO operation
  P6DIR |= L_FORWARD; //L_FORWARD output
    
  //P6 pin 2
  P6SEL0 |= ~R_REVERSE; //R_REVERSE GPIO operation
  P6SEL1 &= ~R_REVERSE; //R_REVERSE GPIO operation
  P6DIR |= R_REVERSE; //R_REVERSE output
  
  //P6 pin 3
  P6SEL0 |= ~L_REVERSE; //L_REVERSE GPIO operation
  P6SEL1 &= ~L_REVERSE; //L_REVERSE GPIO operation
  P6DIR |= L_REVERSE; //L_REVERSE output
    
  //P6 pin 4
  P6SEL0 &= ~LCD_BACKLITE; //LCD_BACKLITE GPIO operation
  P6SEL1 &= ~LCD_BACKLITE; //LCD_BACKLITE GPIO operation
  P6OUT = LCD_BACKLITE; //LCD_BACKLITE ON
  P6DIR |= LCD_BACKLITE; //LCD_BACKLITE ouput
    
  //P6 pin 5
  P6SEL0 &= ~P6_5;      //P6_5 GPIO operation
  P6SEL1 &= ~P6_5;      //P6_5 GPIO operation
  P6DIR &= ~P6_5;      //P6_5 input
    
  //P6 pin 6
  P6SEL0 &= ~GRN_LED;   //GRN_LED GPIO operation
  P6SEL1 &= ~GRN_LED;   //GRN_LED GPIO operation
  P6OUT &= ~GRN_LED;    //GRN_LED on
  P6DIR |= GRN_LED;   //GRN_LED output
}