//===========================================================================
// File Name : interrupts_ports.c
//
// Description: This file contains all interrupt handlers triggered by SW1/SW2
//
// Author: William Brazil
// Date: September 2020
// Compiler: Built with IAR Embedded Workbench Version: V7.20.1
//===========================================================================


#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include  "macros.h"

extern char display_line[DISPLAY_ROWS][DISPLAY_COLUMNS];
extern char *display[DISPLAY_ROWS];
extern volatile unsigned char display_changed;
volatile unsigned int SW1_DEBOUNCED = FALSE;
volatile unsigned int SW2_DEBOUNCED = FALSE;
volatile unsigned int SW1_DEBOUNCE_COUNT = INIT;
volatile unsigned int SW2_DEBOUNCE_COUNT = INIT;
extern char event;
volatile unsigned int Movement = FALSE;
extern int spin;
char ADC_Channel = INIT;
volatile int ADC_Left_Detect = INIT;
volatile int ADC_Right_Detect = INIT;
volatile int ADC_Thumb = INIT;
char switch_states;

#pragma vector=PORT4_VECTOR
__interrupt void switch1_interrupt(void){
  //==============================================================================
  //  Function Name: switch1_interrupt
  //
  //  Description: Intterupts the processor every time SW1 is pressed
  //
  //  Local Variables: None
  //  Global Variables: SW1_DEBOUNCED, SW1_DEBOUNCE_COUNT, SW1_PRESSED,
  //                    display_changed, display_line[DISPLAY_ROWS][DISPLAY_COLUMNS]
  //
  //  William Brazil
  //  Sept 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  
  // Switch 1
  if (P4IFG & SW1) {
    P1OUT |= RED_LED;   //visual indicator during testing that the code entered interrupt
    
    P4IE &= ~SW1; //disable SW1
    P4IFG &= ~SW1; // IFG SW1 cleared
    SW1_DEBOUNCED = TRUE;  //specify debounce active
    TB0CCR1 = TB0CCR1_INTERVAL; // CCR1
    TB0CCTL1 &= ~CCIFG; //IFG for CCR1 cleared    
    TB0CCTL1 |= CCIE; // CCR1 enable interrupt
    switch_states |= SW1;
  }
}

#pragma vector=PORT2_VECTOR
__interrupt void switch2_interrupt(void){
  //==============================================================================
  //  Function Name: switch2_interrupt
  //
  //  Description: Intterupts the processor every time SW2 is pressed
  //
  //  Local Variables: None
  //  Global Variables: SW2_DEBOUNCED, SW2_DEBOUNCE_COUNT, SW2_PRESSED,
  //                    display_changed, display_line[DISPLAY_ROWS][DISPLAY_COLUMNS]
  //
  //  William Brazil
  //  Sept 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  
  // Switch 2
  if (P2IFG & SW2) {
    P6OUT |= GRN_LED; //visual indicator during testing that the code entered interrupt
    
    P2IE &= ~SW2; //disable SW2
    P2IFG &= ~SW2; // IFG SW1 cleared
    SW2_DEBOUNCED = TRUE;
    TB0CCR1 = TB0CCR1_INTERVAL; // CCR1
    TB0CCTL1 &= ~CCIFG; //IFG for CCR1 cleared    
    TB0CCTL1 |= CCIE; // CCR1 enable interrupt
    switch_states |= SW2;
  }
}

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
  //==============================================================================
  //  Function Name: ADC_ISR
  //
  //  Description: Intterupts the processor every time an ADC conversion is done
  //
  //  Local Variables: None
  //  Global Variables: ADC_Left_Detect, ADC_Right_Detect, ADC_Channel, ADC_Thumb,
  //
  //  William Brazil
  //  Oct 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
  case ADCIV_NONE:
    break;
  case ADCIV_ADCOVIFG:  // When a conversion result is written to the ADCMEM0
                        // before its previous conversion result was read.
    break;
  case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
    break;
  case ADCIV_ADCHIIFG: // Window comparator interrupt flags
    break;
  case ADCIV_ADCLOIFG: // Window comparator interrupt flag
    break;
  case ADCIV_ADCINIFG: // Window comparator interrupt flag
    break;
  case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
    ADCCTL0 &= ~ADCENC; // Disable ENC bit.
    switch (ADC_Channel++){
    case Left_Detector:                  // Channel A2 Interrupt
      ADCMCTL0 &= ~ADCINCH_2;   // Disable Last channel A2
      ADCMCTL0 |= ADCINCH_3;    // Enable Next channel A3
      ADC_Left_Detect = ADCMEM0; // Move result into Global
      ADC_Left_Detect = ADC_Left_Detect >> 1; // Divide the result by 4
      ADCCTL0 |= ADCSC;
      break;
    case Right_Detector:
      ADCMCTL0 &= ~ADCINCH_3;
      ADCMCTL0 |= ADCINCH_2;
      ADC_Right_Detect = ADCMEM0;
      ADC_Right_Detect = ADC_Right_Detect >> 1;
      ADCCTL0 |= ADCSC;
      break;
    case Thumbwheel:
      //ADCMCTL0 &= ~ADCINCH_5;
      //ADCMCTL0 |= ADCINCH_9;
      //ADC_Thumb = ADCMEM0;      // Channel A5
      //ADC_Thumb = ADC_Thumb >> 2;
      //HEXtoBCD(ADC_Thumb);
      //adc_line4(INIT);
      ADC_Channel=INIT;
      break;
    default:
      break;
    }
    ADCCTL0 |= ADCENC;          // Enable Conversions
    break;
  default:
    break;
  }
}