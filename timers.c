//===========================================================================
// File Name : timers.c
//
// Description: This file contains the Initialization of TimerB0 and 
// a 5ms delay function
//
// Author: William Brazil
// Date: September 2020
// Compiler: Built with IAR Embedded Workbench Version: V7.20.1
//===========================================================================


#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include  "macros.h"

extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
volatile unsigned int FIFTY_MS_INTERVALS = INIT;
volatile unsigned int ONE_S_INTERVALS = INIT;
volatile unsigned int FIVE_MS_INTERVALS = INIT;
int DAC_data;


void Init_Timer_B0(void) {
  //==============================================================================
  //  Function Name: Init_Timer_B0
  //
  //  Description: Initializes TimerB0 and sets up both B0_0, B0_1-B0_2 
  //  and overflow
  //
  //  Local Variables: None
  //  Global Variables: None
  //
  //  William Brazil
  //  Sept 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  
  TB0CTL = TBSSEL__SMCLK;        // SMCLK source
  TB0CTL |= TBCLR;               // Resets TB0R, clock divider, count direction
  TB0CTL |= MC_2;      // Continuous up
  TB0CTL |= ID__8;               // Divide clock by 8

  TB0EX0 = TBIDEX__8;             // Divide clock by an additional 8

  TB0CCR0 = TB0CCR0_INTERVAL;    // CCR0
  TB0CCR0 &= ~CCIFG;
  TB0CCTL0 |= CCIE;              // CCR0 enable interrupt
  
  TB0CCR2 &= ~CCIFG;
  TB0CCTL2 |= CCIE;            //CCR2 disable interrupt
  
  TB0CTL &= ~TBIE;               // Disable Overflow Interrupt
  TB0CTL &= ~TBIFG;              // Clear Overflow Interrupt flag
  //TB0CCR1 = TB0CCR1_INTERVAL;    // CCR1

}

void Init_Timer_B1(void){
  //==============================================================================
  //  Function Name: Init_Timer_B1
  //
  //  Description: Initializes TimerB1 and sets up both B1_0, B1_1-B1_2 
  //  and overflow
  //
  //  Local Variables: None
  //  Global Variables: None
  //
  //  William Brazil
  //  Oct 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  TB1CTL = TBSSEL__SMCLK;        // SMCLK source
  TB1CTL |= TBCLR;               // Resets TB0R, clock divider, count direction
  TB1CTL |= MC_2;               // Continuous up
  TB1CTL |= ID__8;               // Divide clock by 8

  TB1EX0 = TBIDEX__8;             // Divide clock by an additional 8

  TB1CCR0 = TB1CCR0_INTERVAL;    // CCR0
  TB1CCR0 &= ~CCIFG;
  TB1CCTL0 &= ~CCIE;              // CCR0 disables interrupt
  
  TB1CCR1 = TB1CCR1_INTERVAL;
  TB1CCR1 &= ~CCIFG;
  TB1CCTL1 &= ~CCIE;            //CCR1 disables interrupt    
  
  TB1CCR2 = TB1CCR2_INTERVAL;
  TB1CCR2 &= ~CCIFG;
  TB1CCTL2 &= ~CCIE;
  
  TB1CTL &= ~TBIE;               // Disable Overflow Interrupt
  TB1CTL &= ~TBIFG;              // Clear Overflow Interrupt flag
}


void Init_Timer_B3(void){
  //==============================================================================
  //  Function Name: Init_Timer_B3
  //
  //  Description: Initialized TimerB3 and CCR0, CCR1, CCR2, CCR3, and CCR4.
  //
  //  Local Variables: None
  //  Global Variables: None
  //
  //  William Brazil
  //  Sept 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  TB3CTL = TBSSEL__SMCLK; // SMCLK
  TB3CTL |= MC__UP; // Up Mode
  TB3CTL |= TBCLR; // Clear TAR
  
  TB3CCR0 = WHEEL_PERIOD; // PWM Period
  
  TB3CCTL1 = OUTMOD_7; // CCR1 reset/set
  RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.0 Right Forward PWM duty cycle
  
  TB3CCTL2 = OUTMOD_7; // CCR2 reset/set
  LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Left Forward PWM duty cycle
  
  TB3CCTL3 = OUTMOD_7; // CCR3 reset/set
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM duty cycle
  
  TB3CCTL4 = OUTMOD_7; // CCR4 reset/set
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.3 Left Reverse PWM duty cycle
  
  
}

void msec_sleep(unsigned int msec){
  //==============================================================================
  //  Function Name: five_msec_sleep
  //
  //  Description: Pauses the clock by doing a counter for x ms
  //
  //  Local Variables: msec
  //  Global Variables: FIVE_MS_INTERVALS
  //
  //  William Brazil
  //  Sept 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  
  FIVE_MS_INTERVALS = INIT;
  while((FIVE_MS_INTERVALS++) < msec);
}


