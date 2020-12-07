//===========================================================================
// File Name : init.c
//
// Description: This file contains the initialization of conditions and timers
//
// Author: William Brazil
// Date: September 2020
// Compiler: Built with IAR Embedded Workbench Version: 7.20.1
//===========================================================================
#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"
#include <string.h>


extern char display_line[DISPLAY_ROWS][DISPLAY_COLUMNS];
extern char *display[DISPLAY_ROWS];
extern volatile unsigned int update_display_count;
extern volatile unsigned char update_display;
extern volatile unsigned int Time_Sequence;
unsigned int wheel_on_count;
char wheels_on;
extern volatile unsigned int update_display_count;

void Init_Conditions(void){
  //==============================================================================
  // Interrupts are disabled by default
  enable_interrupts();

  wheels_on = FALSE;
  wheel_on_count = INIT;
  //==============================================================================
}

void Init_Timers(void){
  Init_Timer_B0();
  Init_Timer_B1();
  Init_Timer_B3();
}

void Init_Serial(void){
  Init_Serial_UCA0(HIGHBAUD);
  Init_Serial_UCA1(HIGHBAUD);
}