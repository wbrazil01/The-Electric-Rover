// ==============================================================================
//
//  Description: This file contains several function s regarding the operation of
//              the display
//
//  William Brazil
//  Nov 2020
//  Built with IAR Embedded Workbench Version: V7.20.1
// ==============================================================================

#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include  "macros.h"

extern char display_line[DISPLAY_ROWS][DISPLAY_COLUMNS];
extern volatile unsigned char display_changed;
extern char adc_char[DISPLAY_COLUMNS];
extern volatile unsigned char update_display;
extern char string2display[ELEVEN];
extern char baudrate[TEN];
extern char process_buffer[50][2];
extern char ssid[ELEVEN];
extern char ip1[ELEVEN];
extern char ip2[ELEVEN];
extern char TCP_command[20];
extern char arrivedstring[ELEVEN];
extern char displaytimer[ELEVEN];

void Display(void){
  if(update_display){
    update_display = INIT;
    Display_Update(0,0,0,0);
  }
}

void BootText(void){
  strcpy(display_line[LINE1], "Connecting");
  update_string(display_line[LINE1], LINE1);
  strcpy(display_line[LINE2], "          ");
  update_string(display_line[LINE2], LINE2);
  strcpy(display_line[LINE3], "           ");
  update_string(display_line[LINE3], LINE3);
  strcpy(display_line[LINE4], "           ");
  update_string(display_line[LINE4], LINE4);
  
  display_changed = TRUE;
}

void Forward_Text(void){
  strcpy(display_line[LINE1], "  Forward ");
  update_string(display_line[LINE1], LINE1);
  
  display_changed = TRUE;
}

void Reverse_Text(void){
  strcpy(display_line[LINE1], "  Reverse ");
  update_string(display_line[LINE1], LINE1);
  
  display_changed = TRUE;
}

void Stop_Text(void){
  strcpy(display_line[LINE1], "   STOP   ");
  update_string(display_line[LINE1], LINE1);

  display_changed = TRUE;
}

void Right_Text(void){
  strcpy(display_line[LINE1], "   RIGHT  ");
  update_string(display_line[LINE1], LINE1);
  
  display_changed = TRUE;
}

void Left_Text(void){
  strcpy(display_line[LINE1], "   LEFT   ");
  update_string(display_line[LINE1], LINE1);
  
  display_changed = TRUE;
}

void clockwise_text(void){
  strcpy(display_line[LINE1], "   Spin   ");
  update_string(display_line[LINE1], LINE1);
  strcpy(display_line[LINE2], " Clockwise");
  update_string(display_line[LINE2], LINE2);
  strcpy(display_line[LINE3], "          ");
  update_string(display_line[LINE3], LINE3);
  
  display_changed = TRUE;
}

void counterclockwise_text(void){
  strcpy(display_line[LINE1], "   Spin   ");
  update_string(display_line[LINE1], LINE1);
  strcpy(display_line[LINE2], "  Counter ");
  update_string(display_line[LINE2], LINE2);
  strcpy(display_line[LINE3], " Clockwise");
  update_string(display_line[LINE3], LINE3);
  
  display_changed = TRUE;
}

void Reset_Text(void){
  strcpy(display_line[LINE1], "   NCSU   ");
  update_string(display_line[LINE1], LINE1);
  strcpy(display_line[LINE2], " WOLFPACK ");
  update_string(display_line[LINE2], LINE2);
  strcpy(display_line[LINE3], "  ECE306  ");
  update_string(display_line[LINE4], LINE4);
  
  display_changed = TRUE;
}

void emitter_state(int state){
  switch(state){
  case ON:
    strcpy(display_line[LINE2], "IR:  ON   ");
    update_string(display_line[LINE2], LINE2);
    break;
  case OFF:
    strcpy(display_line[LINE2], "IR:  OFF   ");
    update_string(display_line[LINE2], LINE2);
    break;
  default:
    break;
  }
  display_changed = TRUE;
  
}

void adc_line4(char location){
  strcpy(display_line[LINE3], "L    R    ");
  update_string(display_line[LINE3], LINE3);
  strcpy(display_line[LINE4],adc_char);
  update_string(display_line[LINE4], LINE4);
  
  display_changed = TRUE;
}

void clear_display(void){
  strcpy(display_line[LINE1], "          ");
  update_string(display_line[LINE1], LINE1);
  strcpy(display_line[LINE2], "          ");
  update_string(display_line[LINE2], LINE2);
  strcpy(display_line[LINE3], "          ");
  update_string(display_line[LINE3], LINE3);
  strcpy(display_line[LINE4], "          ");
  update_string(display_line[LINE4], LINE4);
  
  display_changed = TRUE;
}

void display_received(void){
  strcpy(display_line[LINE1], " Recieved ");
  update_string(display_line[LINE1], LINE1);
  strcpy(display_line[LINE4], string2display);
  update_string(display_line[LINE4], LINE4);
  display_changed = TRUE;
}

void display_transmitted(void){
  strcpy(display_line[LINE1], " Transmit ");
  update_string(display_line[LINE1], LINE1);
  strcpy(display_line[LINE2], string2display);
  update_string(display_line[LINE2], LINE2);
  display_changed = TRUE;
}

void display_connected(void){
  strcpy(display_line[LINE1], "Connected ");
  update_string(display_line[LINE1], LINE1);
  display_changed = TRUE;
}

void display_ssid(void){
  strcpy(display_line[LINE1], ssid);
  update_string(display_line[LINE1], LINE1);
  display_changed = TRUE;
}

void display_ip(void){
  strcpy(display_line[LINE1], " Waiting  ");
  update_string(display_line[LINE1], LINE1);
  strcpy(display_line[LINE2], ip1);
  update_string(display_line[LINE2], LINE2);
  strcpy(display_line[LINE3], ip2);
  update_string(display_line[LINE3], LINE3);
  strcpy(display_line[LINE4], displaytimer);
  update_string(display_line[LINE4], LINE4);
  
  display_changed = TRUE;
}

void display_tcp(void){
  strcpy(display_line[LINE3], TCP_command);
  update_string(display_line[LINE3], LINE3);
  
  display_changed = TRUE;
}

void display_arrived(void){
  strcpy(display_line[LINE1], arrivedstring);
  update_string(display_line[LINE1], LINE1);
  
  
  display_changed = TRUE;
}

void display_timer(void){
  strcpy(display_line[LINE4], displaytimer);
  update_string(display_line[LINE4], LINE4);
  
  display_changed = TRUE;
}