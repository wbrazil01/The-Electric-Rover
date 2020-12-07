//===========================================================================
// File Name : port5.c
//
// Description: This file contains the initialization of port 5
//
// Author: William Brazil
// Date: August 2020
// Compiler: Built with IAR Embedded Workbench Version: V7.20.1
//===========================================================================

#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"

void Init_Port5(void){
  P5OUT = LOW;          //P5 set low
  P5DIR = OUTPUT;       //Set P5 direction to output
  
  //P5 pin 0
  P5SEL0 &= ~IOT_RESET;  //IOT_RESET GPIO operation
  P5SEL1 &= ~IOT_RESET;  //IOT_RESET GPIO operation
  P5DIR &= ~IOT_RESET;  //IOT_RESET input
  
  //P5 pin 1
  P5SEL0 |= V_BAT;     //ADC input for V_BAT
  P5SEL1 |= V_BAT;     //ADC input for V_BAT
  
  //P5 pin 2
  P5SEL0 &= ~IOT_PROG_SEL; //IOT_PROG_SEL GPIO operation
  P5SEL1 &= ~IOT_PROG_SEL; //IOT_PROG_SEL GPIO operation
  P5DIR &= ~IOT_PROG_SEL; //IOT_PROG_SEL input
  
  //P5 pin 3
  P5SEL0 &= ~V_3_3;     //V_3_3 GPIO operation
  P5SEL1 &= ~V_3_3;     //V_3_3 GPIO operation
  P5DIR &= ~V_3_3;     //V_3_3 input
  
  //P5 pin 4
  P5SEL0 &= ~IOT_PROG_MODE; //IOT_PROG_MODE GPIO operation
  P5SEL1 &= ~IOT_PROG_MODE; //IOT_PROG_MODE GPIO operation
  P5DIR &= ~IOT_PROG_MODE; //IOT_PROG_MODE input
}