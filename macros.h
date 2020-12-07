//===========================================================================
// File Name : macros.h
//
// Description: This file contains the macros used by all the other files
//
// Author: William Brazil
// Date: August 2020
// Compiler: Built with IAR Embedded Workbench Version: 7.20.1 
//===========================================================================
#include "ports.h"

//main.c macros
//#define RESET_STATE             (0)
//#define ALWAYS                  (1)
//#define ORIGINAL             (0x00) //
//#define RED_LED              (0x01) // RED LED 0
//#define GRN_LED              (0x40) // 6 GREEN LED
//#define SW2                  (0x08) // 2.3 SW2
//#define SW1                  (0x02) // 4.1 SW1
//#define Time_Sequence_Rate         (50)
//#define S1250 (1250/Time_Sequence_Rate) //
//#define S1000 (1000/Time_Sequence_Rate) //
//#define S750   (750/Time_Sequence_Rate) //
//#define S500   (500/Time_Sequence_Rate) //
//#define S250   (250/Time_Sequence_Rate) //

//simplified main.c macros
#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // GREEN LED 1
#define LINE1                   (0)
#define LINE2                   (1)
#define LINE3                   (2)
#define LINE4                   (3)
#define FALSE                   (0)     
#define TRUE                    (1)
#define INIT                    (0)       

//display macros
#define DISPLAY_COLUMNS         (11)
#define DISPLAY_ROWS            (4)        
#define L                       (0)
#define R                       (6)

//clocks.c macros
#define MCLK_FREQ_MHZ           (4)              // MCLK = 1MHz
#define CLEAR_REGISTER     (0X0000)

// Wheel States 
#define NONE            ('N')
#define STRAIGHT        ('L')
#define CIRCLE          ('C')
#define FIGURE8         ('F')
#define TRIANGLE        ('T')
#define WAIT            ('W')
#define START           ('S')
#define RUN             ('R')
#define END             ('E')
#define WHEEL_COUNT_TIME (10)
#define RIGHT_COUNT_TIME (7)
#define LEFT_COUNT_TIME  (7)
#define TRAVEL_DISTANCE  (2)
#define WAITING2START    (300)

//timer.c defines
#define TB0CCR0_INTERVAL (25000) // 4,000,000 / 8 / 8 / (1 / 200msec)
#define TB0CCR1_INTERVAL (62500) // 4,000,000 / 8 / 8 / (1 / 500msec)
#define TB0CCR2_INTERVAL (12500) // 4,000,000 / 8 / 8 / (1 / 100msec)
#define TB0CTL_INTERVAL  (6250)
#define TB1CCR0_INTERVAL (125)  //1msec
#define TB1CCR1_INTERVAL (1250) //10msec
#define TB1CCR2_INTERVAL (62500)        
#define TimerB0_0CCR_VECTOR (TIMER0_B0_VECTOR)        
#define TimerB0_1_2_OF_CCR_VECTOR (TIMER0_B1_VECTOR)
#define DELAY           (5)
#define MAX_DELAY       (62500)
#define MAX_COUNT       (256)
#define RIGHT_FORWARD_SPEED     (TB3CCR2)
#define LEFT_FORWARD_SPEED      (TB3CCR1)
#define RIGHT_REVERSE_SPEED     (TB3CCR4)
#define LEFT_REVERSE_SPEED      (TB3CCR3)
#define WHEEL_PERIOD    (40005)
#define WHEEL_OFF       (0)
#define WHEEL_ON        (40000)
#define WHEEL_ON_75     (30000)
#define WHEEL_ON_50     WHEEL_ON
#define WHEEL_ON_25     (1000)
#define WHEEL_ON_20     (8000)
#define WHEEL_ON_15     (6000)
#define WHEEL_ON_10     (4000)
#define WHEEL_ON_5      (2000)
#define LEFT_DIFFERENTIAL       (200)       
#define TENMINPL        (2)
#define MINPL           (3)
#define TENSECPL        (5)
#define SECPL           (6)

//Generic macros
#define ON              (1)
#define OFF             (0)
#define INCREMENT       (1)
#define ZERO            ('0')
#define ONE             (1)
#define TWO             (2)
#define FOUR            (4)
#define FIVE            (5)
#define SEVEN           (7)
#define TEN             (10)
#define ELEVEN          (11)
#define FIFTEEN         (15)
#define TWENTY          (20)
#define FIFTY           (50)
#define SEVENTY         (70)
#define ONETHOUSAND     (1000)
#define ONEHUNDRED      (100)
#define RESET           (0)
#define COLUMN_FOUR     (3)
#define COLUMN_FIVE     (4)
#define COLUMN_SIX      (5)
#define COLUMN_SEVEN    (6)
#define SIXPLACES       (6)
#define clearstring     ("          ")
#define YES             (1)
#define NO              (0)
#define DECCONV         (48)

//HEX to BCD Conversion macros
#define Thousands       (0)
#define Hundreds        (1)
#define Tens            (2)
#define Ones            (3)
#define End             (4)
#define ASCII_CONV      (0x30)
#define ONETHOUSAND     (1000)
#define ONEHUNDRED      (100)
#define TEN             (10)
#define ELEVEN          (11)

//ADC macros
#define Left_Detector   (0)
#define Right_Detector  (1)
#define Thumbwheel      (2)

//Serial Macros
#define BEGINNING       (0)
#define SMALL_RING_SIZE (16)
#define LARGE_RING_SIZE (49)
#define LOWBAUD         ('0')
#define HIGHBAUD        ('1')
#define LOWERRATE   ("  009600  ")
#define HIGHERRATE  ("  115200  ")
#define CR              ('\r')
#define LF              ('\n')
#define PROCESSED       (2)
#define SEND            (0)
#define RECEIVE         (1)
#define WIFI            (0)
#define SSID            (1)
#define IP              (2)
#define PORT            (3)
#define PAUSE           (4)
#define TCP             (5)
#define CMDIN           (0)
#define CMDOUT          (1)
#define YES1            CMDIN
#define YES2            CMDOUT
#define SEARCHING       (0)
#define FOUND           (1)
#define READING         (2)
#define CARAT           (2)
#define PIN1            (3)
#define PIN2            (4)
#define PIN3            (5)
#define PIN4            (6)
#define INSTRUCTION     (7)
#define TIME1           (8)
#define TIME2           (9)
#define TIME3           (10)

//IOT course macros
#define MARKNUM         (8)
#define FOLLOWING       (2)
#define EXIT            (3)