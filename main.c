//==============================================================================
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  William Brazil
//  Nov 2020
//  Built with IAR Embedded Workbench Version: V(7.20.1)
//==============================================================================

#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include  "macros.h"

  // Global Variables
extern char display_line[DISPLAY_ROWS][DISPLAY_COLUMNS];
extern char *display[DISPLAY_ROWS];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
volatile unsigned int Time_Sequence;
volatile char one_time;
char start_moving;
unsigned int moving;
unsigned int Last_Time_Sequence;
unsigned int cycle_time;
unsigned int time_change;
char event;
extern char state;
extern int IR_State;

void main(void){
//==============================================================================
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//==============================================================================
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;

//Initialize Peripherals
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timers();                       // Initialize Timers
  Init_ADC();                          // Initialize ADC
  Init_DAC();
  Init_LCD();                          // Initialize LCD
  Init_Serial();
  
  //Boot Text
  BootText();
  
  //Init Emitter
//  emitter_state(OFF);
//  IR_State = ON;

  
//==============================================================================
// Begining of the "While" Operating System
//==============================================================================
  while(ALWAYS) {                      // Can the Operating system run
    Switches_Process(); // Check for switch state change
    Display();
    Black_Line();
    IOT();
    
  } // End of While Always
//==============================================================================
} // End of main();