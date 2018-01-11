//------------------------------------------------------------------------------
//  File name : LED.c
//  Description: This file contains the 8 LEDs
//
//  Author: Benjamin Tang  
//  Date: Sept 2016
//  Built with IAR Embedded Workbench Version: 6.50.1
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"
#include  "globals.h"

void Init_LEDs(void){
  
  //============================================================================
  // Function name: Init_LEDs
  //
  // Description: This function initializes the LED Configurations.
  // 
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  //
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  
  //----------------------------------------------------------------------------
  // LED Configurations
  //----------------------------------------------------------------------------
  // Turns on all 8 LEDs
  //  PJOUT &= ~LED1;
  //  PJOUT &= ~LED2;
  //  PJOUT &= ~LED3;
  //  PJOUT &= ~LED4;
  //  P3OUT &= ~LED5;
  //  P3OUT &= ~LED6;
  //  P3OUT &= ~LED7;
  //  P3OUT &= ~LED8;
  //----------------------------------------------------------------------------
}

