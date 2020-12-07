//===========================================================================
// File Name : interrupts_timers.c
//
// Description: This file contains all interrupt handlers triggered by TimerB0
//
// Author: William Brazil
// Date: September 2020
// Compiler: Built with IAR Embedded Workbench Version: V7.20.1
//===========================================================================

#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include  "macros.h"

unsigned int interrupt_counter = INIT;
int Interval_Counter = INIT;
unsigned int update_display_counter;
int spin = FALSE;
extern volatile unsigned char update_display;
unsigned int toggle = ON;
extern volatile char one_time;
extern volatile unsigned int Time_Sequence;
extern volatile unsigned int FIFTY_MS_INTERVALS;
extern volatile unsigned int ONE_S_INTERVALS;
extern volatile unsigned int FIVE_MS_INTERVALS;
extern volatile unsigned int SW1_PRESSED;
extern volatile unsigned int SW2_PRESSED;
extern volatile unsigned int SW1_DEBOUNCED;
extern volatile unsigned int SW2_DEBOUNCED;
extern volatile unsigned int SW1_DEBOUNCE_COUNT;
extern volatile unsigned int SW2_DEBOUNCE_COUNT;
extern volatile unsigned int Movement;
extern char display_line[DISPLAY_ROWS][DISPLAY_COLUMNS];
extern volatile unsigned char display_changed;
extern volatile int Average;
extern int FoundLine;
extern volatile int ADC_Left_Detect;
extern volatile int ADC_Right_Detect;
int pause = TRUE, startup = TRUE;
extern char baudrate[TEN];
extern int TCPtimer;
int TCPcounter = INIT;
int timercounter = INIT;
int timertensec = INIT;
int timermin = INIT;
int timertenmin = INIT;
int tenmin = FALSE;
int min = FALSE;
int tensec = FALSE;
int sec = FALSE;
int skip = FALSE;
char displaytimer[ELEVEN] = "  00:00   ";
extern char TCPinstruction;
int followcounter = INIT;
extern int travelcount;


#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
  //==============================================================================
  //  Function Name: Timer0_B0_ISR
  //
  //  Description: Intterupts the processor every 200msec.
  //
  //  Local Variables: None
  //  Global Variables: Time_Sequence, one_time, update_display_counter,
  //                    update_display
  //
  //  William Brazil
  //  Sept 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  
  if(travelcount == TRUE){
    if(followcounter++ == FIFTY){
      TCPinstruction = 'C';
      processTCP();
    }
  }
  
  if(display_changed){          //EVERY 200MSEC
    display_changed = INIT;
    update_display = TRUE;
  }
  
  
  TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0
}


#pragma vector = TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
  //==============================================================================
  //  Function Name: Timer0_B1_ISR
  //
  //  Description: Uses TimerB0's CCR1 and CCR2. They interrupt the processor
  //  every 1sec and 100msec respectively.
  //
  //  Local Variables: None
  //  Global Variables: SW1_DEBOUNCED, SW1_DEBOUNCE_COUNT, SW2_DEBOUNCED,
  //                    SW2_DEBOUNCE_COUNT, interrupt_counter
  //
  //  William Brazil
  //  Sept 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  switch(__even_in_range(TB0IV,14)){
  case 0: 
    break; // No interrupt
  case 2: // CCR1 used
    if(SW1_DEBOUNCED){                          //SW1 debounce counter
      if(DELAY <= SW1_DEBOUNCE_COUNT++){
        P4IE |= SW1;            //re-enable switch
        P4IFG &= ~SW1;          //clear switch flag
        SW1_DEBOUNCED = FALSE;
        SW1_DEBOUNCE_COUNT = INIT;
      }
    }
    
    if(SW2_DEBOUNCED){                          //SW2 debounce
      if(DELAY <= SW2_DEBOUNCE_COUNT++){
        P2IE |= SW2;            //re-enable switch
        P4IFG &= ~SW2;          //clear flag        
        SW2_DEBOUNCED = FALSE;
        SW2_DEBOUNCE_COUNT = INIT;
      }
    }
    
    if (!(SW1_DEBOUNCED) && !(SW2_DEBOUNCED)) { //if both 0, disable this interrupt
      TB0CCTL1 &= ~CCIE;            // CCR1 disable interrupt
    }
    
    TB0CCR1 += TB0CCR1_INTERVAL; // Add Offset to TBCCR1
    break;
  case 4: // CCR2 used
    P5OUT |= IOT_RESET;
    P5DIR &= ~IOT_RESET;
    TB0CCR2 &= ~CCIFG;
    TB0CCTL2 &= ~CCIE; 
    TB0CCR2 += TB0CCR2_INTERVAL; // Add Offset to TBCCR2
    break;
  case 14: // overflow
    break;
  default: break;
  }
}

