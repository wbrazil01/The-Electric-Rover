//===========================================================================
// File Name : line.c
//
// Description: This file contains anything related to finding/following
//              the black line
//
// Author: William Brazil
// Date: October 2020
// Compiler: Built with IAR Embedded Workbench Version: V7.20.1
//===========================================================================

#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include  "macros.h"

int FoundLine = FALSE;
int Average = INIT;
int lastAvg = ONETHOUSAND;
extern volatile int ADC_Left_Detect;
extern volatile int ADC_Right_Detect;
extern volatile int ADC_Thumb;
extern char display_line[DISPLAY_ROWS][DISPLAY_COLUMNS];
extern volatile unsigned char display_changed;
int Left;
int Right;
extern char TCPinstruction;



void Search(void){
  //==============================================================================
  //  Function Name: Search
  //
  //  Description: Initializes IR_LED and starts the FindLine movement
  //
  //  Local Variables: None
  //  Global Variables: lastAvg
  //
  //  William Brazil
  //  Oct 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  P2OUT |= IR_LED;      //turn on IR emitter
  
  lastAvg = ONETHOUSAND;
  
  TB1CCTL1 |= CCIE;     //enable FoundLine checker
}

void chkLine(void){
  //==============================================================================
  //  Function Name: chkLine
  //
  //  Description: Finds the difference between the last IR_Emitter reading and
  //               the new one in order to detect a black line        
  //
  //  Local Variables: None
  //  Global Variables: lastAvg, Average, Left, Right, ADC_Left_Detect,
  //                    ADC_Right_Detect, and FoundLine.
  //
  //  William Brazil
  //  Oct 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  Left = ADC_Left_Detect;
  Right = ADC_Right_Detect;
  
  Average = (Left + Right) >> ONE;
  
  if(Average > lastAvg){
    FoundLine = TRUE;
    
    //stop moving
    all_wheels_off();    
    
    if(TCPinstruction == NULL){
      TCPinstruction = 'Y';
      processTCP();
    }else if(TCPinstruction == ZERO){
      TCPinstruction = 'Z';
      processTCP();
    }
  }
  lastAvg = Average + SEVENTY;
}

void Black_Line(void){
  HEXtoBCD(ADC_Left_Detect, L); // Convert result to String
  HEXtoBCD(ADC_Right_Detect, R);
}

void line_follow(void){
  //==============================================================================
  //  Function Name: line_follow
  //
  //  Description: Turns the car depending on which side it detects a different in
  //               the emitters
  //
  //  Local Variables: None
  //  Global Variables: Left, Right, ADC_Left_Detect, and ADC_Right_Detect
  //
  //  William Brazil
  //  Nov 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  Left = ADC_Left_Detect;
  Right = ADC_Right_Detect;
  
  if(Left + FIFTY < Right){
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_ON_15;
  }else if(Right + FIFTY < Left){
    RIGHT_FORWARD_SPEED = WHEEL_ON_15;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
  }else if((Right > ONEHUNDRED) && (Left > ONEHUNDRED)){
    RIGHT_FORWARD_SPEED = WHEEL_ON_10;
    LEFT_FORWARD_SPEED = WHEEL_ON_10;
  }
}