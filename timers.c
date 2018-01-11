//------------------------------------------------------------------------------
//  File name : timers.c
//  Description: This file contains the Timer Configurations
//
//  Author: Benjamin Tang  
//  Date: Nov 2016
//  Built with IAR Embedded Workbench Version: 6.50.1
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"


//Globals
extern unsigned int oneSecCount;
unsigned int fivemseccounter;

//============================================================================
// Function name: Init_Timers
//
// Description: This function initializes the Timers.
// 
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
//  Benjamin Tang  
//  Date: Sept 2016
//  Built with IAR Embedded Workbench Version: 6.50.1
//============================================================================
void Init_Timers(void){  
  //----------------------------------------------------------------------------
  // Timer Configurations
  //----------------------------------------------------------------------------
  Init_Timer_A0(); //
  //  Init_Timer_A1(); //
  //  Init_Timer_B0(); //
  Init_Timer_B1(); // PWM Timer Forward
  Init_Timer_B2(); // PWM TImer Reverse
  //  Required for provided compiled code to work
  //----------------------------------------------------------------------------
}

void waitForSeconds(int second){
 oneSecCount = COUNTZERO;
        while ( oneSecCount <=(second*COUNTFIVE)){};
}