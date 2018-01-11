//------------------------------------------------------------------------------
//  File name : interupt_timers.c
//  Description: This file contains the code to configure the timer interrupts
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


// Gloabls
extern volatile unsigned int four_counter;
extern volatile unsigned int updateDisplay_Ok;
volatile unsigned int four_counter = FALSE;
extern volatile unsigned short int switchOnePress;
extern volatile unsigned short int switchOneDebounce;
extern volatile unsigned short int switchTwoPress;
extern volatile unsigned short int switchTwoDebounce;
extern volatile unsigned short int switchOneDebouncing;
extern volatile unsigned short int switchTwoDebouncing;
extern volatile unsigned int interrupt_counter;
extern volatile unsigned int twohunmsec_counter;
extern unsigned int oneSecCount;

void Init_Timer_A0(void) {
  //============================================================================
  // Function name: Init_Timer_A0
  //
  // Description: This function contains the code to initilize the timer A0
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
  //----------------------------------------------------------------------------
  // Timer A0 initialization sets up both A0_0 and A0_1-A0_2
  
  TA0CTL = TASSEL__SMCLK;       // SMCLK source
  TA0CTL |= TACLR;              // Resets TA0R, clock divider, count direction 
  TA0CTL |= MC__CONTINOUS;      // Continuous up
  TA0CTL |= ID__4;              // Divide clock by 4
  TA0CTL &= ~TAIE;              // Disable Overflow Interrupt
  TA0CTL &= ~TAIFG;             // Clear Overflow Interrupt flag
  TA0EX0 = TAIDEX_7;            // Divide clock by an additional 8
  TA0CCR0 = TA0CCR0_INTERVAL;   // CCR0
  TA0CCTL0 |= CCIE;             // CCR0 enable interrupt
  
  TA0CCR1 = TA0CCR1_INTERVAL;  // CCR1
  TA0CCTL1 |= CCIE;            // CCR1 enable interrupt
  
  TA0CCR2 = TA0CCR2_INTERVAL;  // CCR2
  TA0CCTL2 |= CCIE;            // CCR2 enable interrupt
} 
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// TimerA0 0 Interrupt handler
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void){
  //============================================================================
  // Function name: Timer0_A0_ISR
  //
  // Description: This function contains the code to perform the TimerA0 0 
  // Interrupt handler
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
  //----------------------------------------------------------------------------
  
  //...... Add What you need happen in the interrupt ......
  TA0CCR0 += TA0CCR0_INTERVAL; // Add Offset to TACCR0 
  //  if (interrupt_counter == MSEC100){
  //    //P1OUT ^= LCD_BACKLITE ; // LCD_BACKLITE on to indicate boot ISR working 
  //    interrupt_counter = MSEC0;
  //    
  //    //while (four_counter <= 2){
  //    four_counter++;
  //  }
  //  interrupt_counter++;
  
  // 200 millisecond counter
  if (interrupt_counter == COUNTFORTY){
    //P1OUT ^= LCD_BACKLITE ; // LCD_BACKLITE on to indicate boot ISR working 
    interrupt_counter = RESET;
    updateDisplay_Ok = TRUE;
          oneSecCount++;
    //while (four_counter <= 2){
    four_counter++;    
  }
  interrupt_counter++;
  twohunmsec_counter++;

}

//----------------------------------------------------------------------------
// TimerA0 1-2, Overflow Interrupt Vector (TAIV) handler
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void){
  switch(__even_in_range(TA0IV,COUNTFOURTEEN)){
  case COUNTZERO: break; // No interrupt 
  case COUNTERTWO: // CCR1 not used
    TA0CCR1 += TA0CCR1_INTERVAL;     // Add Offset to TACCR1
    
    if ( (switchOnePress == RESET) && (switchTwoPress == RESET)) {
      TA0CCTL1 &= ~CCIE; // disable clock
    }
    break;
  case  COUNTFOUR:                           // CCR2 not used
    //...... Add What you need happen in the interrupt ......
    TA0CCR2 += TA0CCR2_INTERVAL;     // Add Offset to TACCR2
    break;
  case COUNTFOURTEEN:                           // overflow
    //...... Add What you need happen in the interrupt ......
    break; 
  default: break;
  } 
  //----------------------------------------------------------------------------
}

