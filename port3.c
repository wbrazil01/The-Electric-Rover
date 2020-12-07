//===========================================================================
// File Name : port3.c
//
// Description: This file contains the initialization of port 3
//
// Author: William Brazil
// Date: August 2020
// Compiler: Built with IAR Embedded Workbench Version: V7.20.1
//===========================================================================
#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"

void Init_Port3(void){
  P3OUT = LOW;          // P3 set Low
  P3DIR = OUTPUT;       // Set P3 direction to output
  
  //P3 Pin 0
  P3SEL0 &= ~TEST_PROBE; //TEST_PROBE GPIO operation
  P3SEL1 &= ~TEST_PROBE; //TEST_PROBE GPIO operation
  P3DIR &= ~TEST_PROBE; //TEST_PROBE input
  
  //P3 Pin 1
  P3SEL0 &= ~CHECK_BAT; //CHECK_BAT GPIO operation
  P3SEL1 &= ~CHECK_BAT; //CHECK_BAT GPIO operation
  P3DIR &= ~CHECK_BAT; //CHECK_BAT input
  
  //P3 Pin 2
  P3SEL0 &= ~OA2N; //OA2N GPIO operation
  P3SEL1 &= ~OA2N; //OA2N GPIO operation
  P3DIR &= ~OA2N; //OA2N input
  
  //P3 Pin 3
  P3SEL0 &= ~OA2P; //OA2P GPIO operation
  P3SEL1 &= ~OA2P; //OA2P GPIO operation
  P3DIR &= ~OA2P; //OA2P input
  
  //P3 Pin 4
  P3SEL0 &= ~SMCLK_OUT; //SMCLK_OUT GPIO operation
  P3SEL1 &= ~SMCLK_OUT; //SMCLK_OUT GPIO operation
  P3DIR &= ~SMCLK_OUT; //SMCLK_OUT input
  
  //P3 Pin 5
  P3SEL0 &= ~DAC_CNTL; //DAC_CNTL GPIO operation
  P3SEL1 &= ~DAC_CNTL; //DAC_CNTL GPIO operation
  P3DIR &= ~DAC_CNTL; //DAC_CNTL input
  
  //P3 Pin 6
  P3SEL0 &= ~IOT_LINK; //IOT_LINK GPIO operation
  P3SEL1 &= ~IOT_LINK; //IOT_LINK GPIO operation
  P3DIR &= ~IOT_LINK; //IOT_LINK input
  
  //P3 Pin 7
  P3SEL0 &= ~P3_7; //P3_7 GPIO operation
  P3SEL1 &= ~P3_7; //P3_7 GPIO operation
  P3DIR &= ~P3_7; //P3_7 input
}