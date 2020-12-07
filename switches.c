//===========================================================================
// File Name : switches.c
//
// Description: This file contains different switches process for SW1 and SW2
//
// Author: William Brazil
// Date: September 2020
// Compiler: Built with IAR Embedded Workbench Version: V7.20.1
//===========================================================================


#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"

extern char display_line[DISPLAY_ROWS][DISPLAY_COLUMNS];
extern volatile unsigned char display_changed;
extern volatile unsigned char display_changed;
extern char start_moving;
extern unsigned int moving;
extern char event;
extern unsigned int repeat;
extern volatile unsigned int SW1_PRESSED;
extern volatile unsigned int SW2_PRESSED;
extern volatile unsigned int SW1_DEBOUNCED;
extern volatile unsigned int SW2_DEBOUNCED;
extern volatile unsigned int SW1_DEBOUNCE_COUNT;
extern volatile unsigned int SW2_DEBOUNCE_COUNT;
int IR_State = ON;
extern int FoundLine;
extern char switch_states;
extern char port_command[16];
extern char start_command[11];

void Switches_Process(void){
  //==============================================================================
  //  Function Name: Swtiches_Process
  //
  //  Description: Handles the SW1 debounce counter after the debounce delay is
  //  over it reenables the respective SW and re-enables the blinking LCD
  //
  //  Local Variables: None
  //  Global Variables: SW1_DEBOUNCE_COUNT, SW1_DEBOUNCED, SW1_PRESSED, 
  //                    display_line[DISPLAY_ROWS][DISPLAY_COLUMNS], display_changed
  //
  //  William Brazil
  //  Sept 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  if(switch_states & SW1){              
    switch_states &= ~SW1;      //clear flag bit
    
    //FUNCITON==========================================
    
    
    for(int z = INIT; z<sizeof(port_command);z++)
        out_character(port_command[z]);
    
//    for(int i=INIT;i<MAX_COUNT;i++)            //small delay
//      msec_sleep(FOUR*ONETHOUSAND);  
//    
//    FoundLine = FALSE;
//    
//    //search for blkline
//    Search();                                   
//    //stop
//    all_wheels_off();
//    //display
//    strcpy(display_line[LINE1], "Searching.");
//    update_string(display_line[LINE1], LINE1);
//    display_changed = TRUE;
//    //movement
//    forward_slow();
//    
//    display_changed = TRUE;
  }
  
  if(switch_states & SW2){
    switch_states &= ~SW2;
    
    //FUNCITON==========================================
    
    switch(IR_State){
    case OFF:
      P2OUT &= ~IR_LED;
      emitter_state(OFF);
      IR_State = ON;
      break;
    case ON:
      P2OUT |= IR_LED;
      emitter_state(ON);
      IR_State = OFF;
      break;
    default:
      break;
    }
  }
}

void enable_switch_SW1(void){

}

void enable_switch_SW2(void){
  
}

void Init_Switches(void){
  
}