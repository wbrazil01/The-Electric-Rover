//===========================================================================
// File Name : led.c
//
// Description: This file contains the Initialization for LED's
//
// Author: William Brazil
// Date: August 2020
// Compiler: Built with IAR Embedded Workbench Version: V7.20.1
//===========================================================================
#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"


void Init_LEDs(void){
  //==============================================================================
  // LED Configurations
  //==============================================================================
  // Turns off both LEDs
  P1OUT &= ~RED_LED;
  P6OUT &= ~GRN_LED;
  //==============================================================================
}
