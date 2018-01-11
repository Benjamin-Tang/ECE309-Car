//------------------------------------------------------------------------------
//  File name : interrupts_ports.c
//  Description: This file contains the code to perform the port interrupts
//
//
//  Author: Benjamin Tang  
//  Date: Sept 2016
//  Built with IAR Embedded Workbench Version: 6.50.1
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

// Globals
volatile unsigned short int switchOnePress = RESET;
volatile unsigned short int switchOneDebounce;
volatile unsigned short int switchTwoPress = RESET;
volatile unsigned short int switchTwoDebounce;
volatile unsigned short int switchOneDebouncing = RESET;
volatile unsigned short int switchTwoDebouncing = RESET;
volatile unsigned int interrupt_counter = RESET;
volatile unsigned int twohunmsec_counter = RESET;
int timer_debounce = RESET;

  //============================================================================
  // Function name: switch_interrupt
  //
  // Description: This function contains the code to efficiently interrupt the
  // the switches
  //
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Globals: N/A
  //
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
#pragma vector=PORT4_VECTOR
__interrupt void switch_interrupt(void) {
  
  // Switch 1
  if (P4IFG & SW1) {
    switchOnePress = COUNTERONE;          // Set a variable to identify the switch has been pressed. 
    switchOneDebounce = RESET;      // Reset the count required of the debounce.
    P4IE &= ~SW1;                       // Disable the Switch Interrupt.
    P4IFG &= ~SW1;                      // Clear any current timer interrupt.
    TA0CCTL1 |= CCIE;                     // enable
    P3OUT |= IR_LED;
  }
  // Switch 2
  if (P4IFG & SW2) {
    switchTwoPress = COUNTERONE;          // Set a variable to identify the switch has been pressed. 
    switchTwoDebounce = RESET;      // Reset the count required of the debounce.
    P4IE &= ~SW2;                       // Disable the Switch Interrupt.
    TA0CCTL1 |= CCIE;                   // enable clock
    P4IFG &= ~SW2;                      // Clear any current timer interrupt.
    
    P3OUT &= ~IR_LED;  
  }
  Display_Process();
} 
//------------------------------------------------------------------------------