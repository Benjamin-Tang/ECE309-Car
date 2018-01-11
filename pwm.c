//------------------------------------------------------------------------------
//  File name : pwm.c
//  Description: This file contains the timer configurations for PWM
//
//  Author: Benjamin Tang  
//  Date: Sept 2016
//  Built with IAR Embedded Workbench Version: 6.50.1
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

unsigned int right_reverse_rate = OFF;
unsigned int left_reverse_rate = OFF;
unsigned int right_forward_rate = OFF;
unsigned int left_forward_rate = OFF;


//Macros========================================================================
void Init_Timer_B1(void) {
  //============================================================================
  // Function name: Init_Timer_B1
  //
  // Description: This function controls the time code for PWM forward.
  // 
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Timers Macros
  // 
  //
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  
  //------------------------------------------------------------------------------ 
  // SMCLK source, up count mode, PWM Right Side 
  //------------------------------------------------------------------------------
  TB1CTL = TBSSEL__SMCLK;       // SMCLK
  TB1CTL |= MC_1;               // Up Mode
  TB1CTL |= TBCLR;              // Clear TAR
  
  right_forward_rate = OFF;     // Set Right Forward Off
  left_forward_rate = OFF;      // Set Left Forward Off
  
  TB1CCR0 = WHEEL_PERIOD;       // PWM Period
  TB1CCTL1 = OUTMOD_7;          // CCR1 reset/set
  TB1CCR1 = right_forward_rate; // P3.4 Right Forward PWM duty cycle
  TB1CCTL2 = OUTMOD_7;          // CCR2 reset/set
  TB1CCR2 = left_forward_rate;  // P3.5 Left Forward PWM duty cycle
  //------------------------------------------------------------------------------ 
}

void Init_Timer_B2(void) {
  //============================================================================
  // Function name: Init_Timer_B1
  //
  // Description: This function controls the time code for PWM reverse.
  // 
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Timers Macros
  // 
  //
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  
  //------------------------------------------------------------------------------ 
  // SMCLK source, up count mode, PWM Right Side 
  //------------------------------------------------------------------------------
  TB2CTL = TBSSEL__SMCLK;       // SMCLK
  TB2CTL |= MC_1;               // Up Mode
  TB2CTL |= TBCLR;              // Clear TAR
  
  right_reverse_rate = OFF;     // Set Right reverse Off
  left_reverse_rate = OFF;      // Set Left reverse Off
  
  TB2CCR0 = WHEEL_PERIOD;       // PWM Period
  TB2CCTL1 = OUTMOD_7;          // CCR1 reset/set
  TB2CCR1 = right_reverse_rate; // P3.4 Right reverse PWM duty cycle
  TB2CCTL2 = OUTMOD_7;          // CCR2 reset/set
  TB2CCR2 = left_reverse_rate;  // P3.5 Left reverse PWM duty cycle
  //------------------------------------------------------------------------------ 
}