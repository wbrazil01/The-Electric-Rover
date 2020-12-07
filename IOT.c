#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"

extern char display_line[DISPLAY_ROWS][DISPLAY_COLUMNS];
extern volatile unsigned char display_changed;
extern char process_buffer[50];
extern int response_index;
extern int transmit_response;
char command_response[16];
extern int input_processed;
extern unsigned int buffer1;
extern unsigned int buffer2;
extern int pb_index;
extern unsigned int iot_tx_wr;
extern unsigned int iot_tx_rd;
extern unsigned int iot_rx_wr;
extern unsigned int iot_rx_rd;
extern char IOT_2_PC[50];
extern char PC_2_IOT[16];
int toPC = INIT;
int bootstate = WIFI;
int k = INIT;
int next = FALSE;
char start_command[11] = "AT+NSTAT=?\r";
char port_command[16] = "AT+NSTCP=1025,1\r";
char TCP_command[20];
extern int pbstatus;
int wifi_connected = FALSE;
char empty_command = '\r';
int ssid_found = FALSE;
char ssid[ELEVEN] = "          ";
int ssid_wr = INIT;
extern char testsend;
int foundSSID = FALSE;
int ipstatus = SEARCHING;
int ip_found = FALSE;
int found = FALSE;
char ip1[ELEVEN] = "          ";
char ip2[ELEVEN] = "          ";
int ip_section = INIT;
int ipcounter1 = INIT;
int ipcounter2 = INIT;
int numcounter1 = INIT;
int numcounter2 = INIT;
int foundTCP = INIT;
int tcpCount = INIT;
int skipcounter = INIT;
char TCPinstruction = NULL;
int TCPtimer = INIT;
extern int TCPcounter;
int arrivedcounter = INIT;
char arrivedstring[ELEVEN] = " Marker   ";
extern int FoundLine;
int followingLine = FALSE;
int travelcount = INIT;




void IOT(void){
  //==============================================================================
  //  Function Name: IOT
  //
  //  Description: Handles general IOT process regarding command inputs and 
  //               responses.
  //
  //  Local Variables: None
  //  Global Variables: bootsate, wifi_connected, empty_command, start_command  
  //
  //  William Brazil
  //  Nov 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  process_command(NULL);
  
  switch(bootstate){            //set to PAUSE by default until we are connected.
  case WIFI:
    if(wifi_connected == TRUE){ //if wifi is connected continue.
      out_character(empty_command);
      for(int z = INIT; z<sizeof(start_command);z++)
        out_character(start_command[z]);
      bootstate = SSID;
    }
    break;
  case SSID:
    if(ssid_found == TRUE){
      bootstate = IP;
    }
    break;
  case IP:
    if(ip_found == TRUE){
      bootstate = PORT;
    }
    break;
  case PORT:
    for(int z = INIT; z<sizeof(port_command);z++)
        out_character(port_command[z]);
    bootstate = PAUSE;
    display_ip();
    break;
  case PAUSE:
    break;
  case TCP:
    TB1CCR1 = TB1CCR1_INTERVAL;
    TB1CCR1 &= ~CCIFG;
    TB1CCTL1 &= ~CCIE;            //new command found. disable anything going on
    all_wheels_off();
    
    trimTCP();
    processTCP();
    bootstate = PAUSE;
    break;
  default:
    break;   
  }
}

void process_command(char command){
  if(input_processed == TRUE){
    clear_process_buf();                //clear
    input_processed = FALSE;               //reset indicator
  }
}



void ip_grab(void){
  //==============================================================================
  //  Function Name: ip_grab
  //
  //  Description: Parses the incoming characters to find the IP address and
  //              save it to a string.
  //
  //  Local Variables: None
  //  Global Variables: testsend, ipstatus, found, ip1, ipcounter, and ip_section
  //
  //  William Brazil
  //  Nov 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  switch(ipstatus){
  case SEARCHING:               //searching for "IP"
    if(testsend == 'I' && found == FALSE)         //first instance of I
      found = TRUE;
    else if(testsend != 'P' && found == TRUE)       //if next letter is not P then back to first if
      found = FALSE;
    else if(testsend == 'P' && found == TRUE){
      found = FALSE;
      ipstatus = FOUND;
    } 
    break;
  case FOUND:                  //searching for the '=' before the address
    if(testsend == '=')
      ipstatus = READING;
    break;
  case READING:                 //copying the address to two different arrays
    if(testsend != ' '){
      if(ip_section < TWO){             //first two sections
        ip1[ipcounter1++] = testsend;
        numcounter1++;
        if(testsend == '.')
          ip_section++;
      }else{                            //last two sections
        numcounter2++;
        ip2[ipcounter2++] = testsend;
      }
    }else{                              //space indicates no more values
      ipstatus = PAUSE;
      ip_found = TRUE;
    }
    break;
  default:
    break;
  }
}

void ssid_grab(void){
  //==============================================================================
  //  Function Name: ssid_grab
  //
  //  Description: Parses the incoming characters to find the SSID and
  //              save it to a string.
  //
  //  Local Variables: None
  //  Global Variables: testsend, ssid_found, ssid, and ssid_wr
  //
  //  William Brazil
  //  Nov 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  
  if(testsend == '"' && foundSSID == TRUE){        //second quotation        
    foundSSID = FALSE;
    ssid_found = TRUE;
  }
  
  if(foundSSID == TRUE)                 //check for second quotation first so it doesn't accidentally get added in on the last cycle
    ssid[ssid_wr++] = testsend;         //check for first quotation last so that the first character you add is ssid not "
  
  if(testsend == '"' && foundSSID == FALSE)            //first quotation
    foundSSID = TRUE;
  
}

