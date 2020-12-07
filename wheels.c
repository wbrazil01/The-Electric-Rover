//===========================================================================
// File Name : wheels.c
//
// Description: This file contains all wheel controls.
//
// Author: William Brazil
// Date: September 2020
// Compiler: Built with IAR Embedded Workbench Version: V7.20.1
//===========================================================================

#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"

extern int spin;
extern int Interval_Counter;

void all_wheels_off(void){
  //Set PWM for all wheels off.
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
}

void forward_slow(void){
  RIGHT_FORWARD_SPEED = WHEEL_ON_50;
  LEFT_FORWARD_SPEED = WHEEL_ON_50 + LEFT_DIFFERENTIAL;
}

void reverse(void){
  RIGHT_REVERSE_SPEED = WHEEL_ON_50;
  LEFT_REVERSE_SPEED = WHEEL_ON_50;
}

void reverse_slow(void){
  RIGHT_REVERSE_SPEED = WHEEL_ON_20;
  LEFT_REVERSE_SPEED = WHEEL_ON_20 + LEFT_DIFFERENTIAL;
}

void stop(void){
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
}

void left_wheel_forward_on(void){
   LEFT_FORWARD_SPEED = WHEEL_ON_20;
}

void left_wheel_reverse_on(void){
  LEFT_REVERSE_SPEED = WHEEL_ON_20;
}

void right_wheel_forward_on(void){
  RIGHT_FORWARD_SPEED = WHEEL_ON_20;
}

void right_wheel_reverse_on(void){
  RIGHT_REVERSE_SPEED = WHEEL_ON_20;
}

void NINETY_RIGHT(int delay){
  switch(delay){
  case FALSE:
    //enable interrupt to turn 90deg
    spin = TRUE;
    Interval_Counter = INIT;
    TB1CCTL2 |= CCIE;
    break;
  case TRUE:
    //delay itself
    for(int j=INIT;j<MAX_COUNT;j++)
      msec_sleep(TEN*ONETHOUSAND);
    //make sure wheels are off
    all_wheels_off();
    
    //enable interrupt to turn 90deg
    spin = TRUE;
    Interval_Counter = INIT;
    TB1CCTL2 |= CCIE;
  }
}

void Forward_On(void){
  left_wheel_forward_on();
  right_wheel_forward_on();
}

void Forward_Move(void){
  forward();
}

void Forward_Off(void){
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
}