//===========================================================================
// File Name : states.c
//
// Description: This file contains different states for wheel movement
//
// Author: William Brazil
// Date: September 2020
// Compiler: Built with IAR Embedded Workbench Version: V7.20.1
//===========================================================================
#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include  "macros.h"

char state;
extern unsigned int cycle_time;
extern unsigned int time_change;
unsigned int right_motor_count;
unsigned int left_motor_count;
unsigned int segment_count;
unsigned int delay_start;
extern char event;
unsigned int count;
unsigned int left_time;
unsigned int right_time;
unsigned int rev;               //Time spent doing an action
unsigned int repeat;            //number of times the shape will repeat
unsigned int loopcount;         //Each shape has segments (i.e. Figure 8 has two loops, triangle has 3 sides and 3 corners)
                                //Loopcount is an indicator of how many segements there are in said shape

//STRAIGHT==========================================================
void Run_Straight(void){                
  switch(state){
   case WAIT:           
    wait_case();
    break; 
  case START:           
    start_case();
    break;              
  case RUN:      // Run
    straight_case();
    break; 
  case END:      // End
    end_case();
    break; 
  default: break;
 }
}
//==================================================================

//CIRCLE============================================================
void Run_Circle(void){                  //CIRCLE
  switch(state){
   case WAIT:           
    wait_case();
    break; 
  case START:           
    start_case();
    break;              
  case RUN:      // Run
    circle_case();
    break; 
  case END:      // End
    end_case();
    break; 
  default: break;
  }
}
//==================================================================

//FIGURE8===========================================================
void Run_Figure8(void){
  switch(state){
   case WAIT:           
    wait_case();
    break; 
  case START:           
    start_case();
    break;              
  case RUN:      // Run
    figure8_case();
    break; 
  case END:      // End
    end_case();
    break; 
  default: break;
  }
}
//==================================================================

//TRIANGLE==========================================================
void Run_Triangle(void){
  switch(state){
   case WAIT:           
    wait_case();
    break; 
  case START:           
    start_case();
    break;              
  case RUN:      // Run
    triangle_case();
    break; 
  case END:      // End
    end_case();
    break; 
  default: break;
  }
}
//==================================================================

void wait_case(void){
  if(time_change){
    time_change = 0;
    if(delay_start++ >= WAITING2START){
      delay_start = 0;
      state = START;
    }
  }
  loopcount = 0;
}

void start_case(void){
  cycle_time = 0;
  right_motor_count = 0;
  left_motor_count = 0;
  left_time = (LEFT_COUNT_TIME/7)-1;
  right_time = (RIGHT_COUNT_TIME/7)-1;
  Forward_On();
  segment_count = 0;
  state = RUN;
}

void straight_case(void){               //STRAIGHT
  if(time_change){
    time_change = 0;
    if(segment_count <= TRAVEL_DISTANCE){
      if(right_motor_count++ >= RIGHT_COUNT_TIME){
        P6OUT &= ~R_FORWARD;
      }
      if(left_motor_count++ >= LEFT_COUNT_TIME){
        P6OUT &= ~L_FORWARD;
      }
      if(cycle_time >= WHEEL_COUNT_TIME){
        cycle_time = 0;
        right_motor_count = 0;
        left_motor_count = 0;
        segment_count++;
        Forward_Move();
      }
    }else{
      state = END;
    }
  }
}

void circle_case(void){                 //CIRCLE
  rev = TRAVEL_DISTANCE*63;             // how long I want to be turning for
  
  right_turn(rev);                      //the turn itself
  
  if(segment_count > rev && repeat > 0){   //repeats the number of times indicated in switches.c
    repeat--;
    state = START;
  }else if(segment_count > rev && repeat == 0){
    state = END;
  }
}

void figure8_case(void){                //FIGURE8
  
  rev = TRAVEL_DISTANCE*63;        //how long I want to be turning for

  switch(loopcount){    //The actual turns
    case 0:
      left_turn(rev);
      break;
    case 1:
      right_turn(rev);
      break;
    default: break;
  }
  
  if(segment_count > rev && loopcount < 1){   //This checks whether its turned both left and right or not
    loopcount++;
    segment_count = 0;
  }
  if (segment_count > rev && loopcount == 1){
    if(repeat != 0){
      repeat--;
      loopcount = 0;
      state=START;
    }else if(repeat == 0){
      state=END;
    }
  }
}


void triangle_case(void){               //TRIANGLE
   rev = TRAVEL_DISTANCE*21;             // how long I want to be turning for
  
  switch(loopcount){    //The actual turns
    case 0:
      straight(rev);
      break;
    case 1:
      left_turn(rev);
      break;
    case 2:
      straight(rev);
      break;
    case 3:
      left_turn(rev);
      break;
    case 4:
      straight(rev);
      break;
    case 5:
      left_turn(rev);
      break;
    default: break;
  }                      //the turn itself
  
  if(segment_count > rev && loopcount < 5){   //This checks whether its turned both left and right or not
    loopcount++;
    segment_count = 0;
  }
  if (segment_count > rev && loopcount == 5){
    if(repeat != 0){
      repeat--;
      loopcount = 0;
      state=START;
    }else if(repeat == 0){
      state=END;
    }
  }
}

void end_case(void){
  Forward_Off();
  state = WAIT;
  event = NONE;
}

void left_turn(unsigned int turntime){
  if(time_change){
    time_change = 0;
    if(segment_count <= turntime){
      if(right_motor_count++ >= RIGHT_COUNT_TIME){
        P6OUT &= ~R_FORWARD;
      }
      if(left_motor_count++ >= left_time){
        P6OUT &= ~L_FORWARD;
      }
      if(cycle_time >= WHEEL_COUNT_TIME){
        cycle_time = 0;
        right_motor_count = 0;
        left_motor_count = 0;
        segment_count++;
        Forward_Move();
      }
    }
  }
}

void right_turn(unsigned int turntime){
  if(time_change){
    time_change = 0;
    if(segment_count <= turntime+4) {
      if(right_motor_count++ >= right_time){
        P6OUT &= ~R_FORWARD;
      }
      if(left_motor_count++ >= LEFT_COUNT_TIME){
        P6OUT &= ~L_FORWARD;
      }
      if(cycle_time >= WHEEL_COUNT_TIME){
        cycle_time = 0;
        right_motor_count = 0;
        left_motor_count = 0;
        segment_count++;
        Forward_Move();
      }
    }
  }
  rev = rev+4;
}

void straight(unsigned int turntime){
  if(time_change){
    time_change = 0;
    if(segment_count <= turntime/6){
      if(right_motor_count++ >= RIGHT_COUNT_TIME){
        P6OUT &= ~R_FORWARD;
      }
      if(left_motor_count++ >= LEFT_COUNT_TIME){
        P6OUT &= ~L_FORWARD;
      }
      if(cycle_time >= WHEEL_COUNT_TIME){
        cycle_time = 0;
        right_motor_count = 0;
        left_motor_count = 0;
        segment_count++;
        Forward_Move();
      }
    }
  }
  rev = rev/7;
}