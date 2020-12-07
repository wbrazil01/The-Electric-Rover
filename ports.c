//===========================================================================
// File Name : ports.c
//
// Description: This file contains the Initialization for all port pins
//
// Author: William Brazil
// Date: August 2020
// Compiler: Built with IAR Embedded Workbench Version: V7.20.1
//===========================================================================
#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"

void Init_Ports(void){
  //===========================================================================
  // Init_Ports
  // Purpose: Initialize all Ports
  //===========================================================================
  Init_Port1();
  Init_Port2();
  Init_Port3();
  Init_Port4();
  Init_Port5();
  Init_Port6();
}