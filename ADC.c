// ==============================================================================
//
//  Description: This file contains the ADC Initialization and Hex to BCD Conversion
//
//  William Brazil
//  Nov 2020
//  Built with IAR Embedded Workbench Version: V7.20.1
// ==============================================================================

#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include  "macros.h"

char adc_char[DISPLAY_COLUMNS] = "          ";

void HEXtoBCD(int hex_value, int side){
  //==============================================================================
  //  Function Name: HEXtoBCD
  //
  //  Description: Convert a Hex number to a BCD for display on an LCD or monitor 
  //
  //  Local Variables: value, hex_value
  //  Global Variables: adc_char[DISPLAY_COLUMNS]
  //
  //  William Brazil
  //  Oct 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  
  int value = INIT;
  
  switch(side){
  case L:
    adc_char[Thousands] = ZERO;
    while (hex_value >= ONETHOUSAND){
      hex_value = hex_value - ONETHOUSAND;
      value++;
      adc_char[Thousands] = ASCII_CONV + value;
    }
    value = INIT;
    adc_char[Hundreds] = ZERO;
    while (hex_value >= ONEHUNDRED){
      hex_value = hex_value - ONEHUNDRED;
      value++;
      adc_char[Hundreds] = ASCII_CONV + value;
    }
    value = INIT;
    adc_char[Tens] = ZERO;
    while (hex_value >= TEN){
      hex_value = hex_value - TEN;
      value++;
      adc_char[Tens] = ASCII_CONV + value;
    }
    adc_char[Ones] = ZERO;
    adc_char[Ones] = ASCII_CONV + hex_value;
    break;
  case R:
    adc_char[Thousands+6] = ZERO;
    while (hex_value >= ONETHOUSAND){
      hex_value = hex_value - ONETHOUSAND;
      value++;
      adc_char[Thousands+6] = ASCII_CONV + value;
    }
    value = INIT;
    adc_char[Hundreds+6] = ZERO;
    while (hex_value >= ONEHUNDRED){
      hex_value = hex_value - ONEHUNDRED;
      value++;
      adc_char[Hundreds+6] = ASCII_CONV + value;
    }
    value = INIT;
    adc_char[Tens+6] = ZERO;
    while (hex_value >= TEN){
      hex_value = hex_value - TEN;
      value++;
      adc_char[Tens+6] = ASCII_CONV + value;
    }
    adc_char[Ones+6] = ZERO;
    adc_char[Ones+6] = ASCII_CONV + hex_value;
    break;
  default: break;
  }
}

void ADC_Process(void){
  //==============================================================================
  //  Function Name: ADC_Process
  //
  //  Description: Holds program in place while ADC conversions are being made
  //
  //  Local Variables: None
  //  Global Variables: None
  //
  //  William Brazil
  //  Oct 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  
  while(ADCCTL1 && ADCBUSY);
  ADCCTL0 |= ADCENC;            // ADC enable conversion.
  ADCCTL0 |= ADCSC;             // ADC start conversion.
}