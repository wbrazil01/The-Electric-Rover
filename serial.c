//===========================================================================
// File Name : serial.c
//
// Description: Initializes and handles serial communications
//
// Author: William Brazil
// Date: Oct 2020
// Compiler: Built with IAR Embedded Workbench Version: V7.20.1
//===========================================================================

#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"

extern char display_line[DISPLAY_ROWS][DISPLAY_COLUMNS];
extern char *display[DISPLAY_ROWS];
extern volatile unsigned char display_changed;
volatile char USB_Char_Rx[SMALL_RING_SIZE];
volatile char USB_Char_Tx[LARGE_RING_SIZE];
char IOT_2_PC[50];
char PC_2_IOT[16];
unsigned int iot_rx_wr = BEGINNING;
unsigned int iot_rx_rd = BEGINNING;
unsigned int iot_tx_wr = BEGINNING;
unsigned int iot_tx_rd = BEGINNING;
volatile unsigned int UCA0_index;
volatile unsigned int UCA1_index;
char test_command[TEN];
char string2display[ELEVEN] = "          ";
int counter = INIT;
char process_buffer[50]; // Size for appropriate Command Length
char response_buffer[50];
int pb_index;                  // Index for process_buffer
unsigned int tempsend = INIT;
unsigned int tempreceive = INIT;
unsigned int i = INIT;
unsigned int echoPC = INIT;     //tells tx that it can trasmit back to PC
unsigned int command = FALSE;   //signifies its a command
char test = NULL;
char testsend = NULL;
char testTCP = NULL;
unsigned int buffer1 = INIT;
unsigned int buffer2 = INIT;
unsigned int inputValid = FALSE;
extern char command_response[16];
int response_index;
int transmit_response = FALSE;
int input_processed = NO;
int CRPLACE = INIT;
char response = NULL;
int pbstatus = PAUSE;
extern int wifi_connected;
extern int ssid_found;
extern int ip_found;

void Init_Serial_UCA0(char speed){
  //==============================================================================
  //  Function Name: Init_Serial_UCA0
  //
  //  Description: Configure eUSCI_A0 for UART mode
  //
  //  Local Variables: speed
  //  Global Variables: NONE
  //
  //  William Brazil
  //  Oct 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  // Configure eUSCI_A0 for UART mode
  UCA0CTLW0 = INIT;
  UCA0CTLW0 |= UCSWRST ; // Put eUSCI in reset
  UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA0CTLW0 &= ~UCMSB; // MSB, LSB select
  UCA0CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
  UCA0CTLW0 &= ~UCPEN; // No Parity
  UCA0CTLW0 &= ~UCSYNC;
  UCA0CTLW0 &= ~UC7BIT;
  UCA0CTLW0 |= UCMODE_0;
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
  // UCA?MCTLW = UCSx + UCFx + UCOS16
  switch(speed){
  case LOWBAUD:
    UCA0BRW = 52 ; // 9.600 baud
    UCA0MCTLW = 0x4911 ;
    break;
  case HIGHBAUD:
    UCA0BRW = 4 ; // 115,200 baud
    UCA0MCTLW = 0x5551 ;
    break;
  default:break;
  }
  UCA0CTLW0 &= ~UCSWRST; // release from reset
  UCA0TXBUF = 0x00; // Prime the Pump
  UCA0IE |= UCRXIE;// Enable RX interrupt
  UCA0IE &= ~UCTXIE;
  //--------------------------------------------------------------
}

void Init_Serial_UCA1(char speed){
  //==============================================================================
  //  Function Name: Init_Serial_UCA1
  //
  //  Description: Configure eUSCI_A1 for UART mode
  //
  //  Local Variables: speed
  //  Global Variables: NONE
  //
  //  William Brazil
  //  Oct 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  UCA1CTLW0 = INIT;
  UCA1CTLW0 |= UCSWRST ; // Put eUSCI in reset
  UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA1CTLW0 &= ~UCMSB; // MSB, LSB select
  UCA1CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
  UCA1CTLW0 &= ~UCPEN; // No Parity
  UCA1CTLW0 &= ~UCSYNC;
  UCA1CTLW0 &= ~UC7BIT;
  UCA1CTLW0 |= UCMODE_0;
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
  // UCA?MCTLW = UCSx + UCFx + UCOS16
  switch(speed){
  case LOWBAUD:
    UCA1BRW = 52 ; // 9.600 baud
    UCA1MCTLW = 0x4911 ;
    break;
  case HIGHBAUD:
    UCA1BRW = 4 ; // 115,200 baud
    UCA1MCTLW = 0x5551 ;
    break;
  default:break;
  }
  UCA1CTLW0 &= ~UCSWRST ; // release from reset
  UCA1TXBUF = 0x00; // Prime the Pump
  UCA1IE |= UCRXIE;// Enable RX interrupt
  UCA1IE &= ~UCTXIE;   //Disable TX interrupt so nothing is transmitted
  
  //--------------------------------------------------------------
}