void Init_ADC(void){
  //==============================================================================
  //  Function Name: Init_ADC
  //
  //  Description: Initializes ADC conversion and Registers 0, 1, and 2.
  //
  //  Local Variables: None
  //  Global Variables: None
  //
  //  William Brazil
  //  Oct 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  
  
  //------------------------------------------------------------------------------
  // V_DETECT_L (0x04) // P1 Pin 2 A2
  // V_DETECT_R (0x08) // P1 Pin 3 A3
  // V_THUMB    (0x02) // P5 Pin 1 A9 
  //------------------------------------------------------------------------------
  
  // ADCCTL0 Register
  ADCCTL0 = RESET;                  // Reset
  ADCCTL0 |= ADCSHT_0;          // 4 ADC clocks
  ADCCTL0 |= ADCMSC;            // MSC
  ADCCTL0 |= ADCON;             // ADC ON
 
  // ADCCTL1 Register
  ADCCTL1 = RESET;                  // Reset
  ADCCTL1 |= ADCSHS_0;          // 00b = ADCSC bit
  ADCCTL1 |= ADCSHP;            // ADC sample-and-hold SAMPCON signal from sampling timer.
  ADCCTL1 &= ~ADCISSH;          // ADC invert signal sample-and-hold.
  ADCCTL1 |= ADCDIV_0;          // ADC clock divider - 000b = Divide by 1
  ADCCTL1 |= ADCSSEL_0;         // ADC clock SMCLK
  ADCCTL1 |= ADCCONSEQ_0;       // ADC conversion sequence 00b = Single-channel single-conversion
  // ADCCTL1 & ADCBUSY identifies a conversion is in process
  
  // ADCCTL2 Register
  ADCCTL2 = RESET;                  // Reset
  ADCCTL2 |= ADCPDIV0;          // ADC pre-divider 00b = Pre-divide by 1
  ADCCTL2 |= ADCRES_1;          // ADC resolution 10b = 10 bit (12 clock cycle conversion time)
  ADCCTL2 &= ~ADCDF;            // ADC data read-back format 0b = Binary unsigned.
  ADCCTL2 &= ~ADCSR;            // ADC sampling rate 0b = ADC buffer supports up to 200 ksps
  
  // ADCMCTL0 Register
  ADCMCTL0 = RESET;
  ADCMCTL0 |= ADCSREF_0;        // VREF - 000b = {VR+ = AVCC and VR– = AVSS }
  ADCMCTL0 |= ADCINCH_2;        // V_DETECT_L A2
  ADCIE |= ADCIE0;
  ADCCTL0 |= ADCENC;            // ADC enable conversion.
  ADCCTL0 |= ADCSC;             // ADC start conversion.
}

void Init_DAC(void){
  //==============================================================================
  //  Function Name: Init_DAC
  //
  //  Description: Initializes DAC conversion
  //
  //  Local Variables: None
  //  Global Variables: None
  //
  //  William Brazil
  //  Oct 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  
  //using 1000 sets it to 6.1V
  DAC_data = 1000; // Value between 0x000 and 0x0FFF
  SAC3DAT = DAC_data; // Initial DAC data
  SAC3DAC = DACSREF_1; // Select int Vref as DAC reference
  SAC3DAC |= DACLSEL_0; // DAC latch loads when DACDAT written
  // SAC3DAC |= DACIE; // generate an interrupt
  SAC3DAC |= DACEN; // Enable DAC
  SAC3OA = NMUXEN; // SAC Negative input MUX controL
  SAC3OA |= PMUXEN; // SAC Positive input MUX control
  SAC3OA |= PSEL_1; // 12-bit reference DAC source selected
  SAC3OA |= NSEL_1; // Select negative pin input
  SAC3OA |= OAPM; // Select low speed and low power mode
  SAC3PGA = MSEL_1; // Set OA as buffer mode
  SAC3OA |= SACEN; // Enable SAC
  SAC3OA |= OAEN; // Enable OA
}

void Init_REF(void){
  //==============================================================================
  //  Function Name: Init_REF
  //
  //  Description: Initializes Refernce Module
  //
  //  Local Variables: None
  //  Global Variables: None
  //
  //  William Brazil
  //  Oct 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  
  // Configure reference module
  PMMCTL0_H = PMMPW_H; // Unlock the PMM registers
  PMMCTL2 = INTREFEN; // Enable internal reference
  PMMCTL2 |= REFVSEL_2; // Select 2.5V reference
  while(!(PMMCTL2 & REFGENRDY)); // Poll till internal reference settles
  // Using a while statement is not usually recommended without an exit strategy.
  // This while statement is the suggested operation to allow the reference to settle.
}