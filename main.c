//------------------------------------------------------------------------------
//  File name : main.c
//  Description: This file contains the Main Routine - "While" Operating System.
//
//
//  Author: Benjamin Tang  
//  Date: Nov 2016
//  Built with IAR Embedded Workbench Version: 6.50.1
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"


// Required defines
// In the event the universe no longer exists, this bit will reset

//Macros
// CHAR_SIZE_11            (11)
// MSEC0                   (0)
// MSEC50                  (50)
// SIZECNT5                (5)
// BIG0                    (1)
// BIG1                    (0)
// L_SPACE_1               (1)                   
// L_SPACE_2               (2)
// L_SPACE_3               (3)
// L_SPACE_4               (4)

// Global Variables
unsigned char menu_toggle = RESET;
volatile unsigned char control_state[CNTL_STATE_INDEX];
volatile unsigned int Time_Sequence;
char led_smclk;
volatile char one_time;
volatile unsigned int five_msec_count;
char posL1;
char posL2;
char posL3;
char posL4;
char size_count;
char big;
extern volatile unsigned char control_state[CNTL_STATE_INDEX];
extern volatile unsigned int Time_Sequence;
extern char led_smclk;
extern volatile char one_time;
extern volatile unsigned int five_msec_count;
extern char display_line_1[CHAR_SIZE_11];
extern char display_line_2[CHAR_SIZE_11];
extern char display_line_3[CHAR_SIZE_11];
extern char display_line_4[CHAR_SIZE_11];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;
extern char size_count;
extern char big;
extern unsigned int baudrate;
extern volatile unsigned int twohunmsec_counter;
extern char IOT_receive_command;
extern volatile char IOT_Char_Rx[SMALL_RING_SIZE];
extern unsigned int iot_rx_ring_rd;
char ipaddressL1[10];
char ipaddressL2[10];
unsigned int k;
unsigned int follow_toggle;

void increment_iot_rx_ring(void);

//ADC
//extern volatile unsigned int channelToSwitchCount;
volatile unsigned int updateDisplay_Ok;
char hexSignal[COUNTEIGHT];
unsigned int oneSecCount;
void command_menu(void);

void main(void){
  //============================================================================
  // Function name: main
  //
  // Description: This function contains the while loop that runs continuously
  // to act for the operating system. It also calls all the functions to
  // initialize the system.
  //
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Globals: char* display_1
  // char* display_2
  // slow_input_down
  // control_state[CNTL_STATE_INDEX]
  //
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  
  //----------------------------------------------------------------------------
  // Main Program
  // This is the main routine for the program. Execution of code starts here.
  // The operating system is Back Ground Fore Ground.
  //
  //----------------------------------------------------------------------------
  
  Init_Ports();                             // Initialize Ports
  Init_Clocks();                            // Initialize Clock System
  Init_Conditions();
  Time_Sequence = RESET;                    //
  Init_Timers();                            // Initialize Timers
  //  five_msec_sleep(MSEC50);                // 250 msec delay for the clock to settle
  //  Init_LEDs();                          // Initialize LEDs
  Init_LCD();                               // Initialize LCD
  Init_ADC();                               // Initialize ADC
  Init_Serial_UCA0(BRW_9600, MCTLW_9600);                       // Initialize Serial Port for USB
  Init_Serial_UCA1(BRW_9600, MCTLW_9600);                       // Initialize Serial Port for USB
  PJOUT |= IOT_RESET;
  
  
  posL1 = COUNTZERO;
  P3OUT &= ~IR_LED;  // Turn off IR LED
  //----------------------------------------------------------------------------
  // Begining of the "While" Operating System
  //----------------------------------------------------------------------------  
  //channelToSwitchCount = COUNTZERO;
  
  //char message[] = "NCSU  #1";
  //char baudrate_1[] = "9,600";
  //char baudrate_2[] = "115,200";
  
  
  hexSignal[COUNTZERO] = HEXN;
  hexSignal[COUNTERONE] = HEXC;
  hexSignal[COUNTERTWO] = HEXS;
  hexSignal[COUNTTHREE] = HEXU;
  hexSignal[COUNTFOUR] = HEXSPACE;
  hexSignal[COUNTFIVE] = HEXSPACE;
  hexSignal[COUNTSIX] = HEXPOUND;
  hexSignal[COUNTSEVEN] = HEXONE;
  
  // Case 0 = 9600
  // Case 1 = 115200
  
  // Project 08
  //Init_Serial_UCA1(BRW_9600, MCTLW_9600); 
  //UCA1IE |= UCTXIE;
  
  while(ALWAYS) { 
    display_1 = "Ben Tang";
    
    if (!(P4IN & SW1)){
      menu_toggle = RESET;
      display_2 = "";
      display_2 = "USB->CAR";
    }
    if (!(P4IN & SW2)) {
      menu_toggle = 1;
      display_2 = "";
      display_2 = "IOT->CAR";
    }
    menu();
    command_menu();
    
    for (int i = 0; i < SMALL_RING_SIZE; i++){       
      if(IOT_Char_Rx[iot_rx_ring_rd] == '1') {
        if(IOT_Char_Rx[iot_rx_ring_rd + 1] == '0') {
          for(int j = 0; j < 6; j ++) {
            ipaddressL1[j] = IOT_Char_Rx[iot_rx_ring_rd];
            increment_iot_rx_ring();
          }
          for(int k = 0; k < 7; k++) {
            ipaddressL2[k] = IOT_Char_Rx[iot_rx_ring_rd];
            increment_iot_rx_ring();
          }
        }
        increment_iot_rx_ring();
      }
      increment_iot_rx_ring();
      display_2 = "";
      display_3 = ipaddressL1;
      display_4 = ipaddressL2;
    }
    
    if(twohunmsec_counter > 10){
      Display_Process();
      twohunmsec_counter = RESET;
    }
  }    
}