void checkstats(void){
  
}

void checkTCP(void){
  //==============================================================================
  //  Function Name: checkTCP
  //
  //  Description: checks incoming message to see if it is a command
  //
  //  Local Variables: None
  //  Global Variables: testsend, foundTCP, tcpCount, bootstate, and TCP_command
  //
  //  William Brazil
  //  Nov 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  
  if(testsend == 0x1B && foundTCP == TRUE){        //second ESC        
    foundTCP = FALSE;
    tcpCount = INIT;
    bootstate = TCP;
  }
  
  if(foundTCP == TRUE){                 //check for second quotation first so it doesn't accidentally get added in on the last cycle
     TCP_command[tcpCount++] = testsend;
  }
  
  if(testsend == 0x1B && foundTCP == FALSE)            //first ESC
    foundTCP = TRUE;
}

void trimTCP(void){
  //==============================================================================
  //  Function Name: trimTCP
  //
  //  Description: takes the command received and parses it to see if it has the 
  //               correct pin, read the command, and the timing.
  //
  //  Local Variables: i
  //  Global Variables: TCP_command, TCPinstruction, and TCPtimer
  //
  //  William Brazil
  //  Nov 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  
  if(TCP_command[CARAT] == '^'){
    if(TCP_command[PIN1] == '7' && TCP_command[PIN2] == '4' && TCP_command[PIN3] == '5' && TCP_command[PIN4] == '2'){
      TCPcounter = INIT;
      TCPtimer = INIT;
      TCPinstruction = TCP_command[INSTRUCTION];
      TCPtimer += (TCP_command[TIME1]-DECCONV) * ONEHUNDRED;
      TCPtimer += (TCP_command[TIME2]-DECCONV) * TEN;
      TCPtimer += (TCP_command[TIME3]-DECCONV) * ONE;
      for(int i=INIT; i<8; i++){
        k = i + 3;
        TCP_command[i] = TCP_command[k];
        TCP_command[k] = NULL;
      }
    }
  }
}

void processTCP(void){
  //==============================================================================
  //  Function Name: processTCP
  //
  //  Description: reads TCPinstruction and runs the according action
  //
  //  Local Variables: i
  //  Global Variables: TCPinstruction, arrivedstring, display_line, FoundLine
  //                    display_changed, travelcount.
  //
  //  William Brazil
  //  Nov 2020
  //  Built with IAR Embedded Workbench Version: V(7.20.1)
  //==============================================================================
  switch(TCPinstruction){
  case 'F':
    all_wheels_off();
    forward_slow();
    TB1CCTL2 |= CCIE;
    Forward_Text();
    TCPinstruction = NULL;
    break;
  case 'B':
    all_wheels_off();
    reverse_slow();
    Reverse_Text();
    TCPinstruction = NULL;
    break;
  case 'R':
    all_wheels_off();
    left_wheel_forward_on();
    Right_Text();
    TCPinstruction = NULL;
    break;
  case 'L':
    all_wheels_off();
    right_wheel_forward_on();
    Left_Text();
    TCPinstruction = NULL;
    break;
  case 'S':
    all_wheels_off();
    stop();
    Stop_Text();
    TCPinstruction = NULL;
    break;
  case 'I':
    arrivedstring[MARKNUM] = arrivedcounter++ + ZERO;
    display_arrived();
    TCPinstruction = NULL;
    break;
  case 'T':
    TB1CCTL2 ^= CCIE;
    TCPinstruction = NULL;
  case 'X':
    strcpy(display_line[LINE1], "Intercept ");
    update_string(display_line[LINE1], LINE1);
    Display_Update(0,0,0,0);
    
    for(int i=INIT;i<MAX_COUNT;i++)            //small delay
      msec_sleep(FOUR*ONETHOUSAND);  
    
    FoundLine = FALSE;
    
    //search for blkline
    Search();                                   
    //stop
    all_wheels_off();
  
    //movement
    forward_slow();
    
    display_changed = TRUE;
    TCPinstruction = NULL;                      //put it into waiting
    break;
  case 'Y':
    for(int i=INIT;i<MAX_COUNT;i++)            //small delay
      msec_sleep(FOUR*ONETHOUSAND);  
    
    FoundLine = FALSE;
    
    //search for blkline
    Search();                                   
    //stop
    all_wheels_off();
    //display
    //movement
    right_wheel_forward_on();
    
    display_changed = TRUE;
    TCPinstruction = ZERO;
    break;
  case 'Z':
    FoundLine = FOLLOWING;
    
    all_wheels_off();
    
    Search();

    strcpy(display_line[LINE1], "BL Travel ");
    update_string(display_line[LINE1], LINE1);
    display_changed = TRUE;
    
    travelcount = TRUE;
    TCPinstruction = NULL;
    break;
  case 'C':
    FoundLine = FOLLOWING;

    strcpy(display_line[LINE1], "BL Circle ");
    update_string(display_line[LINE1], LINE1);
    Display_Update(0,0,0,0);
    
    all_wheels_off();
    
    for(int i=INIT;i<MAX_COUNT;i++)            //small delay
      msec_sleep(FOUR*ONETHOUSAND);
    
    
    Search();
    
    
    TCPinstruction = NULL;
  break;
  case 'E':
    all_wheels_off();  
    
    strcpy(display_line[LINE1], " BL EXIT  ");
    update_string(display_line[LINE1], LINE1);
    Display_Update(0,0,0,0);
    
    
    
    for(int i=INIT;i<MAX_COUNT;i++)            //small delay
      msec_sleep(FOUR*ONETHOUSAND);
    
    all_wheels_off();
    
    FoundLine = EXIT;
    
    Search();
    break;
  default:
    break;
  }
}