#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
  //==============================================================================
  //  Function Name: eUSCI_A0_ISR
  //
  //  Description: Handles the Rx and Tx of UCA0
  //
  //  Local Variables: i
  //  Global Variables: iot_rx_rd, iot_rx_wr, IOT_2_PC, process_buffer, pb_index
  //
  //  William Brazil
  //  Oct 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  switch(__even_in_range(UCA0IV,0x08)){
  case 0: // Vector 0 - no interrupt
    break;
  case 2: // Vector 2 - RXIFG
    testsend = UCA0RXBUF;
      if(testsend != NULL){
        IOT_2_PC[iot_rx_wr++] = testsend; // Rx -> IOT_2_PC character array
        if (iot_rx_wr >= (LARGE_RING_SIZE)){
          iot_rx_wr = BEGINNING; // Circular buffer back to beginning
        }
        
        if(wifi_connected == FALSE)
          check_wifi();
        else if(ssid_found == FALSE)    //if wifi_connected is true then we move on to the next one        
          ssid_grab();
        else if(ip_found == FALSE)
          ip_grab();
        
        checkTCP();                     //check character indicates TCP command
        
        UCA1IE |= UCTXIE;           //for testing echo back to PC
      }
      
    break;
  case 4: // Vector 4 - TXIFG
      UCA0TXBUF = process_buffer[iot_tx_wr];
      if (process_buffer[iot_tx_wr++] == CR){
        input_processed = TRUE;
        iot_tx_wr = BEGINNING;
        CRPLACE = INIT;
        UCA0IE &= ~UCTXIE;
      }
    
    break;
  default: break;
  }
}

#pragma vector = EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
  //==============================================================================
  //  Function Name: eUSCI_A1_ISR
  //
  //  Description: Handles the Rx and Tx of UCA1
  //
  //  Local Variables: None
  //  Global Variables: iot_rx_rd, iot_rx_wr, IOT_2_PC
  //
  //  William Brazil
  //  Oct 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
   switch(__even_in_range(UCA1IV,0x08)){
  case 0:                                       //no interrupt
    break;      
  case 2:                                       //RXIFG 
    test = UCA1RXBUF;
    
    if(test != NULL){
      PC_2_IOT[iot_rx_rd] = test; // Rx -> PC_2_IOT character array
      process_buffer[buffer1++] = PC_2_IOT[iot_rx_rd]; // Transmit Current Indexed value
      PC_2_IOT[iot_rx_rd++] = NULL;
      if (iot_rx_rd >= (SMALL_RING_SIZE)){
        iot_rx_rd = BEGINNING;
      }
      if(PC_2_IOT[iot_rx_rd] == '^')
        command = TRUE;
      
      if(test == CR){
        UCA0IE |= UCTXIE;
        CRPLACE = iot_rx_rd;
        buffer1 = INIT;
        to_process_buff();
      }  
    }
    
    break;
  case 4:
    UCA1TXBUF = IOT_2_PC[iot_tx_rd];
    IOT_2_PC[iot_tx_rd++] = NULL;
    if (iot_tx_rd >= (LARGE_RING_SIZE)){
      iot_tx_rd = BEGINNING;
    } 
    if (iot_tx_rd == iot_rx_wr){
      UCA1IE &= ~UCTXIE; // Disable TX interrupt 
    }
    
    break;
  default: break;
  }
}



void USCI_A0_transmit(void){ 
  //==============================================================================
  //  Function Name: USCI_A0_transmit
  //
  //  Description: Transmit Function for USCI_A0
  //
  //  Local Variables: None
  //  Global Variables: pb_index
  //
  //  William Brazil
  //  Oct 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  
  // Transmit Function for USCI_A0
  // Contents must be in process_buffer
  // End of Transmission is identified by NULL character in process_buffer
  // process_buffer includes Carriage Return and Line Feed
  pb_index = INIT; // Set Array index to first location
  UCA0IE |= UCTXIE; // Enable TX interrupt
}

void clear_process_buf(void){
  //==============================================================================
  //  Function Name: clear_process_buf
  //
  //  Description: Clear Process Buffer with NULL's
  //
  //  Local Variables: i
  //  Global Variables: temp
  //
  //  William Brazil
  //  Oct 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  int i = INIT;
  while(process_buffer[i] != NULL){
    process_buffer[i] = NULL;
    i++;
  }
}

void to_process_buff(void){
  
  
  for(int i=INIT; i<sizeof(string2display); i++){
    if(process_buffer[i] == NULL)
      string2display[i] = ' ';
    else
      string2display[i] = process_buffer[i];    //copy to string for displaying to screen
  }
}

void check_wifi(void){
  if((testsend == 'S') && (inputValid == FALSE))          //checking for wifi_connectivity
    inputValid = TRUE;
  else if((testsend == 'S') && (inputValid == TRUE)){
    wifi_connected = TRUE;
    inputValid = FALSE;
  }
}

void out_character(char character){
  while(!(UCA0IFG & UCTXIFG));
  UCA0TXBUF = character;
}