#pragma vector=TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void){
  
  //==============================================================================
  //  Function Name: Timer1_B0_ISR
  //
  //  Description: Uses TimerB1's CCR0. They interrupt the processor
  //  every 50msec
  //
  //  Local Variables: None
  //  Global Variables: None
  //
  //  William Brazil
  //  Oct 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  
  ADCCTL0 |= ADCSC;           // Start next sample
  TB1CCR0 += TB1CCR0_INTERVAL;
}

#pragma vector = TIMER1_B1_VECTOR
__interrupt void TIMER1_B1_ISR(void){
  //==============================================================================
  //  Function Name: Timer1_B1_ISR
  //
  //  Description: Uses TimerB1's CCR1 and CCR2. They interrupt the processor
  //  every 100msec and 604msec respectively
  //
  //  Local Variables: j
  //  Global Variables: display_line[DISPLAY_ROWS][DISPLAY_COLUMNS],
  //                    display_changed, pause, spin, interrupt_counter,
  //                    interval_counter
  //
  //  William Brazil
  //  Oct 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  
  switch(__even_in_range(TB1IV,14)){
  case 0: 
    break; // No interrupt
  case 2: // CCR1 used
    switch(FoundLine){
    case FALSE:
      chkLine();
      break;
    case TRUE:
      //interrupt stuff
      ADCCTL0 |= ADCENC;        // ADC disable conversion.
      TB1CCR1 &= ~CCIFG;        //clear ccr0 interrupt flag
      TB1CCTL1 &= ~CCIE;        //disable current interrupt        
      ADCCTL0 |= ADCSC;         //start adc conversion
      break;
    case FOLLOWING:
        line_follow();
      break;
    case EXIT:
      forward_slow();
      
      for(int i=INIT;i<MAX_COUNT;i++)            //small delay
        msec_sleep(TEN*ONETHOUSAND);
      
      strcpy(display_line[LINE1], " BL STOP  ");
      update_string(display_line[LINE1], LINE1);
      Display_Update(0,0,0,0);
      
      all_wheels_off();
      
      TB1CCR1 &= ~CCIFG;        //clear ccr0 interrupt flag
      TB1CCTL1 &= ~CCIE;        //disable current interrupt  
      break;
    default:
      break;
    }
    TB1CCR1 += TB1CCR1_INTERVAL; // Add Offset to TBCCR1
    break;
  case 4: // CCR2 used
    if(skip == FALSE){
      if(timercounter < 10){
        displaytimer[SECPL] = timercounter++ + ZERO;
      }else{
        timertensec++;
        if(timertensec < 6){
          displaytimer[TENSECPL] = timertensec + ZERO;
          displaytimer[SECPL] = ZERO;
          timercounter = ONE;
        }else{
          timermin++;
          displaytimer[MINPL] = timermin + ZERO;
          displaytimer[SECPL] = ZERO;
          displaytimer[TENSECPL] = ZERO;
          timercounter = ONE;
          timertensec = INIT;
        }
      }
      
      if(timermin < 10){
        displaytimer[MINPL] = timermin + ZERO;
      }else{
        timertenmin++;
        displaytimer[TENMINPL] = timertenmin + ZERO;
        displaytimer[MINPL] = ZERO;
        timermin = INIT;
      }
      
      display_timer();
      skip = TRUE;
    }else
      skip = FALSE;
    
    TB1CCR2 += TB1CCR2_INTERVAL; // Add Offset to TBCCR2
    break;
  case 14: // overflow
    break;
  default: break;
  }
}